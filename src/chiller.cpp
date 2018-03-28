/***************************************************************************
                          chiller.cpp  -  description
                             -------------------
    begin                : Sat Jan 13 2001
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

#include "chiller.h"

Chiller::Chiller(ScreenObject &object, int arg1)
{
    ison = false;
    ourbot = &object;
    heatdiss = arg1;
    int count;
    int count2;
    for (count = 0; count < 3; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

Chiller::~Chiller()
{
}

void Chiller::execute()
{
    if (ison && ourbot->fuel() > 5) {
        ourbot->changeHeat(-(heatdiss * 2));
        ourbot->setFuel(-(5));
    } else {
        ourbot->changeHeat(-(heatdiss));
    }
    if (stacktaken[0][0] == true) {
        ison = portstack[0][0];
        moveportstack(0);
    }
}