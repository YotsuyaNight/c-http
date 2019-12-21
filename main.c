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
#include <stdlib.h>
#include <stdio.h>

void helloworld(httprequest *req, httpresponse *res)
{
        res->headers = NULL;
        res->status = HTTP_STATUS_200;
        res->contentlength = 48;
        res->body = "<html><body><h1>Hello world!</h1></body></html>";
}

int main(int argc, char *argv[])
{
        httphandle(HTTP_GET, "/", &helloworld);
        int status = httplisten("8081");
        return status;
}
