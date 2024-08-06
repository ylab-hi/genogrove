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
#add_library(genogrove ${SOURCES})
#target_include_directories(genogrove PUBLIC
#        $<BUILD)


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

######## Install #######
#include(GNUInstallDirs)
#install(TARGETS genogrove
#        EXPORT ${PROJECT_NAME}Targets
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#install(EXPORT genogroveTargets
#        FILE ${PROJECT_NAME}Targets.cmake
#        NAMESPACE ${PROJECT_NAME}::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
#)
#install(DIRECTORY include/genogrove
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#
## Export package for use from the build tree
#export(EXPORT ${PROJECT_NAME}Targets
#        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
#        NAMESPACE ${PROJECT_NAME}::
#)



