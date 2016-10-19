//
//  qlibsample.cpp

#if 0

#include "qlibsample.hpp"

typedef double Real;

using std::cout;
using std::endl;

using namespace QuantLib;



void testingBlackScholesCalculator ()
{
   Real S0=100.0, K=105.0;
   Real rd =0.034 , rf =0.021 , tau =0.5 , vol =0.177;
   Real domDisc=std::exp(-rd*tau), forDisc=std::exp(-rf*tau); Real stdDev=vol*std::sqrt(tau);
   boost::shared_ptr <PlainVanillaPayoff > vanillaPayoffPut(
                                                            new QuantLib::PlainVanillaPayoff(Option::Put,K));
   boost::shared_ptr<AssetOrNothingPayoff> aonPayoffCall(
                                                            new AssetOrNothingPayoff(QuantLib::Option::Call,K));
   QuantLib::BlackScholesCalculator vanillaPutPricer(vanillaPayoffPut,S0,forDisc,stdDev,domDisc);
   QuantLib::BlackScholesCalculator aonCallPricer(aonPayoffCall,S0,forDisc,stdDev,domDisc);
   std::cout << "--------------Vanilla Values -------------" << std::endl;
   std::cout << "Value:" << vanillaPutPricer.value() << std::endl;
   std::cout << "Delta:" << vanillaPutPricer.delta() << std::endl;
   std::cout << "Gamma:" << vanillaPutPricer.gamma() << std::endl;
   std::cout << "Vega:" << vanillaPutPricer.vega(tau) << std::endl;
   std::cout << "Theta:" << vanillaPutPricer.theta(tau) << std::endl;
   std::cout << "Delta Fwd:" << vanillaPutPricer.deltaForward() << std::endl;
   std::cout << "Gamma Fwd:" << vanillaPutPricer.gammaForward() << std::endl;
   std::cout << "-------------- AON Values-------------" << std::endl;
   std::cout << "Value:" << aonCallPricer.value() << std::endl;
   std::cout << "Delta:" << aonCallPricer.delta() << std::endl;
   std::cout << "Gamma:" << aonCallPricer.gamma() << std::endl;
   std::cout << "Vega:" << aonCallPricer.vega(tau) << std::endl;
   std::cout << "Theta:" << aonCallPricer.theta(tau) << std::endl;
   std::cout << "Delta Fwd:" << aonCallPricer.deltaForward() << std::endl;
   std::cout << "Gamma Fwd:" << aonCallPricer.gammaForward() << std::endl;


}

struct BlackScholesPrameters {
   double S0;
   double K;
   double rd;
   double rf;
   double tau;
   double vol;
};


void callBlackScholes(BlackScholesPrameters  &bp)
{
   // create a vanilla option (standard option type)
   boost::shared_ptr<PlainVanillaPayoff>
      vanillaPut(new QuantLib::PlainVanillaPayoff(Option::Put,bp.K));

   // compute discount rates
   double cur_disc = std::exp(-bp.rd  * bp.tau);  // current discount rate
   double for_disc = std::exp(-bp.rf  * bp.tau);  // foward  discount rate
   double stdev    = bp.vol * std::sqrt(bp.tau);  // standard deviation

   BlackScholesCalculator putPricer(vanillaPut, bp.S0, for_disc, stdev, cur_disc);

   // Print options greeks
   cout << "value:" << putPricer.value() << endl;
   cout << "delta:" << putPricer.delta() << endl;
   cout << "gamma:" << putPricer.gamma() << endl;
   cout << "vega:"  << putPricer.vega(bp.tau)  << endl;
   cout << "theta:" << putPricer.theta(bp.tau) << endl;
   cout << "delta Fwd:" << putPricer.deltaForward() << endl;
   cout << "gamma Fwd:" << putPricer.gammaForward() << endl;

}

void testBlackScholes()
{
   BlackScholesPrameters bp;

   bp.S0 = 95.0;     // current price
   bp.K  = 100.0;    // strike
   bp.rd = 0.026;    // current rate of return
   bp.rf = 0.017;    // forward rate of return
   bp.tau= 0.62;     // tau (time greek)
   bp.vol= 0.193;    // volatility

   callBlackScholes(bp);
}



void testDates()
{
   Date date(10, Month::April, 2010);
   cout << "original date: " << date << endl;

   date += 2 * Days;
   cout << "after 2 days: " << date << endl;

   date += 3 * Months;
   cout << "after 3 months: " << date << endl;
}

void nextAndPreviousDay()
{
   Date date(28, Month::February, 2010);
   cout << "original date: " << date << endl;

   date++;
   cout << "next day: " << date << endl;

   date--;
   cout << "previous day: " << date << endl;
}

void dateQuestions()
{
   Date date(20, Month::February, 2010);


   cout << "weekday: " << date.weekday() << endl;

   cout << "is leap year? " << Date::isLeap(date.year()) << endl;

   cout << "is end of month? " << Date::isEndOfMonth(date) << endl;
}

void useCalendar()
{
   Calendar cal = UnitedStates(UnitedStates::NYSE);

   cout << " list of holidays " << endl;
   for (auto date : Calendar::holidayList(cal, Date(1, Month::Jan, 2010), Date(1, Month::Jan, 2012)))
   {
      cout << " " << date;
   }

   cout << " is Jan 1 2010 a business day?  "
        << cal.isBusinessDay(Date(1, Month::Jan, 2010)) << endl;
   cout << " is Jan 1 2010 a holiday?  "
        << cal.isHoliday(Date(1, Month::Jan, 2010))     << endl;
   cout << " is Jan 1 2010 end of month?  "
        << cal.isEndOfMonth(Date(1, Month::Jan, 2010))  << endl;
}

Calendar createNewCalendar()
{
   Calendar newCal = UnitedStates(UnitedStates::NYSE);

   // Remove winter holiday
   newCal.removeHoliday(Date(25, Month::December, 2016));

   // Add international worker's day
   newCal.addHoliday   (Date(1,  Month::May, 2016));

   cout << " list of holidays " << endl;
   for (auto date : Calendar::holidayList(newCal, Date(1, Month::Jan, 2016), Date(1, Month::Jan, 2016)))
   {
      cout << " " << date;
   }

   return newCal;
}

int getNumberOfDays(Date d1, Date d2)
{
   Calendar usCal = UnitedStates(UnitedStates::NYSE);

   int nDays = usCal.businessDaysBetween(d1, d2);

   cout << " the interval size is "  << nDays << endl;

   return nDays;
}


int main_qlib()
{

   cout << " hello \n" ;
   return 0;
   //testingBlackScholesCalculator();
}

#endif