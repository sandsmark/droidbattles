/***************************************************************************
                          scandetect.cpp  -  description
                             -------------------
    begin                : Sat Dec 9 2000
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

#include "scandetect.h"

ScanDetect::ScanDetect(ScreenObject &object)
{
    ourbot = &object;
    int count;
    int count2;
    numscans = 0;
    lastscandir = 0;
    lastscanintensity = 0;
    for (count = 0; count < 3; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

ScanDetect::~ScanDetect()
{
}

void ScanDetect::execute()
{
    if (stacktaken[0][0]) //Zero scan counter
    {
        numscans = 0;
        moveportstack(0);
    }
}

int ScanDetect::readPort(uint8_t port)
{
    switch (port) {
    case 0:
        return numscans;
        break;
    case 1:
        return lastscandir;
        break;
    case 2:
        return lastscanintensity;
        break;
    }
    return 0;
}

int ScanDetect::type()
{
    return 11;
}

/**
	* Gets called by enemy scanner via bot
	* Updates variables
	*/
void ScanDetect::doSpecial(int intensity, int dir)
{
    numscans++;
    lastscandir = dir;
    lastscanintensity = intensity;
}
