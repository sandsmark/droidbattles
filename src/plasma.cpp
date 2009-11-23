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

plasma::plasma (screenobject &object, int arg1, int offset)
{
    ourlevel = arg1;
    ourbot = &object;
    int count;
    int count2;
    readiness = 200;
    relang = offset*4;
    for (count=0; count<3; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

plasma::~plasma()
{
}

/**
	* Increases readiness and checks if port orders it
	* to shoot
	*/
void plasma::execute()
{
    if (readiness < 200)
        readiness += ourlevel;
    if (stacktaken[0][0] == true && readiness > 0)
    {
        moveportstack (0);
        //Fire plasma missile code
        ourbot->addscrobject (ourbot->getXpos(),ourbot->getYpos(),
                              ourbot->getdir() +relang,2,ourbot->getnum());
        ourbot->changeheat (45);
        readiness -= 80;
    }
}
