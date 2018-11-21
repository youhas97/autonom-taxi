#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include "bus.h"
#include "server.h"
#include "ip/img_proc.h"

#include "../spi/protocol.h"

#define SERVER_PORT_START 9000
#define SERVER_PORT_END 9100

#define SLAVE_SENS 7
#define SLAVE_CTRL 8

/* bus commands for ctrl */
struct bus_cmd BC_MAN =
    {BCB_MAN,     SLAVE_CTRL, sizeof(struct ctrl_frame_man)};
struct bus_cmd BC_ERR =
    {BCB_ERR,     SLAVE_CTRL, sizeof(struct ctrl_frame_err)};
struct bus_cmd BC_REG_VEL =
    {BCB_REG_VEL, SLAVE_CTRL, sizeof(struct ctrl_frame_reg)};
struct bus_cmd BC_REG_ROT =
    {BCB_REG_ROT, SLAVE_CTRL, sizeof(struct ctrl_frame_reg)};
struct bus_cmd BC_RST_CTRL =
    {BCB_RST,     SLAVE_CTRL, 0 };

/* bus commands for sens */
const struct bus_cmd BC_GET_SENS =
    {BCB_SENSORS, SLAVE_SENS, sizeof(struct sens_frame_data)};
const struct bus_cmd BC_RST_SENS =
    {BCB_RST,     SLAVE_CTRL, 0};

/* data from sensors stored on pi */
struct data_sensors {
    struct sens_frame_data f;
    
    pthread_mutex_t lock;
};

struct data_mission {
    bool active;

    /* TODO commands */
    int cmds_completed;
    int cmds_remaining;

    pthread_mutex_t lock;
};

struct data_rc {
    struct ctrl_frame_man man;

    pthread_mutex_t lock;
};

/* server commands, called by server on remote command */

bool sc_get_sens(struct srv_cmd_args *a) {
    struct data_sensors *sens_data = (struct data_sensors*)a->data1;

    /* read data */
    sens_dist_t df, dr;
    sens_odom_t dist;
    pthread_mutex_lock(&sens_data->lock);
    df = sens_data->f.dist_front;
    dr = sens_data->f.dist_right;
    dist = sens_data->f.distance;
    pthread_mutex_unlock(&sens_data->lock);

    /* create string */
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';
    rsp = str_append(rsp, &buf_size, "df=%d ", df);
    rsp = str_append(rsp, &buf_size, "dr=%d ", dr);
    rsp = str_append(rsp, &buf_size, "dist=%d", dist);

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

bool sc_set_bool(struct srv_cmd_args *a) {
    int success = true;
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';

    char* bool_str = a->args[1];
    bool value;

    switch (bool_str[0]) {
        case '0':
        case 'f':
        case 'F':
            value = false;
            break;
        case '1':
        case 't':
        case 'T':
            value = true;
            break;
        default:
            success = false;
    }

    if (success) {
        bool *dst = (bool*)a->data1;
        pthread_mutex_t *lock = (pthread_mutex_t*)a->data2;
        pthread_mutex_lock(lock);
        *dst = value;
        pthread_mutex_unlock(lock);
        success = true;
        rsp = str_append(rsp, &buf_size, "setting value to %d", value);
    } else {
        rsp = str_append(rsp, &buf_size,
                         "invalid argument -- \"%s\"", bool_str);
    }

    a->resp = rsp;
    return success;
}

bool sc_set_float(struct srv_cmd_args *a) {
    int success = false;
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';

    char* float_str = a->args[1];
    char *endptr;
    float value = strtof(float_str, &endptr);

    if (endptr > float_str) {
        float *dst = (float*)a->data1;
        pthread_mutex_t *lock = (pthread_mutex_t*)a->data2;
        pthread_mutex_lock(lock);
        *dst = value;
        pthread_mutex_unlock(lock);
        success = true;
        rsp = str_append(rsp, &buf_size, "setting value to %f", value);
    } else {
        rsp = str_append(rsp, &buf_size,
                         "invalid argument -- \"%s\"", float_str);
    }

    a->resp = rsp;
    return success;
}

bool sc_bus_send_floats(struct srv_cmd_args *a) {
    int success = false;
    int buf_size = 128;
    char *rsp = malloc(buf_size);
    rsp[0] = '\0';
    
    float values[2];
    char *endptr1, *endptr2;
    char* float1_str = a->args[1];
    char* float2_str = a->args[2];
    values[0] = strtof(float1_str, &endptr1);
    values[1] = strtof(float2_str, &endptr2);

    if (endptr1 > float1_str && endptr2 > float2_str) {
        success = true;
        struct bus_cmd *bc = (struct bus_cmd*)a->data1;
        bus_t *bus = (bus_t*)a->data2;
        bus_transmit_schedule(bus, bc, (unsigned char*)values, NULL, NULL);
        rsp = str_append(rsp, &buf_size, "sending values %f, %f",
                         values[0], values[1]);
    } else {
        rsp = str_append(rsp, &buf_size, "invalid arguments -- \"%s\"",
                         float1_str, float2_str);
    }

    a->resp = rsp;
    return success;
}

/* bus signal handlers, called by bus thread when transmission finished */

/* write received values to struct reachable from main thread */
void bsh_sens_recv(void *received, void *data) {
    struct sens_frame_data *frame = (struct sens_frame_data*)received;
    struct data_sensors *sens_data = (struct data_sensors*)data;
    
    pthread_mutex_lock(&sens_data->lock);
    sens_data->f = *frame;
    pthread_mutex_unlock(&sens_data->lock);
}

int main(int argc, char* args[]) {
    bool quit = false;
    pthread_mutex_t quit_lock;
    pthread_mutex_init(&quit_lock, 0);

    const char *inet_addr = args[1];
    if (!inet_addr) {
        fprintf(stderr, "error: no IP address specified\n");
        return EXIT_FAILURE;
    }

    struct data_sensors sens_data = {0};
    struct data_mission miss_data = {0};
    struct data_rc rc_data = {0};
    pthread_mutex_init(&sens_data.lock, 0);
    pthread_mutex_init(&miss_data.lock, 0);
    pthread_mutex_init(&rc_data.lock, 0);

    bus_t *bus = bus_create(F_SPI);
    if (!bus) return EXIT_FAILURE;

    struct srv_cmd cmds[] = {
    {"get_sensor",  0, &sens_data,        &sens_data.lock, *sc_get_sens},
    {"get_mission", 0, &miss_data,        &miss_data.lock, *sc_get_mission},
    {"set_mission", 1, &miss_data,        &miss_data.lock, *sc_set_mission},
    {"set_state",   1, &miss_data.active, &miss_data.lock, *sc_set_bool},
    {"shutdown",    1, &quit,             &quit_lock,      *sc_set_bool},
    {"set_vel",     1, &rc_data.man.vel,  &rc_data.lock,   *sc_set_float},
    {"set_rot",     1, &rc_data.man.rot,  &rc_data.lock,   *sc_set_float},
    {"set_reg_vel", 2, &BC_REG_VEL,       bus,             *sc_bus_send_floats},
    {"set_reg_rot", 2, &BC_REG_ROT,       bus,             *sc_bus_send_floats},
    };
    int cmdc = sizeof(cmds)/sizeof(*cmds);
    srv_t *srv = srv_create(inet_addr, SERVER_PORT_START, SERVER_PORT_END,
                            cmds, cmdc);
    if (!srv) return EXIT_FAILURE;

    /* remote ctrl values */

    char input[100];
    while (!quit) {
        /* pause loop, enable exit */
        int len = scanf("%s", input);
        if (len > 0 && input[0] == 'q') {
            pthread_mutex_lock(&quit_lock);
            quit = true;
            pthread_mutex_unlock(&quit_lock);
        }

        bus_receive_schedule(bus, &BC_GET_SENS, bsh_sens_recv, &sens_data);

        pthread_mutex_lock(&miss_data.lock);
        if (miss_data.active) {
            pthread_mutex_unlock(&miss_data.lock);

            struct ctrl_frame_err error = {0};
            /* TODO img proc + mission */
            bus_transmit_schedule(bus, &BC_ERR, (void*)&error, NULL, NULL);
        } else {
            pthread_mutex_unlock(&miss_data.lock);

            struct ctrl_frame_man manual;
            pthread_mutex_lock(&rc_data.lock);
            manual = rc_data.man;
            pthread_mutex_unlock(&rc_data.lock);
            bus_transmit_schedule(bus, &BC_MAN, (void*)&manual, NULL, NULL);
        }
    }

    srv_destroy(srv);
    bus_destroy(bus);

    return EXIT_SUCCESS;
}
