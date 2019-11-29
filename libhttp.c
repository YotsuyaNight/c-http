#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "libhttp.h"

int httpbindsocket(char *port)
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

char* httpresponsebuild(struct httpresponse *res)
{
        int statussize, headersize;

        statussize = strlen(res->status);

        char clstr[32];
        sprintf(clstr, "%d", res->contentlength);
        char clheader[17+32+1];
        strcpy(clheader, "Content-Length: ");
        strcat(clheader, clstr);
        headersize = strlen(clheader);

        res->responselength = 
                statussize + 1 
                + headersize + 1 
                + 2  //CRLF
                + res->contentlength;
        char *buffer = malloc(sizeof(char) * res->responselength);

        strcpy(buffer, res->status);
        strcat(buffer, "\n");
        strcat(buffer, clheader);
        strcat(buffer, "\n\r\n");
        strcat(buffer, res->body);

        return buffer;
}
