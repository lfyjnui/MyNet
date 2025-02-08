cmake_minimum_required(VERSION 3.12)

project(net)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party)
add_subdirectory(net)
add_subdirectory(test)
