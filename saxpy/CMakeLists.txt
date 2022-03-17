cmake_minimum_required(VERSION 3.10)
project(saxpy)

add_executable(saxpy main.cpp)

set(OpenACC_ACCEL_TARGET tesla)

find_package(OpenACC)
if(OpenACC_CXX_FOUND)
    target_link_libraries(saxpy PUBLIC OpenACC::OpenACC_CXX)
endif()