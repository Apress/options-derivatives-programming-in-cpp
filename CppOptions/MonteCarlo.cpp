//
//  MonteCarlo.cpp

#include "MonteCarlo.hpp"


#include <iostream>
#include <random>
#include <vector>
#include <assert.h>

using std::cout;
using std::endl;
using std::vector;

std::default_random_engine generator;


int get_uniform_int(int max)
{
    if (max < 1)
    {
        cout  << "invalid parameter max " << max << endl;
        throw std::runtime_error("invalid parameter max");
    }
    std::uniform_int_distribution<int> uint(0,max);

    return uint(generator);
}


vector<bool> coin_toss_experiment(int num_experiments)
{
    if (num_experiments < 1)
    {
        cout  << "invalid number of experiments " << num_experiments << endl;
        throw std::runtime_error("invalid number of experiments");
    }

    std::bernoulli_distribution bernoulli(0.5);

    vector<bool> results;
    for (int i=0; i<num_experiments; ++i)
    {
        results.push_back(bernoulli(generator));
    }
    return results;
}

vector<int> num_customers_experiment(double mean, int max, int ntries)
{
    std::default_random_engine generator;

    vector<int> occurrences(max, 0);
    std::poisson_distribution<int> poisson(mean);

    for (int i=0; i<ntries; ++i)
    {
        int result = poisson(generator);
        if (result < max) {
            occurrences[result] ++;
        }

    }

    return occurrences;
}

vector<double> get_normal_observations(int n, double mean, double stdev)
{
    std::default_random_engine generator;


    vector<double> values;
    std::normal_distribution<double> normaldist(mean, stdev);

    for (int i=0; i<n; ++i)
    {
        values.push_back(normaldist(generator));
    }

    return values;
}



int main_mcarl()
{
    auto data = num_customers_experiment(10.5, 20, 200);

    for (int i=0; i<int(data.size()); ++i)
    {
        cout << " event " << i << " occurred "  << data[i] << " times" << endl;
    }

    vector<double> nv = get_normal_observations(1000, 8, 2);

    auto res = std::minmax_element(nv.begin(), nv.end());
    double min = *(res.first);
    double max = *(res.second);

    int N = 100;
    double h = (max - min)/double(N);
    vector<int> values(N, 0);

    for (int i=0; i<int(nv.size()); ++i)
    {
        double v = nv[i];
        int pos = int((v - min) / h);
        if (pos == N) pos--; // avoid the highest element
        assert(pos < N);
        values[pos]++;
    }

    for (int i=0; i<N; ++i)
    {
        cout << min + (i*h) << " " << values[i] << endl;
    }
    return 0;
}


