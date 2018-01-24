#include <iostream>
#include <fstream>
#include <QApplication>
#include "mainwindow.h"
#include "function.hpp"
#include "pythonembedded.hpp"

using namespace std;

#if PY_MAJOR_VERSION >= 3
#define INIT_MODULE PyInit_function
extern "C" PyObject* INIT_MODULE();
#else
#define INIT_MODULE initfunction
extern "C" void INIT_MODULE();
#endif

std::string read_file(const std::string& file_path)
{
    std::stringstream output;
    std::ifstream file;
    file.open(file_path.c_str());
    std::string line;
    while(std::getline(file,line))
        output << line << std::endl;
    return output.str();
}

void set_var(python_embed::py::dict& name_space, Function *f, Derivative *d)
{
    name_space["function"] = python_embed::py::ptr(f);
    name_space["derivative"] = python_embed::py::ptr(d);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;

    python_embed::init("function",&INIT_MODULE);

    Function f(1.0);
    Derivative d(1.0);

    std::string fn_script = read_file("function.py");
    std::string df_script = read_file("derivative.py");

    w.setFn_eval([&](double x)
    {
        f.x = x;
        set_var(python_embed::main_namespace, &f, &d);
        python_embed::run(fn_script,python_embed::main_namespace);
        return f.y;
    });

    w.setDf_eval([&](double x)
    {
        d.x = x;
        set_var(python_embed::main_namespace, &f, &d);
        python_embed::run(df_script,python_embed::main_namespace);
        return d.dy;
    });

    w.setFn_script([&](std::string script)
    {
        fn_script = script;
    });

    w.setDf_script([&](std::string script)
    {
        df_script = script;
    });

    w.show();

    return app.exec();
}
