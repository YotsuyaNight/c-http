#include <stdio.h>

#define printerr(msg) fprintf(stderr, "ERROR: %s\n", msg);

#define HTTP_STATUS_200 "HTTP/1.1 200 OK"
#define HTTP_STATUS_404 "HTTP/1.1 404 Not Found"
#define HTTP_STATUS_500 "HTTP/1.1 500 Internal Server Error"

/*
 * Structure that contains http response elements.
 */
struct httpresponse {
        int responselength;
        char *status;
        int contentlength;
        char *body;
};

/*
 * Binds socket for TCP communication to localhost with specific port.
 * Returns -1 on error, or a file descriptor for new socket
 */
int httpbindsocket(char *port);

/*
 * Returns a buffer containing response. 
 */
char* httpresponsebuild(struct httpresponse *res);
