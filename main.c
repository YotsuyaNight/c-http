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

#include "tcp.h"
#include "header.h"
#include "methods.h"
#include "dispatcher.h"
#include <string.h>

void customhandler(httprequest *req, httpresponse *res)
{
        char *str = malloc(sizeof(char) * 1024);
        strcat(str, req->path);
        printf("Hello '%s' from custom handler!\n", str);
        free(str);
}

void chainedcustomhandler(httprequest *req, httpresponse *res)
{
        char *str = malloc(sizeof(char) * 1024);
        strcat(str, req->path);
        printf("Hello '%s' from chained custom handler!\n", str);
        free(str);
}

int main(int argc, char *argv[])
{
        httphandle(HTTP_GET, "/", &customhandler);
        httphandle(HTTP_GET, "/", &chainedcustomhandler);
        int status = httplisten("8080");
        return status;
}
