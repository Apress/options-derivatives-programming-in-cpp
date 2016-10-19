//
//  LAVectors.cpp

#include "LAVectors.hpp"

#include <cmath>

//
// adds a scalar number to a vector "v"
//
Vector add(double num, const Vector &v)
{
    int n = (int)v.size();
    Vector result(n);
    for (int i=0; i<n; ++i)
    {
        result[i] = v[i] + num;
    }
    return result;
}

//
// pre-multiply a number "num" by the given vector "v"
//
Vector multiply(double num, const Vector &v)
{
    int n = (int)v.size();
    Vector result(n);
    for (int i=0; i<n; ++i)
    {
        result[i] = v[i] * num;
    }
    return result;
}

//
// perform vector addition in place (modifying the given vector)
//
void in_place_add(double num, Vector &v)
{
    int n = (int)v.size();
    for (int i=0; i<n; ++i)
    {
        v[i] += num;
    }
}

//
// perform matrix multiplication in place (modifying the given vector)
//
void in_place_multiply(double num, Vector &v)
{
    int n = (int)v.size();
    for (int i=0; i<n; ++i)
    {
        v[i] *= num;
    }
}


//
// perform vector addition of two vectors  (v1 and v2)
//
Vector add(const Vector &v1, const Vector &v2)
{
    int n = (int)v1.size();
    Vector result(n);
    for (int i=0; i<n; ++i)
    {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

//
// performs the vector product of vectors v1 and v2
//
double product(const Vector &v1, const Vector &v2)
{
    double result = 0;
    int n = (int)v1.size();
    for (int i=0; i<n; ++i)
    {
        result += v1[i] * v2[i];
    }
    return result;
}

//
// in place addition of vectors v1 and v2
//
void  in_place_add(Vector &v1, const Vector &v2)
{
    int n = (int)v1.size();
    for (int i=0; i<n; ++i)
    {
        v1[i] += v2[i];
    }
}

//
// in place product of vectors v1 and v2
//
void  in_place_product(Vector &v1, const Vector &v2)
{
    int n = (int)v1.size();
    for (int i=0; i<n; ++i)
    {
        v1[i] *= v2[i];
    }
}

//
// computes the norm of a vector
//
double norm(const Vector &v)
{
    double result = 0;
    int n = (int)v.size();
    for (int i=0; i<n; ++i)
    {
        result += v[i] * v[i];
    }
    return std::sqrt(result);
}
