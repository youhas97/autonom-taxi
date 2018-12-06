#include "img_proc.h"

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

typedef std::vector<cv::Vec4i> lines_t;

#define FONT cv::FONT_HERSHEY_PLAIN

static int WIDTH = 256;
static int HEIGHT = 144;

const int THR_TYPES[] = {cv::THRESH_BINARY, cv::THRESH_BINARY_INV,
                         cv::THRESH_TRUNC, cv::THRESH_TOZERO,
                         cv::THRESH_TOZERO_INV, cv::THRESH_MASK,
                         cv::THRESH_OTSU};
#define TRACK_MAX 255
#define TRACK_MAX_THRESH sizeof(THR_TYPES)/sizeof(*THR_TYPES)

static int thresh_value;
static int thresh_type;
static int hough_threshold;
static int line_min_length;
static int line_max_gap;
static int mask_width_top;
static int mask_start_y;
static int mask_end_y;
static float thresh_angle_lane;
static float thresh_angle_stop;
static int max_lane_error;
static int lane_width_min;
static int lane_width_max;

static double weight_lw;
static double weight_lx;
static double weight_sd;
static int thresh_lane_vis;
static int thresh_stop_vis;
static int stop_dmax;

extern "C" struct ip *ip_init();
extern "C" void ip_destroy(struct ip *ip);
extern "C" void ip_set_opt(struct ip *ip, struct ip_opt *opt);
extern "C" void ip_process(struct ip *ip, struct ip_res *res);

struct ip {
    cv::VideoCapture *cap;
#ifdef RECORD
    cv::VideoWriter *writer;
#endif

    /* visibility data */
    cv::Point lane;
    cv::Point lane_dir;
    int lane_width;
    int lane_vis;

    cv::Point stop;
    int stop_diff;
    int stop_vis;

    /* ip options */
    struct ip_opt opt;
};

struct ip *ip_init() {
    struct ip *ip = (struct ip*)malloc(sizeof(*ip));

    ip->cap = new cv::VideoCapture(-1);

    if (!ip->cap->isOpened()) {
        std::cout << "Error: Camera not found\n";
        ip_destroy(ip);
        return NULL;
    }
  
    ip->cap->set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
    ip->cap->set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
    ip->cap->set(CV_CAP_PROP_FPS, 90);
    int fps = ip->cap->get(CV_CAP_PROP_FPS);
    WIDTH = ip->cap->get(CV_CAP_PROP_FRAME_WIDTH);
    HEIGHT = ip->cap->get(CV_CAP_PROP_FRAME_HEIGHT);

    printf("ip camera at %dx%d, fps: %d\n", WIDTH, HEIGHT, fps);

    thresh_value = 20;
    thresh_type = 6;
    hough_threshold = 7;
    line_min_length = 0;
    line_max_gap = 40;
    mask_width_top = 0.23*WIDTH;
    mask_start_y = 0.9*HEIGHT;
    mask_end_y = 0.52*HEIGHT;
    thresh_angle_lane = 0.4*CV_PI;
    thresh_angle_stop = 0.45*CV_PI;
    stop_dmax = 0.2*HEIGHT;

    weight_lw = 0.06;
    weight_lx = 0.8;
    weight_sd = 0.6;
    thresh_lane_vis = 5;
    thresh_stop_vis = 3;
    max_lane_error = 0.35*WIDTH;
    lane_width_min = 0.5*WIDTH;
    lane_width_max = 0.8*WIDTH;

    ip->lane = cv::Point(WIDTH/2, 0.8*HEIGHT);
    ip->lane_dir = cv::Point(0, 1);
    ip->lane_width = 0.8*WIDTH;
    ip->lane_vis = 0;

    ip->stop = cv::Point(WIDTH/2, mask_width_top);
    ip->stop_diff = 0;
    ip->stop_vis = 0;

    ip->opt = {0};

#ifdef VISUAL
    cv::namedWindow("Lane", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("", CV_WINDOW_AUTOSIZE);
#endif

#ifdef RECORD
    ip->writer = new cv::VideoWriter("opencv.avi",
        CV_FOURCC('M', 'J', 'P', 'G'),
        fps, cv::Size(WIDTH, HEIGHT));
#endif

    return ip;
}

void ip_set_opt(struct ip *ip, struct ip_opt *opt) {
    ip->opt = *opt;
}

void ip_destroy(struct ip *ip) {
#ifdef VISUAL
    cv::destroyAllWindows();
#endif

    if (ip) {
#ifdef RECORD
        ip->writer->release();
        delete ip->writer;
#endif
        ip->cap->release();
        delete ip->cap;
    }

    free(ip);
}

cv::Mat threshold(cv::Mat& image) {
    cv::Mat edge_img;
    cv::GaussianBlur(image, edge_img, cv::Size(3, 3), 0, 0);
    cv::cvtColor(edge_img, edge_img, cv::COLOR_RGB2GRAY);
    cv::threshold(edge_img, edge_img, thresh_value, 255,
                  THR_TYPES[thresh_type]);

    return edge_img;
}

cv::Mat img_edge_detector(cv::Mat& image) {
    cv::Mat edge_img;
    cv::Canny(image, edge_img, 100, 150, 3);

    return edge_img;
}

std::vector<cv::Point> create_mask() {
    /* region of interest */
    float top_y = mask_end_y;
    float top_rx = (WIDTH+mask_width_top)/2;
    float top_lx = (WIDTH-mask_width_top)/2;

    float bot_y = mask_start_y;
    float bot_lx = 0;
    float bot_rx = WIDTH;

    cv::Point p0(0, HEIGHT), p1(bot_lx, bot_y), p2(top_lx, top_y),
              p3(top_rx, top_y), p4(bot_rx, bot_y), p5(WIDTH, HEIGHT);
    std::vector<cv::Point> roi = {p0, p1, p2, p3, p4, p5};
    
    return roi;
}

cv::Mat mask_image(cv::Mat& image, std::vector<cv::Point> mask_poly) {
    cv::Mat masked_image;
    cv::Mat mask(cv::Mat::zeros(image.size(), image.type()));

    cv::fillConvexPoly(mask, mask_poly.data(), mask_poly.size(),
                       cv::Scalar(255, 0, 0));
    cv::bitwise_and(image, mask, masked_image);

    return masked_image;
}

bool intersects(cv::Point s1, cv::Point e1, cv::Point s2, cv::Point e2) {
    /*
    double t = ((s1.x-s2.x)*(s2.y-e2.y)-(s1.y-s2.y)*(s2.x-e2.x)) /
               ((s1.x-e1.x)*(s2.y-e2.y)-(s1.y-e1.y)*(s2.x-e2.x));
    */
    double denominator = (s1.x-e1.x)*(s2.y-e2.y)-(s1.y-e1.y)*(s2.x-e2.x);
    if (denominator != 0) {
        double numerator = (s1.x-e1.x)*(s1.y-s2.y)-(s1.y-e1.y)*(s1.x-s2.x);
        double u = -(numerator / denominator);
        return (u >= 0 && u <= 1);
    } else {
        return false;
    }
}

/* a*b = |a||b|cos v
 *           a*b
 * => v =  -------
 *          |a||b|
 */
double angle(int ax, int ay, int bx, int by) {
    double len_a = std::sqrt(ax*ax+ay*ay);
    double len_b = std::sqrt(bx*bx+by*by);
    double angle = acos((ax*bx+ay*by)/len_a/len_b);
    return std::min(angle, CV_PI-angle);
}

void classify_lines(struct ip *ip, lines_t& lines, cv::Mat& image,
                    lines_t& right_lines, lines_t& left_lines,
                    lines_t& stop_lines, lines_t& rem_lines) {
    cv::Point lane_top = ip->lane + ip->lane_dir;
    int c = ip->lane.x;
    for (auto line : lines) {
        cv::Point s(line[0], line[1]);
        cv::Point e(line[2], line[3]);
        double angle_to_lane = angle(e.x-s.x, e.y-s.y,
                                     ip->lane_dir.x, ip->lane_dir.y);
        if (!ip->opt.ignore_stop && angle_to_lane > thresh_angle_stop
                                 && intersects(ip->lane, lane_top, s, e)) {
            stop_lines.push_back(line);
        } else if (!ip->opt.ignore_right && angle_to_lane < thresh_angle_lane
                                         && e.x > c && s.x > c
                                         && (s.y >= ip->lane.y || e.y >= ip->lane.y)) {
            right_lines.push_back(line);
        } else if (!ip->opt.ignore_left && angle_to_lane < thresh_angle_lane
                                        && e.x < c && s.x < c
                                        && (s.y >= ip->lane.y || e.y >= ip->lane.y)) {
            left_lines.push_back(line);
        } else {
            rem_lines.push_back(line);
        }
    }
}

#ifdef VISUAL

void plot_lines(cv::Mat& img, lines_t right, lines_t left,
                              lines_t stop, lines_t rem) {
    for (auto l : rem) {
        cv::Point start(l[0], l[1]);
        cv::Point end(l[2], l[3]);
        cv::line(img, start, end, cv::Scalar(100, 100, 100), 1, CV_AA);
    }
    for (auto l : right) {
        cv::Point start(l[0], l[1]);
        cv::Point end(l[2], l[3]);
        cv::line(img, start, end, cv::Scalar(255, 0, 0), 1, CV_AA);
    }
    for (auto l : left) {
        cv::Point start(l[0], l[1]);
        cv::Point end(l[2], l[3]);
        cv::line(img, start, end, cv::Scalar(0, 255, 0), 1, CV_AA);
    }
    for (auto l : stop) {
        cv::Point start(l[0], l[1]);
        cv::Point end(l[2], l[3]);
        cv::line(img, start, end, cv::Scalar(0, 0, 255), 1, CV_AA);
    }
}

#endif

template<class T>
T median(std::vector<T> v) {
    int middle = v.size()/2;
    std::nth_element(v.begin(), v.begin()+middle, v.end());
    T median;
    if (v.size() % 2 == 0) {
        std::nth_element(v.begin(), v.begin()+middle+1, v.end());
        median = (v[middle-1]+v[middle])/2;
    } else {
        median = v[middle];
    }
    return median;
}

/* median x position of lines at y=height */
int line_pos_x(lines_t lines, int height) {
    if (lines.empty()) {
        return -1;
    } else {
        std::vector<int> pos;
        for (auto l : lines) {
            cv::Point s(l[0], l[1]), e(l[2], l[3]);
            if (s.x == e.x) {
                pos.push_back(s.x);
            } else if (s.y != e.y) {
                double k = (double)(e.y-s.y) / (e.x-s.x);
                double m = s.y-k*s.x;
                pos.push_back((int)((height-m)/k));
            }
        }
        return pos.empty() ? -1 : median(pos);
    }
}

/* median y position of lines at x=width */
int line_pos_y(lines_t lines, int width) {
    if (lines.empty()) {
        return -1;
    } else {
        std::vector<int> pos;
        for (auto l : lines) {
            cv::Point s(l[0], l[1]), e(l[2], l[3]);
            if (s.y == e.y) {
                pos.push_back(s.y);
            } else if (s.x != e.x) {
                double k = (double)(e.x-s.x) / (e.y-s.y);
                double m = s.x-k*s.y;
                pos.push_back((int)((width-m)/k));
            }
        }
        return pos.empty() ? -1 : median(pos);
    }
}

void ip_process(struct ip *ip, struct ip_res *res) {
    cv::Mat frame;
	ip->cap->read(frame);

	if (frame.empty()) {
	    std::cout << "Error: Empty frame\n";
	    return;
	}

    /* process image */
    cv::Mat thres_img = threshold(frame);
    cv::Mat edges_image = img_edge_detector(thres_img);
    /* mask proccessed image */
    std::vector<cv::Point> roi = create_mask();
    cv::Mat masked_image = mask_image(edges_image, roi);

    /* find and classify lines */
    lines_t hough_lines;
    cv::HoughLinesP(masked_image, hough_lines, 1, CV_PI/180,
                    hough_threshold, line_min_length, line_max_gap);

    lines_t right, left, stop, rem;
    classify_lines(ip, hough_lines, edges_image, right, left, stop, rem);

    /* calculate lane position */
    int lane_right_x = line_pos_x(right, ip->lane.y);
    int lane_left_x = line_pos_x(left, ip->lane.y);
    int lw;

    /* determine lane width, if lane visible */
    if (lane_right_x != -1 && lane_left_x != -1) {
        lw = lane_right_x - lane_left_x;
        ip->lane_vis++;
    } else {
        ip->lane_vis--;
    }
    lw = std::min(std::max(lane_width_min, lw), lane_width_max);
    ip->lane_width = (ip->lane_width +lw*weight_lw)/(1.0+weight_lw);

    /* limit visibility certainty */
    ip->lane_vis = std::min(std::max(0, ip->lane_vis), thresh_lane_vis*2);
    
    /* determine x position of lane */
    int lane_x = 0;
    if (lane_right_x != -1 && lane_left_x != -1) {
        lane_x = (lane_right_x + lane_left_x)/2;
    } else if (lane_right_x != -1) {
        lane_x = lane_right_x - ip->lane_width/2;
    } else if (lane_left_x != -1) {
        lane_x = lane_left_x + ip->lane_width/2;
    } else {
        lane_x = ip->lane.x;
    }
    lane_x = std::min(std::max(WIDTH/2-max_lane_error, lane_x),
                      WIDTH/2+max_lane_error);
    ip->lane.x = (ip->lane.x+lane_x*weight_lx)/(1.0+weight_lx);

    /* determine lane direction */
    if (!right.empty() || !left.empty())  {
        lines_t lane_lines;
        lane_lines.reserve(left.size() + right.size());
        lane_lines.insert(lane_lines.end(), right.begin(), right.end());
        lane_lines.insert(lane_lines.end(), left.begin(), left.end());
        int lane_top_x = line_pos_x(lane_lines, 0);
        lane_top_x = std::min(std::max(0, lane_top_x), WIDTH);

        ip->lane_dir = cv::Point(lane_top_x-ip->lane.x, -ip->lane.y);
    }

    /* calc stopline position */
    int stop_x = ip->lane.x + (ip->stop.y-ip->lane.y)/ip->lane_dir.y*ip->lane_dir.x;
    int stop_y = line_pos_y(stop, stop_x);

    if (stop_y != -1) {
        ip->stop_vis++;
        int diff = std::max(ip->stop.y-stop_y, 0);
        ip->stop_diff = (ip->stop_diff+diff*weight_sd)/(1+weight_sd);
    } else {
        ip->stop_vis--;
        stop_y = ip->stop.y + ip->stop_diff;
    }

    if (stop_y < mask_end_y || HEIGHT*1.2 <= stop_y) {
        stop_y = mask_end_y;
        ip->stop_diff = 0;
        ip->stop_vis = 0;
    }
    ip->stop = cv::Point(stop_x, stop_y);

    /* limit stopline visibility certainty */
    ip->stop_vis = std::min(std::max(ip->stop_vis, 0), thresh_stop_vis*2);

    /* write to result struct */
    res->lane_offset = (float)(ip->lane.x-WIDTH/2)/(max_lane_error);
    res->lane_right_visible = right.size() > 0;
    res->lane_left_visible = left.size() > 0;
    res->stopline_dist = 1-(float)ip->stop.y/HEIGHT; /* TODO calc in meters */
    res->stopline_visible = ip->stop_vis >= thresh_stop_vis;

#ifdef VISUAL
	static auto start_time = std::chrono::high_resolution_clock::now();
    auto stop_time = std::chrono::high_resolution_clock::now();
    double period = (double)(stop_time-start_time).count()/(1e9);
    start_time = stop_time;
	std::string fps = std::to_string((int)(1/period));
    std::string err = std::to_string(res->lane_offset);
    cv::putText(frame, fps, cv::Point(0,15), FONT, 1, cvScalar(0,0,0), 2);

    cv::putText(frame, err, cv::Point(0,30), FONT, 1, cvScalar(0,100,0), 2);

    plot_lines(frame, right, left, stop, rem);
    cv::polylines(frame, roi, true,
                  cv::Scalar(50, 50, 50));
    cv::line(frame,
             cv::Point(ip->lane.x - ip->lane_width/2, ip->lane.y),
             cv::Point(ip->lane.x + ip->lane_width/2, ip->lane.y),
             cv::Scalar(255,255,0), 1, CV_AA);
    cv::line(frame,
             cv::Point(ip->lane.x, ip->lane.y),
             cv::Point(ip->lane.x+ip->lane_dir.x, ip->lane.y+ip->lane_dir.y),
             cv::Scalar(0,255,255), 3, CV_AA);
    /*
    int stop_thick = res->stopline_found ? 3 : 1;
    cv::line(lines_img,
             cv::Point(lane_left_x, stop_left_y),
             cv::Point(lane_right_x, stop_right_y),
             cv::Scalar(255,0,255), stop_thick, CV_AA);
             */
    if (res->stopline_visible) {
        cv::circle(frame,
                cv::Point(ip->stop.x, ip->stop.y), 3,
                cv::Scalar(255, 0, 255), CV_FILLED);
    }
    cv::circle(frame,
             cv::Point(lane_left_x, ip->lane.y), 3,
             cv::Scalar(0,255,0), CV_FILLED);
    cv::circle(frame,
             cv::Point(lane_right_x, ip->lane.y), 3,
             cv::Scalar(255,0,0), CV_FILLED);

    cv::imshow("threshold", thres_img);
    cv::imshow("CannyEdges: ", edges_image);
    cv::imshow("mask", masked_image);
    cv::imshow("Lane", frame);

    cv::createTrackbar("b,bi,tr,z,zi,msk,otsu,tri", "", &thresh_type,
                       TRACK_MAX_THRESH, NULL);
    cv::createTrackbar("thresval", "", &thresh_value, TRACK_MAX, NULL);
    cv::createTrackbar("hougthres", "", &hough_threshold, TRACK_MAX, NULL);
    cv::createTrackbar("houghmin", "", &line_min_length, TRACK_MAX, NULL);
    cv::createTrackbar("houghgap", "", &line_max_gap, TRACK_MAX, NULL);
    cv::createTrackbar("mask_width_top", "", &mask_width_top, WIDTH, NULL);
    cv::createTrackbar("mask_start_y", "", &mask_start_y, HEIGHT, NULL);
    cv::createTrackbar("mask_end_y", "", &mask_end_y, HEIGHT, NULL);

    int k = cv::waitKey(1);
    if (k == 27) {
        ip_destroy(ip);
        exit(0);
    }
#endif

#ifdef RECORD
    ip->writer->write(frame);
#endif

}
