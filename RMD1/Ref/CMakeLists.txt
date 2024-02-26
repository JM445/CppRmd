project(MyLog)
cmake_minimum_required(VERSION 3.14)


add_library(LogMe src/LogMe.cpp include/LogMe/LogMe.hpp)
target_include_directories(LogMe PUBLIC include)
#set_target_properties(LogMe PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE LogMe)


# Part 4 solved

add_library(B B.cpp)
target_link_libraries(B PRIVATE LogMe)

add_library(C C.cpp)
target_link_libraries(C PRIVATE LogMe)

add_executable(A A.cpp)
target_link_libraries(A PRIVATE B C LogMe)