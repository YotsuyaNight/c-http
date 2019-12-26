cmake_minimum_required(VERSION 3.10.0)
project(cwebserver VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -pedantic)
set(DEFAULT_BUILD_TYPE "Release")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_RPATH .)

add_subdirectory(lib)

add_executable(server main.c)
target_link_libraries(server http)
