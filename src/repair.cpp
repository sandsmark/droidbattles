/***************************************************************************
                          repair.cpp  -  description
                             -------------------
    begin                : Sun Jul 16 2000
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

#include "repair.h"

Repair::Repair(ScreenObject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    repaircycles = ourlevel;
}

Repair::~Repair()
{
}

/**
	* Check if one repair should be done
	*/
void Repair::execute()
{
    if (--repaircycles <= 0) {
        repaircycles = ourlevel;
        int count;
        for (count = 0; count < 32; count++) {
            if ((ourbot->writeToDevice(count, 2, 0) == 99) && (ourbot->writeToDevice(count, 3, 0) > 0)) {
                ourbot->writeToDevice(count, 4, -1); //Repair one damage
                break;
            }
        }
        return;
    }
}

int Repair::readPort(uint8_t /*port*/)
{
    return 0;
}
