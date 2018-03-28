/***************************************************************************
                          cloaker.cpp  -  description
                             -------------------
    begin                : Wed Jan 31 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#include "cloaker.h"

Cloaker::Cloaker(ScreenObject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    cloakon = false;
    int count;
    int count2;
    for (count = 0; count < 4; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

Cloaker::~Cloaker()
{
}

void Cloaker::execute()
{
    if (cloakon && ourbot->fuel() > 5) {
        ourbot->setFuel(-6);
        ourbot->changeHeat(5 + ourlevel);
        ourbot->setRadar(5 - ourlevel);
    }
    if (stacktaken[0][0] == true) {
        cloakon = portstack[0][0];
        moveportstack(0);
    }
}
