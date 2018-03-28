/***************************************************************************
                          rocketlauncher.cpp  -  description
                             -------------------
    begin                : Wed Nov 1 2000
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

#include "rocketlauncher.h"

RocketLauncher::RocketLauncher(ScreenObject &object, int level, int offset)
{
    ourlevel = level;
    ourbot = &object;
    int count;
    int count2;
    readiness = 200;
    relang = offset * 4;
    for (count = 0; count < 3; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

RocketLauncher::~RocketLauncher()
{
}

/**
	* Check for port orders
	*/
void RocketLauncher::execute()
{
    if (readiness < 200) {
        readiness++;
    }
    //Set distance
    if (stacktaken[0][0]) {
        distance = portstack[0][0];
        moveportstack(0);
    }
    //Fire a rocket
    if (stacktaken[1][0]) {
        if (readiness > 100) {
            ourbot->addScreenObject(ourbot->xPos(), ourbot->yPos(),
                                    ourbot->direction() + relang, 6, distance);
            moveportstack(1);
            readiness -= ourlevel;
        }
    }
}

/**
	* return inports
	*/
int RocketLauncher::readPort(unsigned char port)
{
    switch (port) {
    case 0:
        return readiness;
        break;
    case 1:
        return distance;
        break;
    }
    return 0;
}
