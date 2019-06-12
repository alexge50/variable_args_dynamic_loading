cmake_minimum_required(VERSION 3.8)
project(variable_args_dynamic_loading)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_library(DynamicArguments INTERFACE)
target_include_directories(DynamicArguments INTERFACE
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

install(
        TARGETS DynamicArguments
        EXPORT  DynamicArguments-config
)

install(
        EXPORT DynamicArguments-config
        NAMESPACE DynamicArguments::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DynamicArguments
)

install(
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/DynamicArguments
)

add_executable(variable_args_dynamic_loading test/main.cpp test/TypeRegister.h)
target_link_libraries(variable_args_dynamic_loading PRIVATE dl DynamicArguments)

add_library(module SHARED test/module.cpp test/TypeRegister.h)
target_link_libraries(module DynamicArguments)
target_compile_options(module PRIVATE -fvisibility=hidden)