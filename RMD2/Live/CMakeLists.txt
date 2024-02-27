cmake_minimum_required(VERSION 3.5)
project(Logger)

add_library(LogMe src/LogMe.cpp include/LogMe/LogMe.hpp)
target_include_directories(LogMe PUBLIC include)

add_executable(main main.cpp)
target_link_libraries(main LogMe)