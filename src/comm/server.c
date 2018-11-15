#include "server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

/* starting size of buffer for received messages */
#define MSG_BUF_SIZE 2048

struct comm_item {
    srv_command_t command;
    char **args;
    int argc;
    struct comm_link *next;
};

struct server {
    int listen_fd; /* fd for socket that is listened to */

    pthread_t thread;

    struct {
        bool terminate;
        srv_command_t *comms;
        int commc;
        struct comm_item queue;
    } shared;
};

/* internal functions */

int accept_connection(int listen_fd, int conn_fd_prev, fd_set *fds) {
    int conn_fd = accept(listen_fd, NULL, NULL);
    if (conn_fd >= 0) {
        printf("accepted new connection %d, overwrite %d\n",
               conn_fd_prev, conn_fd);
        close(conn_fd_prev);
        FD_CLR(conn_fd_prev, fds);
        FD_SET(conn_fd, fds);
    } else {
        conn_fd = conn_fd_prev;
    }
    return conn_fd;
}

/* string returned must be freed by caller */
char *receive(int conn_fd) {
    int bufsize = MSG_BUF_SIZE;
    char *buf = malloc(bufsize*sizeof(char));
    int length = 0;

    if (conn_fd >= 0) {
        int max_receive;
        int received = 0;

        do {
            if (length >= bufsize) {
                bufsize *= 2;
                buf = realloc(buf, bufsize+1);
            }
            max_receive = bufsize-length;
            received = recv(conn_fd, buf+length, max_receive, 0);
            length += received;
        } while (received == max_receive);
    }

    if (length == 0) {
        free(buf);
        buf = NULL;
    } else {
        buf[length] = '\0';
    }

    return buf;
}

void parse_command(struct server *srv, char *unparsed, struct comm_item *ci) {
    char *copy;
    /* TODO parse:
     *  -command index
     *  -argcount
     *  -list of args
     */
}

void *srv_thread(void *server) {
    struct server *srv = (struct server*)server;
    bool quit = false;
    int conn_fd = -1;

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(srv->listen_fd, &rfds);
    
    while (!quit) {
        /* sleep until connect or receive request */
        int nfds = MAX(srv->listen_fd, conn_fd)+1;
        select(nfds, &rfds, NULL, NULL, NULL);
        printf("server woken up\n");

        /* accept if requested */
        conn_fd = accept_connection(srv->listen_fd, conn_fd, &rfds);

        /* process command if received */
        char *msg = receive(conn_fd);
        if (msg) {
            char **args;
            int argc;
            struct comm_item *ci;
            parse_command(srv, msg, ci);
            //srv_command_t command = ci->command;

            /* TODO create response */
            //char *response;
            send(conn_fd, "hej", 3, 0);
            
            printf("msg: %s\n", msg);
        }
        free(msg);
    }

    close(conn_fd);
    pthread_exit(NULL);
}

/* external api functions */
struct server *srv_create(const char *addr, int port){
    int succ;

    struct server *srv = calloc(1, sizeof(struct server));
    srv->shared.terminate = false;

    srv->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (srv->listen_fd == -1) {
        perror("failed to create unbound socket");
        goto fail;
    }

    /* ensure no blocking when accepting connections */
    fcntl(srv->listen_fd, F_SETFL, O_NONBLOCK); 

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, addr, &address.sin_addr);

    succ = bind(srv->listen_fd, (struct sockaddr*)&address, sizeof(address));
    if (succ == -1) {
        perror("failed to bind socket");
        goto fail;
    }

    succ = listen(srv->listen_fd, 10);
    if (succ == -1) {
        perror("failed to listen to socket");
        goto fail;
    }

    pthread_create(&srv->thread, NULL, srv_thread, (void*)(srv));

    return srv;
fail:
    srv_destroy(srv);
    return NULL;
}

void srv_destroy(struct server *srv) {
    if (srv->listen_fd > 0) close(srv->listen_fd);
    free(srv);
}
