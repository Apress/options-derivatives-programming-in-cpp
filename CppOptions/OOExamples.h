//
//  OOExamples.hpp

#ifndef OOExamples_hpp
#define OOExamples_hpp

#include <string>
#include <iostream>
#include "Date.h"

class GeneralDerivative {

    virtual double strike();
private:
    double m_strike;
};


/// abstract classes

class AbstractDerivative {
public:
    virtual double calculatePriceAtExpiration() = 0;
    virtual void setExpiration(int year, int month, int day);
    virtual double getcurrentPrice() = 0;
};


class PartialDerivative {
public:
    PartialDerivative();
    virtual ~PartialDerivative();
    PartialDerivative(const PartialDerivative &p);
    PartialDerivative &operator=(const PartialDerivative &p);

private:

};

enum CDSUnderlying {
    CDSUnderlying_Bond,
    CDSUnderlying_Cash
};

class Date;
class MathIntegration;

class CDSContract {
public:
    CDSContract() {}
    CDSContract(MathIntegration *mipt);
    CDSContract(const CDSContract &p);
    virtual ~CDSContract() { std::cout << " base delete " << std::endl; }
    CDSContract &operator=(const CDSContract &p);

    std::string counterpart() { return m_counterpart; }
    void setCounterpart(const std::string &s);
    double payoff() { return m_payoff;   }
    void setPayoff(double payoff) { m_payoff = payoff; }
    virtual double computeCurrentValue(const Date &d);

    virtual void processCreditEvent() = 0;

private:
    std::string m_counterpart;
    CDSUnderlying m_underlying;
    double m_payoff;
    int m_term;
    double m_spreadCost;
    MathIntegration *m_mipt;

    static double kStandardPayoff;
};


class LoanOnlyCDSContract : public CDSContract {
public:
    LoanOnlyCDSContract() { std::cout << " derived class delete " << std::endl; }
    // constructors go here
    void changeLoanSource(const std::string &s);
    virtual double computeCurrentValue(const Date &d);

    virtual void processCreditEvent();

private:
    std::string m_loanSource;
};





#endif /* OOExamples_hpp */
