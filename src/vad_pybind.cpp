//
// Created by Charles on 2022/9/5.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;
#include "vad.h"
PYBIND11_MODULE(vad_cpp, m) {
    m.doc() = "batch vad in c++";  // optional module docstring
//    py::class_<Vad>(m, "Vad").def(py::init(&Vad::init_vad))
//    py::class_<Vad>(m,"Vad").def("init_vad", &init_vad, py::return_value_policy::reference, "init_vad");
    m.def("init_vad", &init_vad, py::return_value_policy::reference);
    m.def("free_vad", &free_vad, "free_vad");
    m.def("process_vad", &process_vad);
}
