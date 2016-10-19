//
//  templates.cpp

#include "templates.hpp"

#include <cstring>
#include <iostream>

template <class T>
T generic_max(T a, T b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

template <>
const char * generic_max(const char *a, const char *b)
{
    if (strcmp(a, b) > 0)
    {
        return a;
    }
    else
    {
        return b;
    }
}


template <int N>
void printNumberPlusOne()
{
    int a = N + 1;
    std::cout << a << std::endl;
}

void usePrintTemplate()
{
    printNumberPlusOne<10>();
}

template<int N>
void printNumberRecursive()     // general case
{
    std::cout << N << " ";
    printNumberRecursive<N-1>();
}

template<>
void printNumberRecursive<0>()  //  base case
{
    std::cout << std::endl;
}

void usePrintRecursive()
{
    printNumberRecursive<10>();
}

template <int N>
int intSum()
{
    return N + intSum<N-1>();
}

template <>
int intSum<0>()
{
    return 0;
}

void useIntSum()
{
    std::cout << intSum<20>() << std::endl;
}

void useFactorial()
{
    Factorial<8> fact;
    std::cout << " factorial for argument " << fact.Argument << " is " <<  fact.value() << std::endl;
}

int int_max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void use_template()
{
    int res = 0;
    int a = 15,  b = 32;

    res = generic_max(a, b);


    generic_max("test1", "test2");
}




int main_templat()
{
    usePrintRecursive();
    useIntSum();
    useFactorial();
    return 0;
}