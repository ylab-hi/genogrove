cmake_minimum_required(VERSION 3.22)
project(IBPTree VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

file(GLOB SOURCES "src/*.cpp")
add_executable(IBPTree ${SOURCES})
target_include_directories(IBPTree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

