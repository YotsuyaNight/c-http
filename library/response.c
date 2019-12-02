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
static void freehttpheaders(struct httpheader *header)
{
        if (header != NULL) {
                freehttpheaders(header->next);
                free(header);
        }
}

void freehttpresponse(struct httpresponse *res)
{
        freehttpheaders(res->headers);
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
