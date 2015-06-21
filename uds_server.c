#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <errno.h>
#include "debug.h"
#include "iopcmsgbus.h"
#include "version.h"
#include "uds_server.h"
#include "utils.h"

static int init_socket(struct bind_configuration_t *bind_configuration)
{
    int socketfd;
    struct sockaddr_un sockaddr_server;

    //create socke
    socketfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(socket < 0) {
        debug_error("create socket error\n");
        return -1;
    }

    if (remove(bind_configuration->bind_path) < 0 && errno != ENOENT) {
        debug_error("remove socket path error : %s\n", bind_configuration->bind_path);
        return -1;
    }

    memset(&sockaddr_server, 0, sizeof(struct sockaddr_un));
    sockaddr_server.sun_family = AF_UNIX;
    strcpy(sockaddr_server.sun_path, bind_configuration->bind_path);

    if (bind(socketfd, (struct sockaddr *) &sockaddr_server, sizeof(struct sockaddr_un)) == -1) {
        debug_error("bind socket error\n");
        return -1;
    }
    bind_configuration->socketfd = socketfd;

    return socketfd;
}

static void process_message(struct iopcmsg_t *req, struct iopcmsg_t *res)
{
    
}

void create_server_loop(struct bind_configuration_t *bind_configuration)
{
    struct iopcmsg_t iopcmsg_req;
    struct iopcmsg_t iopcmsg_res;
    struct sockaddr_un sockaddr_client;
    int socketfd = -1;
    ssize_t bytes;
    socklen_t len;

    socketfd = init_socket(bind_configuration);

    if(socketfd < 0) {
        debug_error("Init socket error\n");
        return ;
    }

    while(1) {
        len = sizeof(struct sockaddr_un);
        bytes = recvfrom(socketfd, (void*)&iopcmsg_req.data, BUFF_SIZE, 0, (struct sockaddr *)&sockaddr_client, &len);

        if(bytes < 0) {
            debug_error("receive error\n");
        }

        process_message(&iopcmsg_req, &iopcmsg_res);

        bytes = sendto(socketfd, (void*)&iopcmsg_res.data, iopcmsg_res.data_len, 0, (struct sockaddr *) &sockaddr_client, len);
        if(bytes != sizeof(iopcmsg_res)) {
            debug_error("sendto error\n");
        }
    }
}

