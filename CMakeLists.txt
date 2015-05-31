cmake_minimum_required(VERSION 3.2)
project(laba12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(laba12 ${SOURCE_FILES} helper.h)