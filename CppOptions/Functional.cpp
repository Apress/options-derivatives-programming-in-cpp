//
//  Functional.cpp

#include "Functional.hpp"

#include <iostream>
#include <vector>

#include <functional>   // for functional STL code


//
// Class SimpleOption
//

double SimpleOption::getInTheMoneyProbability(int numDays, double currentUnderlyingPrice) const
{
    return 0; // implementation here
}


//
//  Class OptionComparison
//

OptionComparison::OptionComparison(bool directionLess)
: m_directionLess(directionLess)
{
}

OptionComparison::OptionComparison(const OptionComparison &p)
: m_directionLess(p.m_directionLess)
{
}

OptionComparison::~OptionComparison()
{
}

OptionComparison &OptionComparison::operator=(const OptionComparison &p)
{
    if (this != &p)
    {
        m_directionLess = p.m_directionLess;
    }
    return *this;
}

bool OptionComparison::operator()(const SimpleOption &o1, const SimpleOption &o2)
{
    bool result = false;

    // check components of opt1 and opt2. In practice this could be more complex.
    if (m_directionLess)
    {
        result = o1.daysToExpiration() < o2.daysToExpiration();
    }
    else
    {
        result = o1.daysToExpiration() > o2.daysToExpiration();
    }
    return result;
}


void test_compare()
{
    OptionComparison comparison(true);

    SimpleOption a, b;
    // ...

    if (comparison(a, b))
    {
        std::cout << " a is less than b " << std::endl;
    }
    else
    {
        std::cout << " b is less than a " << std::endl;
    }
}


void test_operator()
{
    using namespace std;

    vector<int> numbers = { 3, 4, 2, 1, 6 };

    sort(numbers.begin(), numbers.end(), greater<int>() );

}



void test_transform()
{
    using namespace std;

    auto list1 = { 3, 4, 2, 1, 6 };
    auto list2 = { 4, 1, 5, 3, 2 };

    vector<int> result(list1.size());

    transform(list1.begin(), list1.end(), list2.begin(), result.begin(), plus<int>() );

    // use transformed list here...

    copy(result.begin(), result.end(), std::ostream_iterator<int>(cout, ", "));

    // prints 7, 5, 7, 4, 8,
}

void use_bind()
{
    using namespace std;
    using namespace std::placeholders;

    auto list1 = { 3, 4, 2, 1, 6 };

    vector<int> result(list1.size());

    //  add 3 to each element of the list
    transform(list1.begin(), list1.end(), result.begin(),  bind(plus<int>(), _1, 3));

    copy(result.begin(), result.end(), std::ostream_iterator<int>(cout, ", "));

    // prints 6, 7, 5, 4, 9,
}


auto computeInTheMoneyProblExample(const std::vector<SimpleOption> &options) -> std::vector<double>
{
    using namespace std;
    using namespace std::placeholders;

    double currentPrice = 100.0;

    vector<double> probabilities(options.size());

    auto inTheMoneyCalc = bind(&SimpleOption::getInTheMoneyProbability, _1, 2, currentPrice);


    transform(options.begin(), options.end(), probabilities.begin(), inTheMoneyCalc);

    return probabilities;
}


void use_lambda()
{
    auto fun = [](double x, double y) -> double { return x + y; };

    double res = fun(4, 5);

    std::cout << " result is "  << res << std::endl;
}

void use_lambda2()
{
    int offset = 5;

    auto fun1 = [ offset](double x, double y) -> double { return x + y + offset; };
    auto fun2 = [&offset](double x, double y) -> double { return x + y + offset; };

    double res = fun1(4, 5);

    std::cout << " result is "  << res << std::endl;

    offset = 10;
    std::cout << " result of fun1 is "  << fun1(4, 5) << std::endl;
    std::cout << " result of fun2 is "  << fun2(4, 5) << std::endl;
}


void use_function(std::function<int(int,int)> f)
{
    auto res = f(2,3);

    std::cout << " the function returns the value "  << res << std::endl;
}

void test_use_function()
{
    auto f1 = [] (int a, int b) { return a + b; };
    auto f2 = [] (int a, int b) { return a * b; };

    use_function(f1);
    use_function(f2);
}

int main()
{
    test_use_function();
    return 0;
}



