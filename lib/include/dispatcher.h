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

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "request.h"
#include "response.h"
#include "methods.h"

/*
 * Dispatch request to proper handler.
 */
void httpdispatch(httprequest *req, httpresponse *res);

/*
 * Register handler function for given route
 */
void httphandle(httpmethod method, char *route,
                void (*handler)(httprequest *req, httpresponse *res));

/*
 * Register handler for 404 error.
 */
void httphandle404(void (*handler)(httprequest *req, httpresponse *res));

#endif
