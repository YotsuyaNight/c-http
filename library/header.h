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

#ifndef HEADER_H
#define HEADER_H

/*
 * Structure cotaining one HTTP header (reqest/response) and pointer to next.
 */
struct httpheader {
        char *name;
        char *value;
        struct httpheader *next;
};

/*
 * Appends new header to given header list.
 */
void httpaddheader(struct httpheader **headers, char *name, char *value);

/*
 * Returns value of specified header, or NULL if that header doesn't exist.
 */
char* httpfindheader(struct httpheader *headers, char *name);

/*
 * Frees memory allocated by headers list in reverse.
 */
void freehttpheaders(struct httpheader *header);


#endif
