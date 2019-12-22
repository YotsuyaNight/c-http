## C "Zero-Dependency" HTTP1.1 Server
This project was created out of boredom, basically as a C exercise. It depends only on C Standard and POSIX libraries. Feel free to use this in production if you want, however I am not responsible for any damage it may cause.

### How To Use
First, you need to compile the library, then link your program against it. Alternatively, you can just use `main.cpp` embedded into this project.

### Minimal working example
```c
#include "tcp.h"
#include "methods.h"
#include "dispatcher.h"

void helloworld(httprequest *req, httpresponse *res)
{
        res->contentlength = 48;
        res->body = "<html><body><h1>Hello world!</h1></body></html>";
}

void error404(httprequest *req, httpresponse *res)
{
        res->status = HTTP_STATUS_404;
        res->contentlength = 54;
        res->body = "<html><body><h1>404 Page Not Found</h1></body></html>";
}

int main(int argc, char *argv[])
{
        httphandle(HTTP_GET, "/", &helloworld);
        httphandle404(&error404);

        int status = httplisten("8080");
        return status;
}
```
First, you define a handler (or a bunch of handlers). Handlers are functions that are called when specified request (identified by method and patrh) arrives. Handlers need to have specific signature:
```c
#include "request.h"
#include "response.h"
void handler(httprequest *req, httpresponse *res)
{
	// Logic goes here.
}
```
`req` and `res` are pointers to structures containing (surprisingly) request and response data. You should update `res` directly with data you want to return.

`httprequest` and `httpresponse` structures are defined as:
```c
#include "request.h"
typedef struct {
        char *method;
        char *path;
        char *protocol;
        httpheader *headers;
} httprequest;

#include "response.h"
typedef struct {
        char *status;
        int contentlength;
        httpheader *headers;
        char *body;
} httpresponse;
```
When setting value of `res.status`, use one of the defines from `statuses.h` file. These are simply strings concatenated to response buffer, so they look like this:
```c
#include "statuses.h"
// ...
#define HTTP_STATUS_200 "HTTP/1.1 200 OK"
#define HTTP_STATUS_201 "HTTP/1.1 201 Created"
#define HTTP_STATUS_202 "HTTP/1.1 202 Accepted"
// ...
```

//TODO: Write something about headers.

To register a handler, use following function:
```c
#include "dispatcher.h"
void httphandle(httpmethod method, char *route, void (*handler)(httprequest *req, httpresponse *res));
```
It accepts 3 parameters: `enum httpmethod`, representing method; `char*` representing route; pointer to handler function.

Function `httphandle404` is used to set handler for 404 errors (that is, when there is no handler registered for given request).

Finally, use `httplisten` function to enable listening on selected port. It enters infinite loop, waiting for connections and handling them according to handlers you set up.
