cmake_minimum_required(VERSION 3.14)
project(variable_args_dynamic_loading)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(variable_args_dynamic_loading test/main.cpp)
target_link_libraries(variable_args_dynamic_loading PRIVATE dl)
add_library(module SHARED test/module.cpp include/Arguments.h include/SymbolGen.h)
target_compile_options(module PRIVATE -fvisibility=hidden)