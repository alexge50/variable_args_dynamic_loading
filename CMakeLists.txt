cmake_minimum_required(VERSION 3.14)
project(variable_args_dynamic_loading)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(DynamicArguments INTERFACE)
target_include_directories(DynamicArguments INTERFACE include)

add_executable(variable_args_dynamic_loading test/main.cpp test/TypeRegister.h)
target_link_libraries(variable_args_dynamic_loading PRIVATE dl DynamicArguments)

add_library(module SHARED test/module.cpp test/TypeRegister.h)
target_link_libraries(module DynamicArguments)
target_compile_options(module PRIVATE -fvisibility=hidden)