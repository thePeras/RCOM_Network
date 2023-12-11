#define _POSIX_SOURCE 1
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "parser.h"
#include "connection.h"
#include "login.h"
#include "passive_mode.h"
#include "file_transfer.h"

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Usage: %s ftp://[<username>:<password>@]<host>[:<port>]/<url-path>\n", argv[0]);
    }

    ParsedURL components = parse_url(argv[1]);

    printf("username: %s\n", components.username);
    printf("password: %s\n", components.password);
    printf("host: %s\n", components.host);
    printf("port: %s\n", components.port);
    printf("path: %s\n", components.path);

    int connection_fd = connect_to_host(components.host, components.port);
    if (connection_fd < 0){
        perror("connect_to_server()");
        exit(-1);
    }

    if (login(connection_fd, components.username, components.password) < 0){
        perror("login()");
        exit(-1);
    }

    //enter passive mode
    char passive_host[INET_ADDRSTRLEN];
    char passive_port[6];
    if (enter_passive_mode(connection_fd, passive_host, passive_port) < 0){
        perror("enter_passive_mode()");
        exit(-1);
    }

    printf("passive_host: %s\n", passive_host);
    printf("passive_port: %s\n", passive_port);

    int passive_connection_fd = connect_to_host(passive_host, passive_port);
    if (passive_connection_fd < 0){
        perror("connect to passive server");
        exit(-1);
    }

    if (start_transfer_command(connection_fd, components.path) < 0){
        perror("send_retr()");
        exit(-1);
    }

    if (receive_file(passive_connection_fd, components.path) < 0){
        perror("receive_file()");
        exit(-1);
    }

    close(connection_fd);
    close(passive_connection_fd);
}