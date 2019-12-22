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

#include "methods.h" 
#include <string.h>

httpmethod httpstrtomethod(char *str)
{
        httpmethod method =  HTTP_UNKNOWN;
        if (strcmp(str, "GET") == 0)
                method =  HTTP_GET;
        else if (strcmp(str, "POST") == 0)
                method =  HTTP_POST;
        else if (strcmp(str, "PUT") == 0)
                method =  HTTP_PUT;
        else if (strcmp(str, "DELETE") == 0)
                method =  HTTP_DELETE;
        else if (strcmp(str, "OPTIONS") == 0)
                method =  HTTP_OPTIONS;
        return method;
}
