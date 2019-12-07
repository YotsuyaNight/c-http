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
#include <netdb.h>
#include <errno.h>
#include "response.h"

void freehttpresponse(struct httpresponse *res)
{
        freehttpheaders(res->headers);
}

char* httpresponsebuild(struct httpresponse *res)
{
        int statussize, headerssize;

        statussize = strlen(res->status) + 1;

        char contentlength[32] = {0};
        sprintf(contentlength, "%d", res->contentlength);
        httpaddheader(&res->headers, "Content-Length", "46");

        headerssize = 0;
        struct httpheader **header = &(res->headers);
        if (*header == NULL)
                printf("NO HEADERS!!!!\n");
        while (*header != NULL) {
                headerssize += strlen((*header)->name)
                                + strlen((*header)->value)
                                + 3; // Newline and ': ' sequence
                header = &((*header)->next);
        }

        res->responselength = statussize + headerssize + 2 + res->contentlength + 1;
        char *buffer = malloc(sizeof(char) * res->responselength);

        strcpy(buffer, res->status);
        strcat(buffer, "\n");

        header = &(res->headers);
        if (*header == NULL)
                printf("NO HEADERS!!!!\n");
        while (*header != NULL) {
                strcat(buffer, (*header)->name);
                strcat(buffer, ": ");
                strcat(buffer, (*header)->value);
                strcat(buffer, "\n");
                header = &((*header)->next);
        }

        strcat(buffer, "\r\n");
        strcat(buffer, res->body);
        strcat(buffer, "\n");

        return buffer;
}
