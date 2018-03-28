/***************************************************************************
                          engine.cpp  -  description
                             -------------------
    begin                : Mon Apr 3 2000
    copyright            : (C) 2000 by Andreas Agorander
    email                : Bluefire@linux.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "engine.h"
//#include <qmessagebox.h>

Engine::Engine(ScreenObject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    int count;
    int count2;
    thrust = 0;
    for (count = 0; count < 4; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

Engine::~Engine()
{
}

/**
	* Check for port orders
	*/
void Engine::execute()
{
    if (stacktaken[0][0] == true) {
        thrust = portstack[0][0];
        if (thrust > ourlevel)
            thrust = ourlevel;
        if (thrust < 0)
            thrust = 0;
        moveportstack(0);
    }

    if (stacktaken[1][0] == true) {
        thrust = -(portstack[1][0]);
        if (thrust < -(ourlevel / 2))
            thrust = -(ourlevel / 2);
        if (thrust > 0)
            thrust = 0;
        moveportstack(1);
    }

    if (thrust >= 0) {
        ourbot->changeHeat(int(thrust / 35));
        if (thrust > ourbot->speed() && ourbot->fuel() >= thrust + 1) {
            ourbot->changeSpeed(1);
            if (thrust > 0)
                ourbot->setFuel(-(1 + thrust / 10));
        } else {
            if (ourbot->speed() > 0)
                ourbot->changeSpeed(-1);
            if (ourbot->speed() < 0)
                ourbot->changeSpeed(1);
        }
    }
    if (thrust < 0) {
        ourbot->changeHeat(int(-(thrust / 25)));
        if (thrust < ourbot->speed() && ourbot->fuel() >= (-thrust) + 1) {
            ourbot->changeSpeed(-1);
            ourbot->setFuel(-(1 + (-thrust) / 10));
        } else {
            if (ourbot->speed() < 0)
                ourbot->changeSpeed(1);
            if (ourbot->speed() > 0)
                ourbot->changeSpeed(-1);
        }
    }
}

/**
	* Returns to CPU instruction IN
	*/
int Engine::readPort(unsigned char port)
{
    switch (port) {
    case 0:
        return thrust;
        break;
    case 1:
        return ourbot->speed();
        break;
    }
    return 0;
}
