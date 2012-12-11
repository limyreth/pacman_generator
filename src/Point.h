/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

template <typename T>
class Point
{
public:
    Point() {}

    Point(int x, int y) 
    :   x(x),
        y(y)
    {
    }

    template <typename U>
    bool operator == (const Point<U>& p) const {
        return this->x == p.x && this->y == p.y;
    }

    template <typename U>
    Point& operator += (const Point<U>& p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    template <typename U>
    Point operator + (const Point<U>& p) const {
        Point p2(*this);
        return p2 += p;
    }

    Point& operator *= (double a) {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Point operator * (double a) const {
        Point p2(*this);
        return p2 *= a;
    }

    Point& operator /= (double a) {
        this->x /= a;
        this->y /= a;
        return *this;
    }

    Point operator / (double a) const {
        Point p2(*this);
        return p2 /= a;
    }

public:
    T x;
    T y;
};

typedef Point<int> IPoint;
typedef Point<double> FPoint;
