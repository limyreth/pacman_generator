/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <iostream>

template <typename T>
class Point
{
public:
    Point() : Point(0, 0) {}

    Point(T x, T y) 
    :   x(x),
        y(y)
    {
    }

    template <typename U>
    bool operator == (const Point<U>& p) const {
        return this->x == p.x && this->y == p.y;
    }

    template <typename U>
    bool operator != (const Point<U>& a) const {
        return !(*this == a);
    }

    template <typename U>
    Point<T>& operator += (const Point<U>& p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    template <typename U>
    Point<T> operator + (const Point<U>& p) const {
        Point<T> p2(*this);
        return p2 += p;
    }

    Point<T>& operator *= (double a) {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Point<T> operator * (double a) const {
        Point<T> p2(*this);
        return p2 *= a;
    }

    Point<T>& operator /= (double a) {
        this->x /= a;
        this->y /= a;
        return *this;
    }

    Point<T> operator / (double a) const {
        Point<T> p2(*this);
        return p2 /= a;
    }

    Point<T> operator -() const {
        return (*this) * -1;
    }

public:
    T x;
    T y;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Point<T> p) {
    out << "(" << p.x << ", " << p.y << ")";
}

typedef Point<int> IPoint;
typedef Point<double> FPoint;
