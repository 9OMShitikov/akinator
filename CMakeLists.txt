cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

include_directories(auxilary_functions)

project(akinator)
add_executable(akinator main_sources/akinator.cpp auxilary_functions/my_stack.cpp 
               auxilary_functions/my_stack.h auxilary_functions/strings_read_functions.h 
               auxilary_functions/akinator_functions.h)

project(akinator-tree-print)
add_executable(akinator-tree-print main_sources/print_tree.cpp)
