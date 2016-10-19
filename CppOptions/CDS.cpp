//
//  CDS.cpp

#if 0

#include "CDS.h"

#include <iostream>

// include classes from QuantLib
#include <ql/instruments/creditdefaultswap.hpp>
#include <ql/instruments/barrieroption.hpp>
#include <ql/quotes/SimpleQuote.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/exercise.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>
#include <ql/pricingengines/barrier/fdblackscholesbarrierengine.hpp>

using namespace QuantLib;

using std::cout;
using std::vector;
using std::pair;

using boost::shared_ptr;



CDSSolver::CDSSolver(double val, double sigma, double divYield, double rf,
                     double strike, double barrier, double rebate)
:
   cur_val(val),
   sigma(sigma),
   divYield(divYield),
   rf(rf),
   strike(strike),
   barrier(barrier),
   rebate(rebate)
{
}

// solve the valuation problem using the barrier technique, from today to the maturity date
pair<BarrierOption, BlackScholesMertonProcess>
CDSSolver::solve(Date maturity_date)
{
   Handle<Quote> quote(boost::shared_ptr<Quote>(new SimpleQuote(cur_val)));
   Date today = Date::todaysDate();


   shared_ptr<YieldTermStructure>   ts1(new FlatForward(today, divYield, Thirty360()));
   shared_ptr<YieldTermStructure>   ts2(new FlatForward(today, rf, Thirty360()));
   shared_ptr<BlackVolTermStructure> vs(new BlackConstantVol(today, NullCalendar(),sigma, Thirty360()));

   auto process = BlackScholesMertonProcess(quote,
         Handle<YieldTermStructure>(ts1),
         Handle<YieldTermStructure>(ts2),
         Handle<BlackVolTermStructure>(vs));


   shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(Option::Type::Call, strike));
   shared_ptr<Exercise> exercise(new EuropeanExercise(maturity_date));

   auto option = BarrierOption(Barrier::Type::UpIn, 
                               barrier, rebate,
                               payoff,
                               exercise);

   auto pproc = shared_ptr<GeneralizedBlackScholesProcess>(&process);

   option.setPricingEngine(shared_ptr<PricingEngine>(new AnalyticBarrierEngine(pproc)));

   return std::make_pair(option, process);
}

void CDSSolver::generateGrid(BarrierOption &option, BlackScholesMertonProcess &process, const vector<Size> &grid)
{
   double value = option.NPV();
   Size maxG = grid[grid.size()-1];   // find maximum grid value

   for (auto g : grid)
   {
      FdBlackScholesBarrierEngine be(shared_ptr<GeneralizedBlackScholesProcess>(&process), maxG, g);
      option.setPricingEngine(shared_ptr<PricingEngine>(&be));

      cout << std::abs(option.NPV()/value -1);

      FdBlackScholesBarrierEngine be1(shared_ptr<GeneralizedBlackScholesProcess>(&process), g, maxG);
      option.setPricingEngine(shared_ptr<PricingEngine>(&be1));

      cout << std::abs(option.NPV()/value -1);
   }
}

void test_CDSSolver()
{
   // use a few test values

   double cur_val = 50.0;
   double sigma = 0.2;
   double divYield = 0.01;
   double rf = 0.05;
   double strike = 104.0;
   double barrier = 85.0;
   double rebate = 0.0;

   CDSSolver solver(cur_val, sigma, divYield, rf, strike, barrier, rebate);

   Date date(10, Month::August, 2016);

   auto result = solver.solve(date);

   std::vector<Size> grid = { 5, 10, 25, 50, 100, 1000, 2000 };
   solver.generateGrid(result.first, result.second, grid);
}


int main_cds()
{
   test_CDSSolver();
   return 0;
}




class CDSContract {
public:
   CDSContract();
   CDSContract(const CDSContract &p);
   ~CDSContract();
   CDSContract &operator=(const CDSContract &p);

   double notional()   { return m_notional; }
   double spread()     { return m_spread;   }
   int timePeriod()    { return m_timePeriod; }
   bool payAtDefault() { return m_payAtDefault; }
   bool isLong()       { return m_isLong; }

private:

   double m_notional;
   double m_spread;
   int m_timePeriod;
   bool m_payAtDefault;
   bool m_isLong;
   
};

#endif 