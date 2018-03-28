/***************************************************************************
                          plasma.cpp  -  description
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

#include "plasma.h"

Plasma::Plasma(ScreenObject &object, int arg1, int offset)
{
    ourlevel = arg1;
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

Plasma::~Plasma()
{
}

/**
	* Increases readiness and checks if port orders it
	* to shoot
	*/
void Plasma::execute()
{
    if (readiness < 200) {
        readiness += ourlevel;
    }
    if (stacktaken[0][0] && readiness > 0) {
        moveportstack(0);
        //Fire plasma missile code
        ourbot->addScreenObject(ourbot->xPos(), ourbot->yPos(),
                                ourbot->direction() + relang, 2, ourbot->number());
        ourbot->changeHeat(45);
        readiness -= 80;
    }
}
