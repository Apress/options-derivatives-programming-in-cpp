//
//  RungeKutta.cpp

#include "RungeKutta.hpp"


#include <iostream>

using std::cout;
using std::endl;

RungeKuttaMethod::RungeKuttaMethod(DEMathFunction &f)
: m_func(f)
{
}

RungeKuttaMethod::RungeKuttaMethod(const RungeKuttaMethod &p)
: m_func(p.m_func)
{
}

RungeKuttaMethod::~RungeKuttaMethod()
{
}

RungeKuttaMethod &RungeKuttaMethod::operator=(const RungeKuttaMethod &p)
{
    if (this != &p)
    {
        m_func = p.m_func;
    }
    return *this;
}

// Runge-Kutta method with fourth order approximation
//
double RungeKuttaMethod::solve(int n, double x0, double y0, double c)
{
    // initial conditions
    auto x = x0;
    auto y = y0;
    auto h = (c - x0)/n;

    for (int i=0; i<n; ++i)
    {
        // compute the intermediary steps
        //
        auto k1 = h * m_func(x, y);
        auto k2 = h * m_func(x + (h/2), y + (k1/2));
        auto k3 = h * m_func(x + (h/2), y + (k2/2));
        auto k4 = h * m_func(x + h, y + k3);

        // use terms to compute next step
        x += h;
        y += ( k1 + 2*k2 + 2*k3 + k4)/6;
        cout << " x: " << x << " y: " << y << endl;
    }

    return y;
}

/// -----

class RungeKuttaSampleFunc : public DEMathFunction {
public:

    double operator()(double x, double y);
};

double RungeKuttaSampleFunc::operator()(double x, double y)
{
    return  3 * x + 2 * y + 1;
}

int main_rkm()
{
    RungeKuttaSampleFunc f;
    RungeKuttaMethod m(f);
    double res = m.solve (100, 0, 0.25, 2);
    cout << " result is " << res << endl;
    return 0;
}



