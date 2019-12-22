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

#include "dispatcher.h"
#include "methods.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Initialize global dispatcher to NULL
httpdispatcher dispatcher = {
        .get     = NULL,
        .post    = NULL,
        .put     = NULL,
        .delete  = NULL,
        .options = NULL
};

/*
 * Helper function to choose correct branch for given method
 */
static httproute** dispatcherbranch(httpmethod method) {
        httproute **branch;
        switch (method) {
                case HTTP_GET:
                        branch = &(dispatcher.get);
                        break;
                case HTTP_POST:
                        branch = &(dispatcher.post);
                        break;
                case HTTP_PUT:
                        branch = &(dispatcher.put);
                        break;
                case HTTP_DELETE:
                        branch = &(dispatcher.delete);
                        break;
                case HTTP_OPTIONS:
                        branch = &(dispatcher.options);
                        break;
                default:
                        branch = NULL;
        }
        return branch;
}

void httpdispatch(httprequest *req, httpresponse *res)
{
        httpmethod methodnum = httpstrtomethod(req->method);
        httproute **branch = dispatcherbranch(methodnum);
        while (*branch != NULL) {
                if (strcmp((*branch)->route, req->path) == 0) {
                        (*branch)->handler(req, res);
                        return;
                } 
                branch = &((*branch)->next);
        }
        http404errorhandler(req, res);
}

void httphandle(httpmethod method, char *route,
                void (*handler)(httprequest *req, httpresponse *res))
{
        // Add new entry to dispatcher
        httproute *newroute = malloc(sizeof(httproute));
        newroute->route = route;
        newroute->handler = handler;
        newroute->next = NULL;
        httproute **it = dispatcherbranch(method);
        while (*it != NULL) {
                it = &((*it)->next);
        }
        *it = newroute;
}

void (*http404errorhandler)(httprequest *req, httpresponse *res) = NULL;

void httphandle404(void (*handler)(httprequest *req, httpresponse *res))
{
        http404errorhandler = handler;
}
