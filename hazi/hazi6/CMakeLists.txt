cmake_minimum_required(VERSION 3.25)
project(hazi6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -O2 -DTEST_BIRO=1 -Wall -Werror")

add_executable(hazi6 main.cpp)
