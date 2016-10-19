//
//  EulersMethod.cpp

#include "EulersMethod.hpp"


#include <iostream>

using std::cout;
using std::endl;


EulersMethod::EulersMethod(DEMathFunction &f)
: m_f(f)
{
}

EulersMethod::EulersMethod(const EulersMethod &p)
: m_f(p.m_f)
{
}

EulersMethod::~EulersMethod()
{
}

EulersMethod &EulersMethod::operator=(const EulersMethod &p)
{
    if (this != &p)
    {
        m_f = p.m_f;
    }
    return *this;
}

double EulersMethod::solve(int n, double x0, double y0, double c)
{
    // problem :   y' = f(x,y) ;  y(x0) = y0

    auto x = x0;
    auto y = y0;
    auto h = (c - x0)/n;

    cout << " h is " << h << endl;

    for (int i=0; i<n; ++i)
    {
        double F = m_f(x, y);
        auto G = m_f(x + h, y + h*F);

        cout << " F: " << F << " G: " << G << "";

        // update values of x, y
        x += h;
        y += h * (F + G)/2;

        cout << " x: " << x << " y: " << y << endl;
    }


    return y;
}

/// -----

namespace  {


class EulerMethodSampleFunction : public DEMathFunction {
public:
    double operator()(double x, double y);
};

double EulerMethodSampleFunction::operator()(double x, double y)
{
    return  3 * x + 2 * y + 1;
}

}

int main_euler()
{
    EulerMethodSampleFunction f;
    EulersMethod m(f);
    double res = m.solve (100, 0, 0.25, 2);
    cout << " result is " << res << endl;
    return 0;
}
