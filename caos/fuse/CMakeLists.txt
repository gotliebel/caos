cmake_minimum_required(VERSION 3.25)
project(fuse C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall")

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3)

link_libraries(${FUSE_LIBRARIES})         # -lfuse3 -lpthread
include_directories(${FUSE_INCLUDE_DIRS}) # -I/usr/include/fuse3
compile_options(${FUSE_CFLAGS_OTHER})
add_executable(fuse simplefs.c simplefs.c simplefs.c)
