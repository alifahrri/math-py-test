#include "function.hpp"
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(function)
{
    class_<Function>("Function")
            .def_readwrite("x",&Function::x)
            .def_readwrite("y",&Function::y)
            ;

    class_<Derivative>("Derivative")
            .def_readwrite("x",&Derivative::x)
            .def_readwrite("dy",&Derivative::dy)
            ;
}
