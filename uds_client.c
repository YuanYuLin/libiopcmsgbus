#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include "debug.h"
#include "iopcmsgbus.h"
#include "version.h"
#include "uds_client.h"
#include "utils.h"

int create_client(struct bind_configuration_t *bind_configuration)
{
    struct sockaddr_un sockaddr_client;
    int socketfd = -1;

    //Create client socket 
    socketfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(socketfd < 0) {
        debug_error("create socket error\n");
        return -1;
    }

    memset(&sockaddr_client, 0, sizeof(struct sockaddr_un));
    strcpy(sockaddr_client.sun_path, bind_configuration->bind_path);

    if(bind(socketfd, (struct sockaddr *)&sockaddr_client, sizeof(struct sockaddr_un)) < 0) {
        debug_error("bind socket error\n");
        return -1;
    }

    bind_configuration->socketfd = socketfd;
    return socketfd;
}

int send_message_to_peer(int socketfd, char* peer_path, struct iopcmsg_t *req, struct iopcmsg_t *res)
{
    size_t bytes = -1;
    struct sockaddr_un sockaddr_server;

    memset(&sockaddr_server, 0, sizeof(struct sockaddr_un));
    sockaddr_server.sun_family = AF_UNIX;
    strncpy(sockaddr_server.sun_path, peer_path, sizeof(sockaddr_server.sun_path) - 1);

    bytes = sendto(socketfd, req->data, req->data_len, 0, (struct sockaddr *) &sockaddr_server, sizeof(struct sockaddr_un));
    if(bytes != req->data_len) {
        debug_error("send_message: sendto error\n");
        return -1;
    }

    bytes = recvfrom(socketfd, res->data, BUFF_SIZE, 0, NULL, NULL);
    res->data_len = bytes;
    if(bytes < 0) {
        debug_error("send_message: recfrom error\n");
        return -1;
    }

    return bytes;
}

int send_message_to_router(int socketfd, struct iopcmsg_t *req, struct iopcmsg_t *res)
{
    struct bind_configuration_t bind_configuration;
    bind_configuration.type = UDS_ROUTER;
    init_bind_configuration(NULL, &bind_configuration);
    return send_message_to_peer(socketfd, (char*)&bind_configuration.bind_path, req, res);
}

int destroy_client(struct bind_configuration_t *bind_configuration)
{
    remove(bind_configuration->bind_path);
    close(bind_configuration->socketfd);
    return 0;
}
