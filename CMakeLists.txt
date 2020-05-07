cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
