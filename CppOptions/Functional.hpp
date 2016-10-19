//
//  Functional.hpp

#ifndef Functional_hpp
#define Functional_hpp

class SimpleOption {
public:
   // other definitions here
   int daysToExpiration() const { return m_daysToExpiration; }

   double getInTheMoneyProbability(int numDays, double currentUnderlyingPrice) const ;
private:
   int m_daysToExpiration;
};


class OptionComparison {
public:
   OptionComparison(bool directionLess);
   OptionComparison(const OptionComparison &p);
   ~OptionComparison();
   OptionComparison &operator=(const OptionComparison &p);

   bool operator()(const SimpleOption &o1, const SimpleOption &o2);
private:
   bool m_directionLess;
};


#endif /* Functional_hpp */
