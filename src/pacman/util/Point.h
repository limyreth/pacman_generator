/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "assertion.h"

#include <iostream>
#include <cmath>

namespace PACMAN {

template <typename T>
class Point
{
public:
    Point() {}  // invalid state, for use with stl containers, ...

    Point(T x, T y) 
    :   x(x),
        y(y)
    {
    }

    bool operator == (const Point<T>& p) const {
        return this->x == p.x && this->y == p.y;
    }

    bool operator != (const Point<T>& a) const {
        return !(*this == a);
    }

    Point<T>& operator += (const Point<T>& p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    Point<T> operator + (const Point<T>& p) const {
        Point<T> p2(*this);
        return p2 += p;
    }

    Point<T>& operator -= (const Point<T>& p) {
        this->x -= p.x;
        this->y -= p.y;
        return *this;
    }

    Point<T> operator - (const Point<T>& p) const {
        Point<T> p2(*this);
        return p2 -= p;
    }

    Point<T>& operator *= (T a) {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Point<T> operator * (T a) const {
        Point<T> p2(*this);
        return p2 *= a;
    }

    Point<T>& operator /= (T a) {
        REQUIRE(a != 0.0f);
        this->x /= a;
        this->y /= a;
        return *this;
    }

    Point<T> operator / (T a) const {
        Point<T> p2(*this);
        return p2 /= a;
    }

    Point<T> operator -() const {
        return (*this) * -1;
    }

    T dot_product(Point<T> p) const {
        return x*p.x + y*p.y;
    }

    T length() const {
        return sqrt(dot_product(*this));
    }

    void normalise() {
        *this /= length();
    }

public:
    T x;
    T y;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Point<T> p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

typedef Point<int> IPoint;
typedef Point<float> FPoint;

}
