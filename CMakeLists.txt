cmake_minimum_required(VERSION 3.22)
project(IBPTree VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

##### IBPTree #####
file(GLOB SOURCES "src/*.cpp")
add_executable(IBPTree ${SOURCES})
target_include_directories(IBPTree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

##### Tests #####
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)
enable_testing() # enable the testing framework
include(GoogleTest)

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(IBPTree_Test ${SOURCES} ${TEST_SOURCES})
target_include_directories(IBPTree_Test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(IBPTree_Test GTest::gtest_main)
gtest_discover_tests(IBPTree_Test)
