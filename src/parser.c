#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

ParsedURL parse_url(char *url){
    ParsedURL components;
    memset(&components, 0, sizeof(components));

    components.port = "21";
    components.username = "anonymous";
    components.password = "anonymous";
    
    char *protocol = "ftp://";
    char *user_pass_delim = "@";
    char *host_port_delim = ":/";
    char *path_delim = "/";

    // Check if URL starts with 'ftp://'
    if (strncmp(url, protocol, strlen(protocol)) != 0) {
        printf("Invalid FTP URL format\n");
        return components;
    }

    url += strlen(protocol);

    // Find user and password if present
    char *userPassEnd = strstr(url, user_pass_delim);
    if (userPassEnd != NULL) {
        *userPassEnd = '\0';
        char *userPass = url;
        components.username = strtok(userPass, ":");
        components.password = strtok(NULL, user_pass_delim);
        url = userPassEnd + 1;
    }

    // Find host and port
    char *hostPortDelim = strpbrk(url, host_port_delim);
    if (hostPortDelim != NULL) {
        *hostPortDelim = '\0';
        components.host = url;
        url = hostPortDelim + 1;

        char *portStr = strchr(hostPortDelim + 1, ':');
        if (portStr != NULL) {
            *portStr = '\0';
            portStr++;
            components.port = portStr;
        }
    }

    // Find path
    components.path = strchr(url, *path_delim);
    if (components.path != NULL) {
        *components.path = '\0';
        components.path++;
    } else {
        printf("Invalid URL format: path not found\n");
        memset(&components, 0, sizeof(components)); // Reset components to zero/NULL
    }

    return components;
}
