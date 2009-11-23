/***************************************************************************
                          timedev.cpp  -  description
                             -------------------
    begin                : Tue Jul 11 2000
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

#include "timedev.h"

timedev::timedev (screenobject &object)
{
    ourbot = &object;
    timecount = 0;
    int count;
    int count2;
    intenabled = false;
    for (count=0; count<4; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

timedev::~timedev()
{
}

/**
	* Check for changes in inports, update timer and
	* check if time interrupt should be issued
	*/
void timedev::execute()
{
    timecount++;
    if (stacktaken[0][0] == true)
    {
        timecount = portstack[0][0];
        moveportstack (0);
    }
    if (stacktaken[1][0] == true)
    {
        interrupttime = portstack[1][0];
        moveportstack (1);
    }
    if (stacktaken[2][0] == true)
    {
        intenabled = portstack[2][0];
        moveportstack (2);
    }
    if (timecount == interrupttime && intenabled == true)
        ourbot->addinterrupt (1);
}

int timedev::getfromport (int port)
{
    switch (port)
    {
    case 0 :
        return timecount;
        break;
    case 1 :
        return interrupttime;
        break;
    case 2 :
        return intenabled;
        break;
    }
    return 0;
}
