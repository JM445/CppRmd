project(MyLog)
cmake_minimum_required(VERSION 3.14)

# Il faut éviter de faire ça, le faire par target normalement !
add_compile_options(-std=c++20)
include_directories(include)

add_executable(ex1 ex1.cpp src/LogMe.cpp include/LogMe/LogMe.hpp)
add_executable(ex2 ex2.cpp src/LogMe.cpp include/LogMe/LogMeContainer.hpp)
add_executable(ex4 ex4.cpp)
add_executable(ex6 ex6.cpp include/LogMe/LogMeStaticChain.hpp)