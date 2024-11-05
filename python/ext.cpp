#include <nanobind/nanobind.h>
#include <genogrove/all.hpp>

int add(int a, int b) { return a + b; }

NB_MODULE(genogrove, m) {
    m.def("add", &add);
}