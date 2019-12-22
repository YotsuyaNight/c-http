project(c_http_lib)

set(SOURCES
    tcp.c
    methods.c
    dispatcher.c
    header.c
    response.c
    request.c
)

add_library(chttp ${SOURCES})

target_include_directories(chttp PUBLIC .)
