#include "cppliger/myclass.h"
#include "cppliger/myfunction.h"
#include "conversions.hpp"
#include <functional>
#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

template<typename F, typename... Args>
auto wrap_function_impl(F&& f, Args&&... args)
{
    using R = std::invoke_result_t<F, Args...>;
    if constexpr (std::is_void_v<R>)
    {
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    }
    else
    {
        auto result = std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        return toPyArray(std::move(result));
    }
}

// wrapper function for numpy
template<typename F, typename... Args>
auto wrap_function(F&& f, Args&&... args)
{
    return wrap_function_impl(std::forward<F>(f),
                              PyConversions::forwardToSpan(std::forward<Args>(args))...);
}


PYBIND11_MODULE(pyliger, m)
{
    namespace py = pybind11;

    py::add_ostream_redirect(m, "ostream_redirect");
    py::class_<cppliger::MyClass>(m, "MyClass")
            .def(py::init<double>())
            .def(py::init<double, double>())
            .def("Area", &cppliger::MyClass::Area, "Returns the are of MyClass");

    m.def("myfunction", &cppliger::myfunction);
    m.def(
            "vec_add",
            [](const pybind11::array_t<double>& a, const pybind11::array_t<double>& b) {
                return wrap_function(&cppliger::vec_add, a, b);
            },
            "Adds two arrays of same length elementwise");
    m.def(
            "vec_square_inplace",
            [](pybind11::array_t<double> a) {
                return wrap_function(&cppliger::vec_square_inplace, a);
            },
            "Squares elements of vector inplace");
}
