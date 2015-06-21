#ifndef IOPCMSGBUS_H
#define IOPCMSGBUS_H

#define UDS_ROUTER_PATH "/tmp/uds_router"
#define UDS_SERVER_PATH "/tmp/uds_server_%s"
#define UDS_CLIENT_PATH	"/tmp/uds_client_%s"
#define JSON_CFG	"vmbus/vmbus.json"
#define BUFF_SIZE	(4096)

enum {
    UDS_UNKNOW,
    UDS_CLIENT,
    UDS_SERVER,
    UDS_ROUTER,
};

struct iopcmsg_t {
    int data_len;
    char data[BUFF_SIZE];
};

struct bind_configuration_t {
    unsigned int type;
    char bind_path[20];
    int socketfd;
};

#endif
