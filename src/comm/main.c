#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include "bus.h"
#include "server.h"
#include "ip/img_proc.h"

#define SERVER_PORT_START 9000
#define SERVER_PORT_END 9100

#define SLAVE_SENS 10
#define SLAVE_CTRL 11

#define F_SPI 4000000

typedef uint8_t sens_dist_t;
typedef uint8_t sens_rot_t;
typedef float   reg_const_t;
typedef float   err_val_t;

/* format of data sent from sensor via bus */
struct sens_data_frame {
    sens_dist_t dist_front;
    sens_dist_t dist_right;
    sens_rot_t rotations;
};

/* flags for bus command;
 *  examples:
 *      write speed =   0000 0011 = 3
 *      write turn kp = 0000 0101 = 5 */
#define BF_WRITE 1
#define BF_SPEED 2
#define BF_REG   4
#define BF_KD    8

/* bus cmd bytes */
#define BCB_SPEED    BF_WRITE|BF_SPEED
#define BCB_SPEED_KD BF_WRITE|BF_SPEED|BF_REG|BF_KD
#define BCB_SPEED_KP BF_WRITE|BF_SPEED|BF_REG
#define BCB_TURN     BF_WRITE
#define BCB_TURN_KD  BF_WRITE|         BF_REG|BF_KD
#define BCB_TURN_KP  BF_WRITE|         BF_REG
#define BCB_GET_SENS 16
#define BCB_RESET    32

/* bus commands for ctrl */
struct bus_cmd BC_SPEED =    {BCB_SPEED,    SLAVE_CTRL, sizeof(err_val_t)};
struct bus_cmd BC_SPEED_KD = {BCB_SPEED_KD, SLAVE_CTRL, sizeof(reg_const_t)};
struct bus_cmd BC_SPEED_KP = {BCB_SPEED_KP, SLAVE_CTRL, sizeof(reg_const_t)};
struct bus_cmd BC_TURN =     {BCB_TURN,     SLAVE_CTRL, sizeof(err_val_t)};
struct bus_cmd BC_TURN_KD =  {BCB_TURN_KD,  SLAVE_CTRL, sizeof(reg_const_t)};
struct bus_cmd BC_TURN_KP =  {BCB_TURN_KP,  SLAVE_CTRL, sizeof(reg_const_t)};
struct bus_cmd BC_RST_CTRL = {BCB_RESET,    SLAVE_CTRL, 0 };

/* bus commands for sens */
const struct bus_cmd BC_GET_SENS = {BCB_GET_SENS, SLAVE_SENS,
    sizeof(struct sens_data_frame)};
const struct bus_cmd BC_RST_SENS = {BCB_RESET,    SLAVE_CTRL, 0};

/* data from sensors stored on pi */
struct data_sensors {
    sens_dist_t dist_front;
    sens_dist_t dist_right;
    unsigned rotations;
    
    pthread_mutex_t lock;
};

struct data_mission {
    bool active;

    /* TODO commands */
    int cmds_completed;
    int cmds_remaining;

    pthread_mutex_t lock;
};

/* server commands, called by server on remote command */

bool sc_get_sens(struct srv_cmd_args *a) {
    struct data_sensors *sens_data = (struct data_sensors*)a->data1;

    /* read data */
    sens_dist_t df, dr;
    unsigned rotations;
    pthread_mutex_lock(&sens_data->lock);
    df = sens_data->dist_front;
    dr = sens_data->dist_right;
    rotations = sens_data->rotations;
    pthread_mutex_unlock(&sens_data->lock);

    /* create string */
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';
    rsp = str_append(rsp, &buf_size, "df=%d ", df);
    rsp = str_append(rsp, &buf_size, "dr=%d ", dr);
    rsp = str_append(rsp, &buf_size, "rotations=%d", rotations);

    a->resp = rsp;
    return true;
}

bool sc_get_mission(struct srv_cmd_args *a) {
    struct data_mission *miss_data = (struct data_mission*)a->data1;

    /* read data */
    int cmp, rem;
    pthread_mutex_lock(&miss_data->lock);
    cmp = miss_data->cmds_completed;
    rem = miss_data->cmds_remaining;
    pthread_mutex_unlock(&miss_data->lock);

    /* create string */
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';
    rsp = str_append(rsp, &buf_size, "completed=%d ", cmp);
    rsp = str_append(rsp, &buf_size, "remaining=%d", rem);

    a->resp = rsp;
    return true;
}

bool sc_set_mission(struct srv_cmd_args *a) {
    return true;
}

bool sc_set_state(struct srv_cmd_args *a) {
    return true;
}

bool sc_bus_send_float(struct srv_cmd_args *a) {
    int success = false;
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';

    char *endptr;
    float value = strtof(a->args[0], &endptr);

    if (endptr > a->args[0]) {
        struct bus_cmd *bc = (struct bus_cmd*)a->data1;
        bus_t *bus = (bus_t*)a->data2;
        bus_transmit_schedule(bus, bc, (unsigned char*)&value, NULL, NULL);

        success = true;
        rsp = str_append(rsp, &buf_size, "sending value %f", value);
    } else {
        rsp = str_append(rsp, &buf_size,
                         "invalid argument -- \"%s\"", a->args[0]);
    }

    a->resp = rsp;
    return success;
}

/* bus signal handlers, called by bus thread when transmission finished */

/* write received values to struct reachable from main thread */
void bsh_sens_recv(unsigned char* received, void *data) {
    struct sens_data_frame *frame = (struct sens_data_frame*)received;
    struct data_sensors *sens_data = (struct data_sensors*)data;
    
    pthread_mutex_lock(&sens_data->lock);
    sens_data->dist_front = frame->dist_front;
    sens_data->dist_right = frame->dist_right;
    sens_data->rotations += frame->rotations;
    pthread_mutex_unlock(&sens_data->lock);
}

int main(int argc, char* args[]) {
    bool quit = false;

    const char *inet_addr = args[1];
    if (!inet_addr) {
        fprintf(stderr, "error: no IP address specified\n");
        return EXIT_FAILURE;
    }

    struct data_sensors sens_data = {0};
    struct data_mission miss_data = {0};
    pthread_mutex_init(&sens_data.lock, 0);
    pthread_mutex_init(&miss_data.lock, 0);

    bus_t *bus = bus_create(F_SPI);
    if (!bus) return EXIT_FAILURE;

    struct srv_cmd cmds[] = {
        {"shutdown",        0, &quit,        NULL, NULL},     /* TODO enable restart from remote */
        {"get_sensor_data", 0, &sens_data,   NULL, *sc_get_sens},
        {"get_mission",     0, &miss_data,   NULL, *sc_get_mission},
        {"set_mission",     1, NULL,         NULL, *sc_set_mission},  /* TODO */
        {"set_state",       1, NULL,         NULL, *sc_set_state},    /* TODO */
        {"set_speed_delta", 1, NULL,         bus,  NULL},             /* TODO */
        {"set_speed_kp",    1, &BC_SPEED_KP, bus,  *sc_bus_send_float},
        {"set_speed_kd",    1, &BC_SPEED_KD, bus,  *sc_bus_send_float},
        {"set_turn_delta",  1, NULL,         NULL, NULL},             /* TODO */
        {"set_turn_kp",     1, &BC_TURN_KP,  bus,  *sc_bus_send_float},
        {"set_turn_kd",     1, &BC_TURN_KD,  bus,  *sc_bus_send_float},
    };
    int cmdc = sizeof(cmds)/sizeof(*cmds);
    srv_t *srv = srv_create(inet_addr, SERVER_PORT_START, SERVER_PORT_END,
                            cmds, cmdc);
    if (!srv) return EXIT_FAILURE;

    char input[100];
    while (!quit) {
        bus_receive_schedule(bus, &BC_GET_SENS, bsh_sens_recv, &sens_data);

        /* TODO create storage for turn and speed, synchronize
        bus_transmit_schedule(bus, &BC_SPEED, speed);
        bus_transmit_schedule(bus, &BC_TURN, turn);
        */

        /* pause loop, enable exit */
        scanf("%s", input);
        if (input[0] == 'q')
            quit = true;

        pthread_mutex_lock(&sens_data.lock);
        printf("dist_front: %d, dist_right: %d, rotations: %d\n",
                sens_data.dist_front, sens_data.dist_right,
                sens_data.rotations);
        pthread_mutex_unlock(&sens_data.lock);

        /* TODO double err = ip_process() */
    }

    srv_destroy(srv);
    bus_destroy(bus);

    return EXIT_SUCCESS;
}
