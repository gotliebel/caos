cmake_minimum_required(VERSION 3.25)
project(python C)

set(CMAKE_C_STANDARD 11)
find_package(PythonLibs 3.6 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(program ${PYTHON_LIBRARIES})

add_executable(python main.c)
