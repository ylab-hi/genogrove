cmake_minimum_required(VERSION 3.22)
project(genogrove_cli VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

set(CPM_DOWNLOAD_VERSION v0.40.2)
set(CPM_HASH_SUM "c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d")

if(NOT EXISTS ${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
    file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/download/${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
            EXPECTED_HASH SHA256=${CPM_HASH_SUM})
endif()
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

# add packages
CPMAddPackage(
        NAME cxxopts
        GITHUB_REPOSITORY jarro2783/cxxopts
        VERSION 3.2.0
        OPTIONS
            "CXXOPTS_BUILD_EXAMPLES OFF"
            "CXXOPTS_BUILD_TESTS OFF"
)
CPMAddPackage(
        NAME zlib
        GITHUB_REPOSITORY madler/zlib
        GIT_TAG v1.3.1
)

file(GLOB GG_LIB_SOURCES "../src/*.cpp")
file(GLOB GG_CLI_SOURCES "src/*.cpp")

add_executable(genogrove_cli ${GG_LIB_SOURCES} ${GG_CLI_SOURCES})
target_include_directories(genogrove_cli PUBLIC "${cxxopts_SOURCE_DIR}/include/") # cxxopts header files
target_include_directories(genogrove_cli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include/") # genogrove header files
target_include_directories(genogrove_cli PUBLIC include) # cli header files
target_link_libraries(genogrove_cli cxxopts zlibstatic)

# set the output directory for the executable
set_target_properties(genogrove_cli PROPERTIES
        OUTPUT_NAME genogrove
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)






