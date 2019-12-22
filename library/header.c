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

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void httpaddheader(httpheader **headers, char *name, char *value)
{
        httpheader *newheader = malloc(sizeof(httpheader));
        newheader->name = malloc(sizeof(char) * strlen(name));
        strcpy(newheader->name, name);
        newheader->value = malloc(sizeof(char) * strlen(value));
        strcpy(newheader->value, value);
        newheader->next = NULL;
        httpheader **it = headers;
        while (*it != NULL) {
                it = &((*it)->next);
        }
        *it = newheader;
}

char* httpfindheader(httpheader *headers, char *name)
{
        httpheader *header = headers;
        while (headers != NULL) {
                if (strcmp(header->name, name) == 0)
                        return header->value;
                header = header->next;
        }
        return NULL;
}

/*
 * Helper function that frees memory allocated by headers list in reverse.
 */
void freehttpheaders(httpheader *header)
{
        if (header != NULL) {
                freehttpheaders(header->next);
                free(header->name);
                free(header->value);
                free(header);
        }
}
