cmake_minimum_required(VERSION 3.1.0)
project(filter)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(filter filter.cpp)