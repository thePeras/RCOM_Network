#include "login.h"
#include "connection.h"

int login(int fd, char *username, char *password) {
    char buf[256];
    int bytes;
    int code = 0;
    char message[1024];

    //Check if already logged in
    if(get_code(fd, &code, message) < 0){
        perror("get_code()");
        return -1;
    }
    if(code == CODE_LOGGED_IN){
        printf("Already logged in\n");
        return 0;
    }

    if (username == NULL || password == NULL) {
        printf("Username and password must be provided\n");
        return -1;
    }

    bytes = sprintf(buf, "USER %s\n", username);
    if (write(fd, buf, bytes) < 0) {
        perror("write()");
        return -1;
    }

    while(code != CODE_USERNAME_OK){
        if(get_code(fd, &code, message) < 0){
            perror("get_code()");
            return -1;
        }
    }

    bytes = sprintf(buf, "PASS %s\n", password);
    if (write(fd, buf, bytes) < 0) {
        perror("write()");
        return -1;
    }

    while(code != CODE_LOGGED_IN){
        if(get_code(fd, &code, message) < 0){
            perror("get_code()");
            return -1;
        }
    }
    return 0;
}