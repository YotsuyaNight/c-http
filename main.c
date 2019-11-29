#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "libhttp.h"

int main(int argc, char *argv[])
{
        char buff[500];
        if (argc < 2) {
                fprintf(stderr, "usage: %s <port>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        int sfd = httpbindsocket(argv[1]);
        if (sfd == -1)
                exit(EXIT_FAILURE);
        for (;;) {
                memset(buff, 0, 500);
                printf("Awaiting request...\n");
                if (listen(sfd, 50)  == -1)
                        exit(EXIT_FAILURE);
                int session_fd = accept(sfd, 0, 0);
                printf("Received request!\n");
                read(session_fd, buff, 500);

                struct httpresponse res;
                res.status = HTTP_STATUS_200;
                res.contentlength = 500;
                res.body = buff;

                char *response = httpresponsebuild(&res);
                printf("Echoing following response:\n");
                printf(response);
                write(session_fd, response, strlen(response));
                free(response);
        }
        close(sfd);
        return 0;
}