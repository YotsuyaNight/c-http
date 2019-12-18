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
#include <stdlib.h>

// Initialize global dispatcher to NULL
httproute *dispatcher = NULL;

void httphandle(char *method, char *route,
                void (*handler)(httprequest *req, httpresponse *res))
{
        // Add new entry to dispatcher
        httproute *newroute = malloc(sizeof(httproute));
        newroute->route = route;
        newroute->handler = handler;
        newroute->next = NULL;
        httproute **it = &dispatcher;
        while (*it != NULL) {
                it = &((*it)->next);
        }
        *it = newroute;
}
