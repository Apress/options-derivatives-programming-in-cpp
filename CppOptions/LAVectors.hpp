//
//  LAVectors.hpp

#ifndef LAVectors_hpp
#define LAVectors_hpp


#include <vector>

typedef std::vector<double> Vector;

// scalar by vector operations

Vector add(double num, const Vector &v);
Vector multiply(double num, const Vector &v);

void in_place_add(double num, Vector &v);
void in_place_multiply(double num, Vector &v);

inline Vector operator +(double num, const Vector &v)
{
    return add(num, v);
}

inline Vector operator *(double num, const Vector &v)
{
    return multiply(num, v);
}

inline void operator +=(double num, Vector &v)
{
    in_place_add(num, v);
}

inline void operator *=(double num, Vector &v)
{
    in_place_multiply(num, v);
}

// vector to vector operations

Vector add(const Vector &v1, const Vector &v2);
void  in_place_add(Vector &v1, const Vector &v2);

double product(const Vector &v1, const Vector &v2);
void  in_place_product(Vector &v1, const Vector &v2);


inline Vector operator +(const Vector &v1, const Vector &v2)
{
    return add(v1, v2);
}

inline void  operator +=(Vector &v1, const Vector &v2)
{
    in_place_add(v1, v2);
}

inline double operator *(const Vector &v1, const Vector &v2)
{
    return product(v1, v2);
}

inline void  operator *=(Vector &v1, const Vector &v2)
{
    in_place_add(v1, v2);
}

double norm(const Vector &v);


#include <stdio.h>

#endif /* LAVectors_hpp */
