#include "passive_mode.h"

int enter_passive_mode(int connection_fd, char *passive_host, char *passive_port) {
    char *passive_mode_command = "PASV\r\n";

    if (write(connection_fd, passive_mode_command, strlen(passive_mode_command)) < 0) {
        perror("write()");
        return -1;
    }

    int code = 0;
    char message[1024];
    while(code != CODE_PASSIVE_MODE){
        if(get_code(connection_fd, &code, message) < 0){
            perror("get_code()");
            return -1;
        }
    }

    uint8_t h1, h2, h3, h4, p1, p2;
    sscanf(message, "%*[^(](%hhu,%hhu,%hhu,%hhu,%hhu,%hhu)", &h1, &h2, &h3, &h4, &p1, &p2);

    sprintf(passive_host, "%hhu.%hhu.%hhu.%hhu", h1, h2, h3, h4);
    sprintf(passive_port, "%d", p1 * 256 + p2);

    return 0;
}