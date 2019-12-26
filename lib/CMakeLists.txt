cmake_minimum_required(VERSION 3.10.0)
project(chttp VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -pedantic)
set(DEFAULT_BUILD_TYPE "Release")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message("CMAKE_INSTALL_PREFIX not configured, assuming ${PROJECT_SOURCE_DIR}/bin")
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)
endif()

set(SOURCES
    src/server.c
    src/methods.c
    src/dispatcher.c
    src/header.c
    src/response.c
    src/request.c
)

add_library(http SHARED ${SOURCES})
target_include_directories(http PUBLIC include)
install(TARGETS http 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/http)
