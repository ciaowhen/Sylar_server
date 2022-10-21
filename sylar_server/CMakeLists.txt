cmake_minimum_required(VERSION 3.23)
project(sylar_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(sylar_server main.cpp log/log.h)
