
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include "file_transfer.h"
#include "connection.h"

int start_transfer_command(int fd, char *file_path){
    char buf[256];
    int bytes;
    bytes = sprintf(buf, "RETR %s\n", file_path);
    if (write(fd, buf, bytes) < 0) {
        perror("write()");
        return -1;
    }

    int code = 0;
    char message[1024];
    while(code != CODE_FILE_STATUS_OK){
        if(get_code(fd, &code, message) < 0){
            perror("get_code()");
            return -1;
        }
    }

    int file_size;
    sscanf(message, "%*[^(](%d", &file_size);
    printf("Sending file with size: %d\n", file_size);

    while(code != CODE_CLOSING_DATA_CONNECTION){
        if(get_code(fd, &code, message) < 0){
            perror("get_code()");
            return -1;
        }
    }

    return 0;
}

int receive_file(int fd, char *file_path){

    char *file_name = strrchr(file_path, '/');
    if (file_name == NULL){
        file_name = file_path;
    } else {
        file_name++;
    }

    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        perror("fopen()");
        return -1;
    }

    char buf[1024];
    int bytes;
    int total_bytes = 0;
    while ((bytes = read(fd, buf, sizeof(buf))) > 0){
        if (fwrite(buf, 1, bytes, file) < 0){
            perror("fwrite()");
            return -1;
        }
        total_bytes += bytes;
    }

    if (bytes < 0){
        perror("read()");
        return -1;
    }

    fclose(file);

    printf("File named '%s' received\n", file_name);
    printf("Bytes received: %d\n", total_bytes);
    return 0;
}