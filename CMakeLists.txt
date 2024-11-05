cmake_minimum_required(VERSION 3.22)
project(genogrove_all VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Building all subprojects")
include(cmake/tools.cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(GENOGROVE_BUILD_STANDALONE "Build standalone" ON)
option(GENOGROVE_BUILD_PYTHON "Build python binding" ON)
option(GENOGROVE_BUILD_TESTS "Build tests" OFF)
option(GENOGROVE_BUILD_BENCHMARK "Build benchmark" OFF)
option(GENOGROVE_BUILD_DOCUMENTS "Build DOCUMENTS" OFF)

message(STATUS "Building standalone: ${GENOGROVE_BUILD_STANDALONE}")
message(STATUS "Building benchmark: ${GENOGROVE_BUILD_BENCHMARK}")
message(STATUS "Building python binding: ${GENOGROVE_BUILD_PYTHON}")
message(STATUS "Building tests: ${GENOGROVE_BUILD_TESTS}")
message(STATUS "Building documents: ${GENOGROVE_BUILD_DOCUMENTS}")

if(GENOGROVE_BUILD_STANDALONE)
    add_subdirectory(standalone ${CMAKE_BINARY_DIR}/standalone)
else()
    add_subdirectory(library ${CMAKE_BINARY_DIR}/library)
endif()

if (GENOGROVE_BUILD_BENCHMARK)
    add_subdirectory(benchmark ${CMAKE_BINARY_DIR}/benchmark)
endif()

if (GENOGROVE_BUILD_PYTHON)
    add_subdirectory(python ${CMAKE_BINARY_DIR}/python)
endif()

if(GENOGROVE_BUILD_TESTS)
    # needed to generate test target
    enable_testing()
    add_subdirectory(tests ${CMAKE_BINARY_DIR}/tests)
endif()