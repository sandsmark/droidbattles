/***************************************************************************
                          engine.cpp  -  description
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

#include "engine.h"
//#include <qmessagebox.h>

engine::engine (screenobject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    int count;
    int count2;
    thrust = 0;
    for (count=0; count<4; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

engine::~engine()
{
}

/**
	* Check for port orders
	*/
void engine::execute()
{
    if (stacktaken[0][0] == true)
    {
        thrust = portstack[0][0];
        if (thrust >ourlevel) thrust = ourlevel;
        if (thrust <0) thrust =0;
        moveportstack (0);
    }

    if (stacktaken[1][0] == true)
    {
        thrust = - (portstack[1][0]);
        if (thrust < - (ourlevel/2)) thrust = - (ourlevel/2);
        if (thrust >0) thrust =0;
        moveportstack (1);
    }

    if (thrust >= 0)
    {
        ourbot->changeheat (int (thrust/35));
        if (thrust > ourbot->getspeed() && ourbot->getfuel() >= thrust+1)
        {
            ourbot->changespeed (1);
            if (thrust > 0) ourbot->setfuel (- (1+thrust/10));
        }
        else
        {
            if (ourbot->getspeed() > 0)
                ourbot->changespeed (-1);
            if (ourbot->getspeed() < 0)
                ourbot->changespeed (1);
        }
    }
    if (thrust < 0)
    {
        ourbot->changeheat (int (- (thrust/25)));
        if (thrust < ourbot->getspeed() && ourbot->getfuel() >= (-thrust) +1)
        {
            ourbot->changespeed (-1);
            ourbot->setfuel (- (1+ (-thrust) /10));
        }
        else
        {
            if (ourbot->getspeed() < 0)
                ourbot->changespeed (1);
            if (ourbot->getspeed() > 0)
                ourbot->changespeed (-1);
        }
    }
}

/**
	* Returns to CPU instruction IN
	*/
int engine::getfromport (unsigned char port)
{
    switch (port)
    {
    case 0 :
        return thrust;
        break;
    case 1 :
        return ourbot->getspeed();
        break;
    }
    return 0;
}
