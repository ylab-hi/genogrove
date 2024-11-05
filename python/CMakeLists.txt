cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(py_genogrove)

if (CMAKE_VERSION VERSION_LESS 3.18)
    set(DEV_MODULE Development)
else()
    set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.10 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "FIND PYTHON: ${Python_EXECUTABLE}")

#installation
CPMAddPackage(
        GITHUB_REPOSITORY wjakob/nanobind
        VERSION 2.2.0
)
CPMAddPackage(NAME genogrove SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../library)

nanobind_add_module(pygenogrove ext.cpp)
set_target_properties(pygenogrove PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "genogrove")
target_link_libraries(pygenogrove PUBLIC genogrove::genogrove)