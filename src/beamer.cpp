/***************************************************************************
                          beamer.cpp  -  description
                             -------------------
    begin                : Tue Oct 31 2000
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

#include "beamer.h"

/**
	* Constructor, inits device
	*/
Beamer::Beamer(ScreenObject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    int count;
    int count2;
    relang = 0;
    for (count = 0; count < 3; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}
/**
	* Destructor, does nothing
	*/
Beamer::~Beamer()
{
}

/**
	* Checks for port values that orders him to do something
	*/
void Beamer::execute()
{
    if (stacktaken[0][0] == true) {
        moveportstack(0);
        //Fire beam
        if (ourbot->fuel() <= 20) {
            return;
        }
        ourbot->setFuel(-20);
        ourbot->changeHeat(ourlevel);
        ourbot->addScreenObject(ourbot->xPos(), ourbot->yPos(),
                                ourbot->direction() + relang, 5, length);
    }
    if (stacktaken[1][0] == true) {
        relang = portstack[1][0];
        moveportstack(1);
    }

    if (stacktaken[2][0] == true) {
        length = portstack[2][0];
        moveportstack(2);
    }
}

/**
	* Return values to the CPU instruktion IN
	*/
int Beamer::readPort(unsigned char port)
{
    switch (port) {
    case 0:
        return relang;
        break;
    case 1:
        return length;
        break;
    }
    return 0;
}