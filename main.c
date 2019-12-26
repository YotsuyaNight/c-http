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

#include "server.h"
#include "methods.h"
#include "dispatcher.h"
#include "unused.h"

void roothandler(httprequest *req, httpresponse *res)
{
        UNUSED(req);
        UNUSED(res);
        res->contentlength = 54;
        res->body = "<html><body><h1>This is root page!</h1></body></html>";
}

void helloworldhandler(httprequest *req, httpresponse *res)
{
        UNUSED(req);
        UNUSED(res);
        res->contentlength = 48;
        res->body = "<html><body><h1>Hello world!</h1></body></html>";
}

void posthandler(httprequest *req, httpresponse *res)
{
        UNUSED(req);
        UNUSED(res);
        res->contentlength = 53;
        res->body = "<html><body><h1>POST Hello world!</h1></body></html>";
}

void handler404(httprequest *req, httpresponse *res)
{
        UNUSED(req);
        UNUSED(res);
        res->status = HTTP_STATUS_404;
        res->contentlength = 54;
        res->body = "<html><body><h1>404 Page Not Found</h1></body></html>";
}

int main(int argc, char *argv[])
{
        UNUSED(argc);
        UNUSED(argv);

        httphandle(HTTP_GET, "/", &roothandler);
        httphandle(HTTP_GET, "/helloworld", &helloworldhandler);
        httphandle(HTTP_POST, "/", &posthandler);
        httphandle404(&handler404);

        int status = httplisten("8080");
        return status;
}
