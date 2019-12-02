project(c_http_lib)

set(SOURCES
    libhttp.c
)

add_library(chttp ${SOURCES})

target_include_directories(chttp PUBLIC .)
