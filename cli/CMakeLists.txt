cmake_minimum_required(VERSION 3.22)
project(genogrove_cli VERSION 0.1.0)

add_executable(genogrove_cli ../src/main.cpp)
target_link_libraries(genogrove_cli genogrove)

# set the output directory for the executable
set_target_properties(genogrove_cli PROPERTIES
        OUTPUT_NAME genogrove
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)





