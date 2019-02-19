cmake_minimum_required(VERSION 3.10)
project(protocol)

set(CMAKE_CXX_STANDARD 11)

add_executable(protocol src/main.cpp
               lib/src/protocol.cpp
               lib/include/protocol.h
               lib/src/lib.cpp
               lib/include/lib.h
               lib/src/rawData.cpp
               lib/include/rawData.h
               lib/src/ins_process.cpp
               lib/include/ins_process.h
               lib/src/vm.cpp
               lib/include/vm.h
               lib/include/function.h
               lib/src/funtion.cpp)
add_library(protocol_lib
            SHARED
            lib/src/protocol.cpp
            lib/include/protocol.h
            lib/src/lib.cpp
            lib/include/lib.h
            lib/src/rawData.cpp
            lib/include/rawData.h
            lib/src/ins_process.cpp
            lib/include/ins_process.h
            lib/src/vm.cpp
            lib/include/vm.h
            lib/include/function.h
            lib/src/funtion.cpp)

add_executable(run
               src/run.cpp
               lib/src/protocol.cpp
               lib/include/protocol.h
               lib/src/lib.cpp
               lib/include/lib.h
               lib/src/rawData.cpp
               lib/include/rawData.h
               lib/src/ins_process.cpp
               lib/include/ins_process.h
               lib/src/vm.cpp
               lib/include/vm.h
               lib/include/function.h
               lib/src/funtion.cpp)

add_executable(new
               src/new.cpp
               lib/src/protocol.cpp
               lib/include/protocol.h
               lib/src/lib.cpp
               lib/include/lib.h
               lib/src/rawData.cpp
               lib/include/rawData.h
               lib/src/ins_process.cpp
               lib/include/ins_process.h
               lib/src/vm.cpp
               lib/include/vm.h
               lib/include/function.h
               lib/src/funtion.cpp)

add_executable(car
               src/car_test.cpp
               lib/src/protocol.cpp
               lib/include/protocol.h
               lib/src/lib.cpp
               lib/include/lib.h
               lib/src/rawData.cpp
               lib/include/rawData.h
               lib/src/ins_process.cpp
               lib/include/ins_process.h
               lib/src/vm.cpp lib/include/vm.h
               lib/include/function.h
               lib/src/funtion.cpp)