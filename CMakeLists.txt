cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 11)

project(da_vinci_test_task C CXX)

set(sources main.cpp DaVinci_DataStruct.cpp)
set(headers DaVinci_DataStruct.h)

add_executable(da_vinci_test_task
               ${sources}
               ${headers})
