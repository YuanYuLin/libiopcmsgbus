#ifndef UTILS_H
#define UTILS_H

int load_bind_configuration_from_file(struct bind_configuration_t *bind_configuration, char* configuration_path);
int init_bind_configuration(char *app_name, struct bind_configuration_t *bind_configuration);

#endif
