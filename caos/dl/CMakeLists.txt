cmake_minimum_required(VERSION 3.25)
project(dl)
set(CMAKE_CXX_STANDARD 17)

add_executable(dl simple_dlopen.c interfaces.h)
