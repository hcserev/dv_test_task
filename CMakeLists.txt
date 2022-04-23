cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 11)

project(da_vinci_test_task C CXX)

set(sources main.cpp data_struct.cpp)
set(headers data_struct.h)

add_executable(da_vinci_test_task
               ${sources}
               ${headers})
