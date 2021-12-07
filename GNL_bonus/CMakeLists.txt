cmake_minimum_required(VERSION 3.19.2)
project(get_next_line C)

set(CMAKE_C_STANDARD 99)

set(BUFFER_SIZE 10)
add_executable(get_next_line main.c get_next_line_utils_bonus.c get_next_line_bonus.c)
#add_executable(get_next_line main.c)
