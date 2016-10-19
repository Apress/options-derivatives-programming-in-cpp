//
//  templates.hpp

#ifndef templates_hpp
#define templates_hpp

#include <vector>
#include <set>


template <long N>
class Factorial {
public:
    enum {
        Argument = N
    };
    static long value();
};

template <long N>
long Factorial<N>::value()
{
    return N * Factorial<N-1>::value();
}


template <>
long Factorial<0>::value()
{
    return 1;
}

void array_normalize(std::vector<double> &array);

void set_normalize(std::set<double> &set);

template <class T>
class Normalization {
public:
    typedef T  Type;
    static void normalize(T &arg);
};

template <>
void Normalization<std::vector<double>>::normalize(std::vector<double> &a)
{
    array_normalize(a);
}

template <>
void Normalization<std::set<double>>::normalize(std::set<double> &a)
{
    set_normalize(a);
}

template <class T>
void normalize(T &val) {
    Normalization<T>::normalize(val);
}

void use_normalize()
{
    std::set<double> set;
    std::vector<double> array;



    normalize(set);
    normalize(array);
}

void array_normalize(std::vector<double> &array)
{

}

void set_normalize(std::set<double> &set)
{

}


#endif /* templates_hpp */
