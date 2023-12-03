#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "connection.h"

int enter_passive_mode(int connection_fd, char *passive_host, char *passive_port);