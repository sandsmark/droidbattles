/***************************************************************************
                          chafflauncher.cpp  -  description
                             -------------------
    begin                : Fri Dec 1 2000
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

#include "chafflauncher.h"
/**
	* Constructor, init device
	*/
chafflauncher::chafflauncher (screenobject &object,int level)
{
    chaffleft = level;
    int count,count2;
    ourbot = &object;
    for (count=0; count<3; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

/**
	* Destructor, does nothing
	*/
chafflauncher::~chafflauncher()
{
}

/**
	* Checks for port orders
	*/
void chafflauncher::execute()
{
    int count;
    if (stacktaken[0][0] == true)
    {
        for (count = 1; count<4; count++)
        {
            portstack[0][count-1] = portstack[0][count];
            stacktaken[0][count-1] = stacktaken[0][count];
        }
        portstack[0][3] = 0;
        stacktaken[0][3] = false;
        if (chaffleft > 0)
        {
            ourbot->addscrobject (ourbot->getXpos(),ourbot->getYpos(),
                                  ourbot->getdir(),7,ourbot->getspeed() /2);
            chaffleft--;
        }
    }
}

/**
	* Returns number of chaffs left to CPU instruktion IN
	*/
int chafflauncher::getfromport (unsigned char port)
{
    switch (port)
    {
    case 0 :
        return chaffleft;
        break;
    }
    return 0;
}