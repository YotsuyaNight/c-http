#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define printerr(msg) fprintf(stderr, "ERROR: %s\n", msg);

int bindsocket(char *port)
{
        struct addrinfo hints;
        struct addrinfo *result, *rp;
        hints.ai_family = AF_INET; //IPv4
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; //Allow wildcards
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        int s = getaddrinfo("localhost", port, &hints, &result);
        if (s != 0) {
                printerr(gai_strerror(s));
                return -1;
        }
        int sfd = -1;
        for (rp = result; rp != NULL; rp = rp->ai_next) {
                sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
                if (sfd == -1)
                        continue;
                if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                        break;                  
                close(sfd);
        }
        if (rp == NULL) {
                printerr("Could not bind\n");
        }
        freeaddrinfo(result);
        return sfd;
}

int main(int argc, char *argv[])
{
        char buff[500];
        char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 11\n\r\n1111111111\n\n";
        if (argc < 2) {
                fprintf(stderr, "usage: %s <port>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        int sfd = bindsocket(argv[1]);
        if (sfd == -1)
                exit(EXIT_FAILURE);
        for (;;) {
                memset(buff, 0, 500);
                if (listen(sfd, 50)  == -1)
                        exit(EXIT_FAILURE);
                int session_fd = accept(sfd, 0, 0);
                read(session_fd, buff, 500);
                write(session_fd, response, strlen(response) - 1);
        }
        free(response);
        return 0;
}