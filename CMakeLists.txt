cmake_minimum_required(VERSION 3.0.0)
project(twmailer_basic VERSION 0.1.0)

include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB Sources "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_compile_options(-g -Wall -std=c++17)

add_executable(twmailer_basic ${Sources} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
