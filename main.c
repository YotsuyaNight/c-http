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

void gethandler(httprequest *req, httpresponse *res)
{
        res->headers = NULL;
        res->status = HTTP_STATUS_200;
        res->contentlength = 52;
        res->body = "<html><body><h1>GET Hello world!</h1></body></html>";
}

void posthandler(httprequest *req, httpresponse *res)
{
        res->headers = NULL;
        res->status = HTTP_STATUS_200;
        res->contentlength = 53;
        res->body = "<html><body><h1>POST Hello world!</h1></body></html>";
}

int main(int argc, char *argv[])
{
        httphandle(HTTP_GET, "/", &gethandler);
        httphandle(HTTP_POST, "/", &posthandler);

        int status = httplisten("8080");
        return status;
}
