typedef struct {
    char *username;
    char *password;
    char *host;
    char *port;
    char *path;
} ParsedURL;

ParsedURL parse_url(char *url);