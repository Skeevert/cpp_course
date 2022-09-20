cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(my_allocator main.cpp)
set_target_properties(my_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

