cmake_minimum_required(VERSION 3.10)

project(queue VERSION 0.9)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(queue STATIC queue.c)

target_compile_options(queue PRIVATE -g3 -Wall -Wextra -pedantic-errors -O1)



