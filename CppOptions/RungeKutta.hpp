//
//  RungeKutta.hpp

#ifndef RungeKutta_hpp
#define RungeKutta_hpp

#include "EulersMethod.hpp"

class RungeKuttaMethod {
public:
    RungeKuttaMethod(DEMathFunction &f);
    RungeKuttaMethod(const RungeKuttaMethod &p);
    ~RungeKuttaMethod();
    RungeKuttaMethod &operator=(const RungeKuttaMethod &p);
    double solve(int n, double x0, double y0, double c);
private:
    DEMathFunction &m_func;
};

#endif /* RungeKutta_hpp */
