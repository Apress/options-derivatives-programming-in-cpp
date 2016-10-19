//
//  RandomWalk.cpp

#include "RandomWalk.hpp"


#include <cstdlib>
#include <iostream>
#include <random>

using std::vector;
using std::cout;
using std::endl;


std::default_random_engine engine;


RandomWalkModel::RandomWalkModel(int size, double start, double step)
: m_numSteps(size),
  m_stepSize(step),
  m_startPrice(start)
{
}

RandomWalkModel::RandomWalkModel(const RandomWalkModel &p)
: m_numSteps(p.m_numSteps),
  m_stepSize(p.m_stepSize),
  m_startPrice(p.m_startPrice)
{
}

RandomWalkModel::~RandomWalkModel()
{
}

RandomWalkModel &RandomWalkModel::operator=(const RandomWalkModel &p)
{
    if (this != &p)
    {
        m_numSteps = p.m_numSteps;
        m_stepSize = p.m_stepSize;
        m_startPrice = p.m_startPrice;
    }
    return *this;
}

int RandomWalkModel::random_integer(int max)
{

    std::uniform_int_distribution<int> unif(0, max);
    return unif(engine);
}

std::vector<double> RandomWalkModel::getWalk()
{
    vector<double> walk;
    double prev = m_startPrice;

    for (int i=0; i<m_numSteps; ++i)
    {
        int r = random_integer(3);
        cout << r << endl;
        double val = prev;
        if (r == 0) val += (m_stepSize * val);
        else if (r == 1) val -= (m_stepSize * val);
        walk.push_back(val);
        prev = val;
    }
    return walk;
}

int main_randw()
{
    RandomWalkModel rw(200, 30, 0.01);
    vector<double> walk = rw.getWalk();
    for (int i=0; i<walk.size(); ++i)
    {
        cout << ", " << walk[i];
    }
    cout << endl;
    return 0;
}

