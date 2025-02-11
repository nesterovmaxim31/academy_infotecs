cmake_minimum_required(VERSION 3.19)

project(MultiThreadProg VERSION 1.0)


add_executable(start1 ./prog1/start.cc ./prog1/sockethandler.cc ./prog1/sender.cc)
add_executable(start2 ./prog2/start.cc ./prog2/receiver.cc)

target_compile_options(start1 PUBLIC -std=c++20 -Wall)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

