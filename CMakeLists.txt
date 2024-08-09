cmake_minimum_required(VERSION 3.22)
project(genogrove VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

##### genogrove library #####
#file(GLOB SOURCES "src/*.cpp")
#
##add_library(genogrove ${SOURCES})
##target_include_directories(genogrove PUBLIC
##        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
##        $<INSTALL_INTERFACE:include>
##)
#add_executable(genogrove ${SOURCES})
#target_include_directories(genogrove PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

##### Add GenoGrove as a library #####
file(GLOB SOURCES "src/*.cpp")
add_library(genogrove ${SOURCES})
target_include_directories(genogrove PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
include(GenerateExportHeader)
generate_export_header(genogrove)

set_target_properties(genogrove PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)


# install targets
install(TARGETS genogrove
        EXPORT genogrove-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(FILES include/genogrove.hpp DESTINATION include)
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN "genogrove.hpp" EXCLUDE
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/genogrove_export.h DESTINATION include)


export(EXPORT genogrove-targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/genogrove-targets.cmake"
        NAMESPACE genogrove::
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/genogrove-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

# create Config.cmake file
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/genogrove-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/genogrove-config.cmake"
        INSTALL_DESTINATION lib/cmake/genogrove
)

# generate and install cmake config files
install(EXPORT genogrove-targets
        FILE genogrove-targets.cmake
        NAMESPACE genogrove::
        DESTINATION lib/cmake/genogrove
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/genogrove-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/genogrove-config-version.cmake"
        DESTINATION lib/cmake/genogrove
)

##### Tests #####
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.0
)
FetchContent_MakeAvailable(googletest)
enable_testing() # enable the testing framework
include(GoogleTest)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(IBPTree_Test ${SOURCES} ${TEST_SOURCES})
target_include_directories(IBPTree_Test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(IBPTree_Test GTest::gtest_main)

gtest_discover_tests(IBPTree_Test)

