#include <nanobind/nanobind.h>
#include <genogrove/all.hpp>

//https://nanobind.readthedocs.io/en/latest/basics.html

int add(int a, int b) { return a + b; }


NB_MODULE(genogrove, m) {
    m.def("add", &add);
}