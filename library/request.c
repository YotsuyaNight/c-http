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

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "request.h"

/*
 * Reads stream until delimiter. Returns number of bytes read.
 */
static char* delimitedread(int fd, char delimiter)
{
        char tmpbuffer[1024] = {0};
        char *buffer;
        int i = 0;
        char byte = 0;
        for (;;) {
                read(fd, &byte, 1);
                if (byte == delimiter)
                        break;
                tmpbuffer[i] = byte;
                i++;
        }
        buffer = malloc(sizeof(char) * (i + 1));
        strcpy(buffer, tmpbuffer);
        return buffer;
}

httprequest httprequestparse(int sessionfd)
{
        httprequest req;
        req.headers = NULL;

        req.method = delimitedread(sessionfd, ' ');
        req.path = delimitedread(sessionfd, ' ');
        req.protocol = delimitedread(sessionfd, '\n');

        char *header;
        for (;;) {
                header = delimitedread(sessionfd, '\n');
                if (strcmp(header, "\r") == 0)
                        break;
                // Read header name and value
                char *name = strtok(header, ": ");
                char *value = strtok(NULL, ": ");
                httpaddheader(&req.headers, name, value);
                free(header);
        }

        return req;
}
