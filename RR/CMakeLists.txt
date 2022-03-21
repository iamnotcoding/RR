cmake_minimum_required(VERSION 3.10)

project(RR VERSION 0.9)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(RR STATIC process.c RR.c)

target_compile_options(RR PRIVATE -g3 -Wall -Wextra -pedantic-errors -O0)

