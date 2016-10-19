//
//  NewtonMethod.cpp

#include "NewtonMethod.hpp"


#include <iostream>
#include <cmath>

using std::endl;
using std::cout;

namespace {
    const double DEFAULT_ERROR = 0.0001;
}

NewtonMethod::NewtonMethod(MathFunction &f, MathFunction &derivative)
: m_f(f),
m_derivative(derivative),
m_error(DEFAULT_ERROR)
{
}

NewtonMethod::NewtonMethod(MathFunction &f, MathFunction &derivative, double error)
: m_f(f),
m_derivative(derivative),
m_error(error)
{
}

NewtonMethod::NewtonMethod(const NewtonMethod &p)
: m_f(p.m_f),
m_derivative(p.m_derivative),
m_error(p.m_error)
{
}

NewtonMethod::~NewtonMethod()
{
}

NewtonMethod &NewtonMethod::operator=(const NewtonMethod &p)
{
    if (this != &p)
    {
        m_f = p.m_f;
        m_derivative = p.m_derivative;
        m_error = p.m_error;
    }
    return *this;
}

double NewtonMethod::getFunctionRoot(double x0)
{
    double x1 = x0;
    do
    {
        x0 = x1;
        cout << " x0 is " << x0 << endl;  // this line just for demonstration
        double d = m_derivative(x0);
        double y = m_f(x0);
        x1 = x0 - y / d;
    }
    while (std::abs(x0 - x1) > m_error);
    return x1;
}

// ---- A function used as example

namespace {

    class SampleFunction : public MathFunction {
    public:
        virtual ~SampleFunction();
        virtual double operator()(double value);
    };

    SampleFunction::~SampleFunction()
    {
    }

    double SampleFunction::operator ()(double x)
    {
        return (x-1)*(x-1)*(x-1);
    }

    class Derivative : public MathFunction {
    public:
        virtual ~Derivative();
        virtual double operator()(double value);
    };

    // represents the derivative of the sample function
    Derivative::~Derivative()
    {
    }

    double Derivative::operator ()(double x)
    {
        return 3*(x-1)*(x-1);
    }
    
}

int main_newton()
{
    SampleFunction f;
    Derivative df;
    NewtonMethod nm(f, df);
    cout << " the root of the function is " << nm.getFunctionRoot(100) << endl;
    return 0;
}

