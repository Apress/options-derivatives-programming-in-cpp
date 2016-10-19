//
//  BlackScholesPricer.cpp

#if 0  /// use -lQuantLib  to compile this
#include "BlackScholesPricer.hpp"

#include <ql/quantlib.hpp>

#include <ql/pricingengines/blackcalculator.hpp>


//
// The BlackScholesPricer class provides an interface to the ODEINT
// pricer component
//
class BlackScholesPricer {
public:
   BlackScholesPricer(bool call, double price, double strike, double tau, double r, double fr, double vol);
   BlackScholesPricer(const BlackScholesPricer &p);
   ~BlackScholesPricer();
   BlackScholesPricer &operator=(const BlackScholesPricer &p);

   double value();

   double delta();
   double gamma();
   double theta();
   double vega();
private:
   double m_price;
   double m_strike;
   double m_tau;
   double m_rate;
   double m_frate;
   double m_vol;
   double m_isCall;

   boost::shared_ptr<QuantLib::BlackScholesCalculator> m_calc;
};


BlackScholesPricer::BlackScholesPricer(bool call, double price, double strike, double tau, double r, double fr, double vol)
:m_price(price),
m_strike(strike),
m_tau(tau),
m_rate(r),
m_frate(fr),
m_vol(vol),
m_isCall(call)
{
   boost::shared_ptr<QuantLib::PlainVanillaPayoff>
      m_option (new QuantLib::PlainVanillaPayoff(call ? QuantLib::Option::Call : QuantLib::Option::Put, strike));

   // compute discount rates
   double cur_disc = std::exp(-m_rate  * m_tau);  // current discount rate
   double for_disc = std::exp(-m_frate * m_tau);  // foward  discount rate
   double stdev    = m_vol * std::sqrt(m_tau);    // standard deviation

   m_calc.reset(new QuantLib::BlackScholesCalculator(m_option, m_price, for_disc, stdev, cur_disc));
}

BlackScholesPricer::BlackScholesPricer(const BlackScholesPricer &p)
:m_price(p.m_price),
m_strike(p.m_strike),
m_tau(p.m_tau),
m_rate(p.m_rate),
m_frate(p.m_frate),
m_vol(p.m_vol),
m_isCall(p.m_isCall),
m_calc(p.m_calc)
{}

BlackScholesPricer::~BlackScholesPricer() {}

BlackScholesPricer &BlackScholesPricer::operator=(const BlackScholesPricer &p)
{
   if (this != &p)
   {
      m_price = p.m_price;
      m_strike = p.m_strike;
      m_tau = p.m_tau;
      m_rate = p.m_rate;
      m_frate = p.m_frate;
      m_vol = p.m_vol;
      m_isCall = p.m_isCall;
      m_calc = p.m_calc;
   }
   return *this;
}

double BlackScholesPricer::value()
{
   return m_calc->value();
}

double BlackScholesPricer::delta()
{
   return m_calc->delta();
}

double BlackScholesPricer::gamma()
{
   return m_calc->gamma();
}

double BlackScholesPricer::theta()
{
   return m_calc->theta(m_tau);
}

double BlackScholesPricer::vega()
{
   return m_calc->vega(m_tau);
}



#endif