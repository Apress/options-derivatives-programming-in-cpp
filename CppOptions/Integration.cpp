//
//  Integration.cpp

#include "Integration.hpp"


#include "MathFunction.hpp"

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

namespace  {
    const int DEFAULT_NUM_INTERVALS = 100;
}

SimpsonsIntegration::SimpsonsIntegration(MathFunction &f)
: m_f(f),
m_numIntervals(DEFAULT_NUM_INTERVALS)
{
}

SimpsonsIntegration::SimpsonsIntegration(const SimpsonsIntegration &p)
: m_f(p.m_f),
m_numIntervals(p.m_numIntervals)
{
}

SimpsonsIntegration::~SimpsonsIntegration()
{
}

SimpsonsIntegration &SimpsonsIntegration::operator=(const SimpsonsIntegration &p)
{
    if (this != &p)
    {
        m_f = p.m_f;
        m_numIntervals = p.m_numIntervals;
    }
    return *this;
}

double SimpsonsIntegration::getIntegral(double a, double b)
{
    double S = 0;
    double intSize = (b - a)/m_numIntervals;
    double x = a;

    for (int i=0; i<m_numIntervals; ++i)
    {
        S += (intSize / 6) * ( m_f(x) + m_f(x+intSize) + 4* m_f ((x + x+intSize)/2) );
        x += intSize;
    }
    return S;
}

void SimpsonsIntegration::setNumIntervals(int n)
{
    m_numIntervals = n;
}

// Example function

namespace  {

    class SampleFunc : public MathFunction
    {
    public:
        ~SampleFunc();
        double operator()(double x);
    };


    SampleFunc::~SampleFunc()
    {
    }

    double SampleFunc::operator()(double x)
    {
        return sin(x);
    }

}

int main_integ()
{
    SampleFunc f;
    SimpsonsIntegration si(f);
    si.setNumIntervals(4);
    double integral = si.getIntegral(0.5, 2.5);
    cout << " the integral of the function is " << integral << endl;

    si.setNumIntervals(100);
    integral = si.getIntegral(0.5, 2.5);
    cout << " the integral of the function with 200 intervals is " << integral << endl;
    return 0;
}
