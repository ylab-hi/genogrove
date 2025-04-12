#include <pybind11/pybind11.h>

namespace ggs = genogrove::structure;
namespace py = pybind11;
PYBIND11_MODULE(genogrove, m) {
    m.doc() = "GenoGrove Python bindings";

    py::class_<ggs::Grove>(m, "Grove")
            .def(py::init<int>())
            .def("insert", &ggs::Grove::insert)
            .def("search", &ggs::Grove::search)
            .def("__len__", &ggs::Grove::size)
            .def("__str__", [](const ggs::Grove& grove) {
                return "Grove(size=" + std::to_string(grove.size()) + ")";
            })
            .def("insert_many", [](ggs::Grove& g, py::iterable intervals) {
                for (py::handle h : intervals) {
                    auto interval = h.cast<ggs::Interval>();
                    g.insert(interval);
                }
            })
            ;

    py::class_<ggs::Interval>(m, "Interval")
            .def(py::init<std::string, int, int>())
            .def_property("chrom", &ggs::Interval::getChrom, &ggs::Interval::setChrom)
            .def_property("start", &ggs::Interval::getStart, &ggs::Interval::setStart)
            .def_property("end", &ggs::Interval::getEnd, &ggs::Interval::setEnd)
            .def("__str__", [](const ggs::Interval& i) {
                return i.getChrom() + ":" + std::to_string(i.getStart()) +
                "-" + std::to_string(i.getEnd());
            })
            ;
}