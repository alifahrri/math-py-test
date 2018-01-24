#ifndef PYTHONEMBEDDED_HPP
#define PYTHONEMBEDDED_HPP

#include <vector>
#include <string>
#include <boost/python.hpp>

namespace python_embed {

namespace py = boost::python;

py::dict main_namespace;

void init(const std::string& module, void(*initfunc)())
{
    try
    {
        PyImport_AppendInittab(module.c_str(),initfunc);
        Py_Initialize();
        py::object main_module = py::import("__main__");

        main_namespace = py::extract<py::dict>(main_module.attr("__dict__"));

        py::import(module.c_str());
    }
    catch(py::error_already_set& e)
    {
        PyErr_PrintEx(0);
    }
}

void run(std::string script, py::dict namespace_)
{
    try
    {
        py::exec(script.c_str(),namespace_);
    }
    catch(py::error_already_set& e)
    {
        PyErr_PrintEx(0);
    }
}
}

#endif // PYTHONEMBEDDED_HPP
