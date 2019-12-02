/* 
 * This file is part of "C-Http" program (https://github.com/YotsuyaNight/c-http)
 * Copyright (c) 2019 Marcin Dłubakowski.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "libhttp.h"

void httpaddheader(struct httpresponse *res, char *header)
{
        struct httpheader *headerstruct = malloc(sizeof(struct httpheader));
        headerstruct->header = header;
        headerstruct->next = NULL;
        struct httpheader **it = &(res->headers);
        while (*it != NULL) {
                it = &((*it)->next);
        }
        *it = headerstruct;
}

/*
 * Helper function that frees memory allocated by headers list in reverse.
 */
static void freehttpheader(struct httpheader *header)
{
        if (header != NULL) {
                freehttpheader(header->next);
                free(header);
        }
}

void freehttpresponse(struct httpresponse *res)
{
        freehttpheader(res->headers);
}

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
        int statussize, headerssize;

        statussize = strlen(res->status) + 1;

        char clstr[32];
        sprintf(clstr, "%d", res->contentlength);
        char *clheader = malloc(sizeof(char) * (17+32+1));
        strcpy(clheader, "Content-Length: ");
        strcat(clheader, clstr);
        httpaddheader(res, clheader);

        headerssize = 0;
        struct httpheader **header = &(res->headers);
        while (*header != NULL) {
                headerssize += strlen((*header)->header) + 1;
                header = &((*header)->next);
        }

        res->responselength = statussize + headerssize + 2 + res->contentlength + 1;
        char *buffer = malloc(sizeof(char) * res->responselength);

        strcpy(buffer, res->status);
        strcat(buffer, "\n");

        header = &(res->headers);
        while (*header != NULL) {
                strcat(buffer, (*header)->header);
                strcat(buffer, "\n");
                header = &((*header)->next);
        }

        strcat(buffer, "\r\n");
        strcat(buffer, res->body);
        strcat(buffer, "\n");

        return buffer;
}
