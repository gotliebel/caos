cmake_minimum_required(VERSION 3.24)
project(threads C)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
tar
target_link_libraries(atomic.c PRIVATE Threads::Threads)

add_executable(threads atomic.c som.c another_atomic.c udalit'.c)
