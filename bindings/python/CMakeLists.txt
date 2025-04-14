pybind11_add_module(pygenogrove src/bindings.cpp)
target_link_libaries(pygenogrove PRIVATE genogrove)
target_include_directoruies(pygenogrove PRIVATE ${CMAKE_SOURCE_DIR}/include)

