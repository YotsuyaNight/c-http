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
#include <netdb.h>
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
                res.headers = NULL;
                res.status = HTTP_STATUS_200;
                res.contentlength = 46;
                res.body = "<html><body><p>Hello world!</p></body></html>";
                httpaddheader(&res, "Content-Type: text/html");
                char *response = httpresponsebuild(&res);

                printf("Echoing following response:\n");
                printf("%s\n", response);
                write(session_fd, response, strlen(response));

                freehttpresponse(&res);
                free(response);
        }
        close(sfd);
        return 0;
}