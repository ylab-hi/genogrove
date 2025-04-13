option(BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)
if(BUILD_PYTHON_BINDINGS)
    find_package(Python COMPONENTS Interpreter Development)
    include(FetchContent)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11
            GIT_TAG        v2.13.6
    )
    FetchContent_MakeAvailable(pybind11)
    add_subdirectory(python)
endif()

