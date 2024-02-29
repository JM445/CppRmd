cmake_minimum_required(VERSION 3.5)
project(RMD3)

set(CMAKE_CXX_STANDARD 20)

add_executable(main_stack main_stack.cpp)
target_include_directories(main_stack PUBLIC include)
