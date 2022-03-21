cmake_minimum_required(VERSION 3.10)

project(main VERSION 0.9)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(RR)
add_subdirectory(queue)

add_executable(main main.c)

target_link_libraries(main RR)
target_link_libraries(main queue)

target_compile_options(main PRIVATE -g3 -Wall -Wextra -pedantic-errors -O0)