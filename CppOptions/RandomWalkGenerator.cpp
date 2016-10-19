//
//  RandomWalkGenerator.cpp
//
//  Simple random walk implementation.

#include "RandomWalkGenerator.h"

#include <cstdlib>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

//
// Constructor. The supplied parameters represent the number of elements in the
// random walk, the initial price, and the step size for the random walk.
//
RandomWalkGenerator::RandomWalkGenerator(int size, double start, double step)
: m_numSteps(size),
m_stepSize(step),
m_initialPrice(start)
{
}

RandomWalkGenerator::RandomWalkGenerator(const RandomWalkGenerator &p)
: m_numSteps(p.m_numSteps),
m_stepSize(p.m_stepSize),
m_initialPrice(p.m_initialPrice)
{
}

RandomWalkGenerator::~RandomWalkGenerator()
{
}

RandomWalkGenerator &RandomWalkGenerator::operator=(const RandomWalkGenerator &p)
{
    if (this != &p)
    {
        m_numSteps = p.m_numSteps;
        m_stepSize = p.m_stepSize;
        m_initialPrice = p.m_initialPrice;
    }
    return *this;
}

//
// returns a single step of the random walk
//
double RandomWalkGenerator::computeRandomStep(double currentPrice)
{
    int r = rand() % 3;
    double val = currentPrice;
    if (r == 0)
    {
        val += (m_stepSize * val);
    }
    else if (r == 1)
    {
        val -= (m_stepSize * val);
    }
    return val;
}


//
// This is the main method. It will generate random numbers within
// the constraints set in the constructor.
//
std::vector<double> RandomWalkGenerator::generateWalk()
{
    vector<double> walk;
    double prev = m_initialPrice;

    for (int i=0; i<m_numSteps; ++i)
    {
        double val =  computeRandomStep(prev);
        walk.push_back(val);
        prev = val;
    }
    return walk;
}

//
// This is a testing stub. It generates a sequence of random points.
//
int main_rwg()
{
    RandomWalkGenerator rw(100, 30, 0.01);
    vector<double> walk = rw.generateWalk();
    for (int i=0; i<walk.size(); ++i)
    {
        cout << ", " << i << ", " << walk[i];
    }
    cout << endl;
    return 0;
}
