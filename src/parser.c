#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

ParsedURL parse_url(char *url) {
    ParsedURL components;
    memset(&components, 0, sizeof(components));

    components.port = "21";
    components.username = "anonymous";
    components.password = "anonymous";

    char *protocol = "ftp://";
    char *user_pass_delim = "@";
    char *host_port_delim = ":";
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

    // Find host and port if present
    char *hostEnd = strstr(url, host_port_delim);
    if (hostEnd != NULL) {
        *hostEnd = '\0';
        components.host = url;
        url = hostEnd + 1;
        components.port = strtok(url, path_delim);
        url = components.port + strlen(components.port) + 1;
    } else {
        hostEnd = strstr(url, path_delim);
        if (hostEnd != NULL) {
            *hostEnd = '\0';
            components.host = url;
            url = hostEnd + 1;
        } else {
            printf("Invalid URL format: host not found\n");
            memset(&components, 0, sizeof(components)); // Reset components to zero/NULL
            return components;
        }
    }

    components.path = url;

    return components;
}