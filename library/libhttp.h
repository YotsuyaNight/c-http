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
#include "statuses.h"

#define printerr(msg) fprintf(stderr, "ERROR: %s\n", msg);

/*
 * Structure cotaining one HTTP header (reqest/response) and pointer to next.
 */
struct httpheader {
        char *header;
        struct httpheader *next;
};

/*
 * Structure that contains http response elements.
 */
struct httpresponse {
        int responselength;
        char *status;
        int contentlength;
        struct httpheader *headers;
        char *body;
};

/*
 * Helper function that adds header to httpresonse struct.
 */
void httpaddheader(struct httpresponse *res, char *header);

/*
 * Clean up after httpresponse.
 */
void freehttpresponse(struct httpresponse *res);

/*
 * Binds socket for TCP communication to localhost with specific port.
 * Returns -1 on error, or a file descriptor for new socket
 */
int httpbindsocket(char *port);

/*
 * Returns a buffer containing response. 
 */
char* httpresponsebuild(struct httpresponse *res);
