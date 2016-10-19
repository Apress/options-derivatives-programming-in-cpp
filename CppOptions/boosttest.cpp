//
//  boosttest.cpp



#include "boosttest.hpp"


#include <iostream>
#include <boost/array.hpp>

#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

typedef boost::array< double , 3 > state_type;

void lorenz( const state_type &x , state_type &dxdt , double t )
{
   dxdt[0] = sigma * ( x[1] - x[0] );
   dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
   dxdt[2] = -b * x[2] + x[0] * x[1];
}

void write_lorenz( const state_type &x , const double t )
{
   cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
}

void main2(int argc, char **argv)
{
   state_type x = { 10.0 , 1.0 , 1.0 }; // initial conditions
   integrate(lorenz , x , 0.0 , 25.0 , 0.1 , write_lorenz );
}



//
// This is the equation at the right side of the ODE   y' = f(x,y)
// It is evaluated in the inner steps of the algorithm.
//
void right_side_equation(double y, double &dydx, double x)
{
   dydx = 3.0/(2.5*x*x) + y/(1.5*x);
}

// this function simply prints the current value of the interactive
// solution steps.
void write_cout( const double &x , const double t )
{
   cout << t << '\t' << x << endl;
}

// A stepper based on Runge-Kutta algorithm.
// the state_type use is 'double'
typedef runge_kutta_dopri5<double> stepper_type;


// This solves the ODE described above with initial condition x(1) = 0.


int main_boost()
{
   double x = 0.0;
   auto n = integrate_adaptive(
         make_controlled(1E-12, 1E-12, stepper_type()),  // instantiate the stepper
         right_side_equation,            // equation
         x,                              // initial state
         1.0 , 10.0 , 0.1 ,              // start x, end x, and step size
         write_cout );
   cout << " process completed after "  << n << " steps \n";
   return 0;
}