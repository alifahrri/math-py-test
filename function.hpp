#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>

struct Function
{
    Function(double x_) : x(x_) {}
    Function() {}
    double x;
    double y;
};

struct Derivative
{
    Derivative(double x_) : x(x_) {}
    Derivative() {}
    double x;
    double dy;
};


struct Function2
{
    double x1;
    double x2;
    double y;
};

struct Derivative2
{
    double x1;
    double x2;
    double y;
};

#endif // FUNCTION_HPP
