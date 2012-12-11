/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

// TODO rename to Point
class SDL_Point
{
public:
    SDL_Point() {}

    SDL_Point(int x, int y) 
    :   x(x),
        y(y)
    {
    }

    bool operator == (const SDL_Point& p) const {
        return this->x == p.x && this->y == p.y;
    }

    SDL_Point& operator += (const SDL_Point& p) {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    SDL_Point operator + (const SDL_Point& p) const {
        SDL_Point p2(*this);
        return p2 += p;
    }

    SDL_Point& operator *= (int a) {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    SDL_Point operator * (int a) const {
        SDL_Point p2(*this);
        return p2 *= a;
    }

    SDL_Point& operator /= (int a) {
        this->x /= a;
        this->y /= a;
        return *this;
    }

    SDL_Point operator / (int a) const {
        SDL_Point p2(*this);
        return p2 /= a;
    }

public:
    int x;
    int y;
};
