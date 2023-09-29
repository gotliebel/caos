cmake_minimum_required(VERSION 3.23)
project(process C)

set(CMAKE_C_STANDARD 99)

add_executable(process third.c simple.c)
