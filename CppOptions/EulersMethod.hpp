//
//  EulersMethod.hpp

#ifndef EulersMethod_hpp
#define EulersMethod_hpp


class DEMathFunction  {
public:

    virtual ~DEMathFunction() {}
    virtual double operator()(double x, double y) = 0; // version with two variables
private:
    // this just an interface
};


class EulersMethod {
public:
    EulersMethod(DEMathFunction &f);
    EulersMethod(const EulersMethod &p);
    ~EulersMethod();
    EulersMethod &operator=(const EulersMethod &p);

    double solve(int n, double x0, double y0, double c);
private:
    DEMathFunction &m_f;
};


#endif /* EulersMethod_hpp */
