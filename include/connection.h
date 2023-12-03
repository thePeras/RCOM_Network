
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//  Positive Completion reply codes
#define CODE_SERVICE_READY 220
#define CODE_LOGGED_IN 230
#define CODE_PASSIVE_MODE 227

// Positive Intermediate reply codes
#define CODE_USERNAME_OK 331

int connect_to_host(char *host, char *port);
int get_code(int fd, int *code, char *message);