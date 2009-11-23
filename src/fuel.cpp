/***************************************************************************
                          fuel.cpp  -  description
                             -------------------
    begin                : Mon Apr 17 2000
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

#include "fuel.h"

fuel::fuel (screenobject &object, int arg1)
{
    int ourlevel = arg1;
    ourbot = &object;
    ourbot->setfuel (ourlevel);
    intenabled = false;
    int count;
    int count2;
    for (count=0; count<4; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

fuel::~fuel()
{
}

/**
	* Returns amount of fuel to in instruction
	*/
int fuel::getfromport (unsigned char port)
{
    switch (port)
    {
    case 0 :
        return ourbot->getfuel();
        break;
    }
    return 0;
}

/**
	* First checks if "fuel below level" interrupt
	* should be issued, then checks for inport
	* orders (which sets the should interrupt be
	* issued variable and the level for the interrupt)
	*/
void fuel::execute()
{
    if (intenabled)
    {
        if (ourbot->getfuel() < fuelintlevel)
            ourbot->addinterrupt (4);
    }
    if (stacktaken[0][0] == true)
    {
        intenabled = portstack[0][0];
        moveportstack (0);
    }
    if (stacktaken[1][0] == true)
    {
        fuelintlevel = portstack[1][0];
        moveportstack (1);
    }
}