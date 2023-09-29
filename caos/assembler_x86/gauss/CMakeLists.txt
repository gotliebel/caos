cmake_minimum_required(VERSION 3.23)
project(gauss C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")
add_executable(gauss main.c)
