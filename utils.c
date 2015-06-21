#include <string.h>
#include "iopcmsgbus.h"

static int get_bind_path_client(char* bind_path)
{
    strcpy(bind_path, "UDS_CLIENT");
    return 0;
}

static int get_bind_path_server(char* bind_path)
{
    strcpy(bind_path, "UDS_SERVER");
    return 0;
}

static int get_bind_path_router(char* bind_path)
{
    strcpy(bind_path, "UDS_ROUTER");
    return 0;
}

int load_bind_configuration_from_file(struct bind_configuration_t *bind_configuration, char* configuration_path)
{
    return 0;    
}

int init_bind_configuration(char *app_name, struct bind_configuration_t *bind_configuration)
{
    int type = bind_configuration->type;

    if(type == UDS_CLIENT) {
        get_bind_path_client((char*)&bind_configuration->bind_path);
    }

    if(type == UDS_SERVER) {
        get_bind_path_server((char*)&bind_configuration->bind_path);
    }

    if(type == UDS_ROUTER) {
        get_bind_path_router((char*)&bind_configuration->bind_path);
    }
    return 0;
}
