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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "tcp.h"
#include "response.h"
#include "request.h"
#include "dispatcher.h"

static int httpbindsocket(char *port)
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

int httplisten(char *port)
{
        int sfd = httpbindsocket(port);
        if (sfd == -1)
            return -1;
                
        for (;;) {
                httprequest req;
                httpresponse res;

                // Assign default values
                res.headers = NULL;
                res.status = HTTP_STATUS_200;
                res.body = "";
                res.contentlength = 0;

                if (listen(sfd, 50)  == -1)
                        return -1;

                printf("Awaiting request...\n");

                int sessionfd = accept(sfd, 0, 0);
                printf("Received request!\n");
                req = httprequestparse(sessionfd);
                printf("METHOD: %s\n", req.method);
                printf("PATH: %s\n", req.path);
                printf("PROTOCOL: %s\n", req.protocol);
                printf("HEADERS:\n");
                httpheader **header = &(req.headers);
                while (*header != NULL) {
                        printf("%s: %s\n", (*header)->name, (*header)->value);
                        header = &((*header)->next);
                }
                printf("\n");

                // Delegate request and response to dispatcher
                httpdispatch(&req, &res);

                // Build response buffer
                char *response = httpresponsebuild(&res);

                // printf("Echoing following response:\n");
                // printf("%s\n", response);
                write(sessionfd, response, strlen(response));

                freehttpresponse(&res);
                free(response);
        }
        close(sfd);

        return 0;
}
