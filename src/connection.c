
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "connection.h"

int connect_to_host(char *host, char *port) {
    int socket_fd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    // DNS resolution
    if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        // open a TCP socket
        if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            perror("socket");
            continue;
        }

        // connect to the server
        if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(socket_fd);
            perror("connect()");
            continue;
        }

        // estalished connection successfully
        break; 
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to connect\n");
        return -1;
    }

    // just for printing purposes
    inet_ntop(p->ai_family, &(((struct sockaddr_in *)(p->ai_addr))->sin_addr), s, sizeof s);
    printf("Connected to %s\n", s);

    // free linked list
    freeaddrinfo(servinfo);

    return socket_fd;
} 

int get_code(int fd, int *code, char *message) {
    char buf[1024];
    int bytes;
    if ((bytes = read(fd, buf, 1024)) < 0) {
        perror("read()");
        return -1;
    }

    char temp_code[4];
    strncpy(temp_code, buf, 3);
    temp_code[3] = '\0';
    *code = atoi(temp_code);
    strcpy(message, buf + 4);

    return 0;
}