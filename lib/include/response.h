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

#ifndef RESPONSE_H
#define RESPONSE_H

#include "statuses.h"
#include "header.h"

/*
 * Structure that contains http response elements.
 */
typedef struct {
        char *status;
        int contentlength;
        httpheader *headers;
        char *body;
} httpresponse;

/*
 * Helper function that adds header to httpresonse struct.
 */
void httpresponseaddheader(httpresponse *res, char *name, char *value);

/*
 * Clean up after httpresponse.
 */
void freehttpresponse(httpresponse *res);

/*
 * Returns a buffer containing response. 
 */
char* httpresponsebuild(httpresponse *res);

#endif
