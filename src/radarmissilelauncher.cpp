/***************************************************************************
                          radarmissilelauncher.cpp  -  description
                             -------------------
    begin                : Fri Aug 11 2000
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

#include "radarmissilelauncher.h"

RadarMissileLauncher::RadarMissileLauncher(ScreenObject &object, int level,
                                           Ram *memdevice, int offset)
{
    ourlevel = level;
    memd = memdevice;
    relang = offset * 4;
    int count, count2;
    ourbot = &object;
    reloadtime = 1;
    for (count = 0; count < 3; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

RadarMissileLauncher::~RadarMissileLauncher()
{
}

/**
	* Commit port orders
	*/
void RadarMissileLauncher::execute()
{
    if (reloadtime > 0) {
        reloadtime--;
    }
    //Set boot mem
    if (stacktaken[0][0]) {
        bootmem = portstack[0][0];
        moveportstack(0);
    }
    //Set stack mem
    if (stacktaken[1][0]) {
        stackmem = portstack[1][0];
        moveportstack(1);
    }
    //Fire a missile
    if (stacktaken[2][0]) {
        if (reloadtime <= 0) {
            ourbot->addScreenObject(ourbot->xPos(), ourbot->yPos(),
                                    ourbot->direction() + relang, 4, bootmem, stackmem, memd);
            moveportstack(2);
            reloadtime = ourlevel;
        }
    }
}

/**
	* return reloadtime
	*/
int RadarMissileLauncher::readPort(uint8_t port)
{
    switch (port) {
    case 0:
        return reloadtime;
        break;
    }
    return 0;
}
