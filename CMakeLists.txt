cmake_minimum_required(VERSION 3.10)
project(protocol)

set(CMAKE_CXX_STANDARD 11)

add_executable(protocol main.cpp protocol.cpp protocol.h type.h lib.cpp lib.h)