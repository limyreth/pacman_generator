/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Sounds;

class App
{
public:
    App(Sounds* snd);

    Sounds* getSnd() { return snd; }
    void dot_eaten();
    void delay(unsigned int ms);

private:
    Sounds *snd;
};
