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

#ifndef STATUSES_H
#define STATUSES_H

#define HTTP_STATUS_100 "HTTP/1.1 100 Continue"
#define HTTP_STATUS_101 "HTTP/1.1 101 Switching Protocols"

#define HTTP_STATUS_200 "HTTP/1.1 200 OK"
#define HTTP_STATUS_201 "HTTP/1.1 201 Created"
#define HTTP_STATUS_202 "HTTP/1.1 202 Accepted"
#define HTTP_STATUS_203 "HTTP/1.1 203 Non-Authoritative Information"
#define HTTP_STATUS_204 "HTTP/1.1 204 No Content"
#define HTTP_STATUS_205 "HTTP/1.1 205 Reset Content"
#define HTTP_STATUS_206 "HTTP/1.1 206 Partial Content"

#define HTTP_STATUS_300 "HTTP/1.1 300 Multiple Choices"
#define HTTP_STATUS_301 "HTTP/1.1 301 Moved Permanently"
#define HTTP_STATUS_302 "HTTP/1.1 302 Found"
#define HTTP_STATUS_303 "HTTP/1.1 303 See Other"
#define HTTP_STATUS_304 "HTTP/1.1 304 Not Modified"
#define HTTP_STATUS_305 "HTTP/1.1 305 Use Proxy"
#define HTTP_STATUS_307 "HTTP/1.1 307 Temporary Redirect"

#define HTTP_STATUS_400 "HTTP/1.1 400 Bad Request"
#define HTTP_STATUS_401 "HTTP/1.1 401 Unauthorized"
#define HTTP_STATUS_402 "HTTP/1.1 402 Payment Required"
#define HTTP_STATUS_403 "HTTP/1.1 403 Forbidden"
#define HTTP_STATUS_404 "HTTP/1.1 404 Not Found"
#define HTTP_STATUS_405 "HTTP/1.1 405 Method Not Allowed"
#define HTTP_STATUS_406 "HTTP/1.1 406 Not Acceptable"
#define HTTP_STATUS_407 "HTTP/1.1 407 Proxy Authentication Required"
#define HTTP_STATUS_408 "HTTP/1.1 408 Request Time-out"
#define HTTP_STATUS_409 "HTTP/1.1 409 Conflict"
#define HTTP_STATUS_410 "HTTP/1.1 410 Gone"
#define HTTP_STATUS_411 "HTTP/1.1 411 Length Required"
#define HTTP_STATUS_412 "HTTP/1.1 412 Precondition Failed"
#define HTTP_STATUS_413 "HTTP/1.1 413 Request Entity Too Large"
#define HTTP_STATUS_414 "HTTP/1.1 414 Request-URI Too Large"
#define HTTP_STATUS_415 "HTTP/1.1 415 Unsupported Media Type"
#define HTTP_STATUS_416 "HTTP/1.1 416 Requested range not satisfiable"
#define HTTP_STATUS_417 "HTTP/1.1 417 Expectation Failed"

#define HTTP_STATUS_500 "HTTP/1.1 500 Internal Server Error"
#define HTTP_STATUS_501 "HTTP/1.1 501 Not Implemented"
#define HTTP_STATUS_502 "HTTP/1.1 502 Bad Gateway"
#define HTTP_STATUS_503 "HTTP/1.1 503 Service Unavailable"
#define HTTP_STATUS_504 "HTTP/1.1 504 Gateway Time-out"
#define HTTP_STATUS_505 "HTTP/1.1 505 HTTP Version not supported"

#endif
