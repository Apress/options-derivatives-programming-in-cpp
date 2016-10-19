//
//  Integration.hpp

#ifndef Integration_hpp
#define Integration_hpp

#include "MathFunction.hpp"

class SimpsonsIntegration {
public:
    SimpsonsIntegration(MathFunction &f);
    SimpsonsIntegration(const SimpsonsIntegration &p);
    ~SimpsonsIntegration();
    SimpsonsIntegration &operator=(const SimpsonsIntegration &p);

    double getIntegral(double a, double b);
    void setNumIntervals(int n);
private:
    MathFunction &m_f;
    int m_numIntervals;
};


#endif /* Integration_hpp */
