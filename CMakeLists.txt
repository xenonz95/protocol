cmake_minimum_required(VERSION 3.10)
project(protocol)

set(CMAKE_CXX_STANDARD 11)

include_directories(lib/include lib/src src)

set(libList
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

add_executable(protocol src/main.cpp ${libList})
add_library(protocol_lib SHARED ${libList})

add_executable(run src/run.cpp ${libList})

add_executable(new src/new.cpp ${libList})

add_executable(car src/car_test.cpp ${libList})

add_executable(simple src/simple_test.cpp ${libList})
add_executable(simple_send src/simple_send.cpp ${libList})
add_executable(simple2 src/simple_test2.cpp ${libList})
add_executable(vm_send src/vm_send.cpp ${libList})