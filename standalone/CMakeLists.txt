cmake_minimum_required(VERSION 3.22)
project(
        GenogroveStandalone
        VERSION 0.1.0
        LANGUAGES CXX
)
SET(CMAKE_CXX_STANDARD 20)
message(STATUS "Building Standalone")

#-- - Import tools -- --
include(../cmake/tools.cmake)

#-- -- Dependencies -- --
include(../cmake/CPM.cmake)

#installation
CPMAddPackage(
        GITHUB_REPOSITORY jarro2783/cxxopts
        VERSION 3.2.0
        OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)
CPMAddPackage(NAME genogrove SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../library)

add_executable(genogrove-cli ${CMAKE_CURRENT_SOURCE_DIR}/genogrove/src/main.cpp)
target_link_libraries(genogrove-cli PRIVATE genogrove::genogrove cxxopts)
set_target_properties(genogrove-cli PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "genogrove")