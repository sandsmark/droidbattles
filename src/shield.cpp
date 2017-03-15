/***************************************************************************
                          shield.cpp  -  description
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

#include "shield.h"

Shield::Shield (ScreenObject &object, int arg1)
{
    ourbot = &object;
    ourlevel = arg1;
    Isup = false;
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

Shield::~Shield()
{
}

/**
	* Set shield up/down
	* if shield is up, use fuel
	*/
void Shield::execute()
{
    if (stacktaken[0][0] == true)
    {
        Isup = portstack[0][0];
        moveportstack (0);
    }
    if (ourbot->getfuel() <= 3) Isup = false;
    if (Isup == true)
    {
        ourbot->setfuel (-4);
        ourbot->changeheat (1);
    }
}

int Shield::absorbhit (int strength, int /*ifint*/)
{
    if (Isup == true)
    {
        int strabsorb = int (strength * ourlevel * 0.01);
        if (strabsorb > ourlevel) strabsorb = ourlevel;
        ourbot->changeheat (strabsorb*4);
        return (strength-strabsorb);
    }
    return strength;
}

int Shield::getfromport (unsigned char port)
{
    switch (port)
    {
    case 0 :
        return Isup;
        break;
    }
    return 0;
}

/**
	* If shield is up, paint blue circle
	*/
void Shield::showgfx (QPainter *painter)
{
    if (Isup == true)
    {
        painter->setPen (QColor (0,0,255));
        painter->drawEllipse ( (ourbot->getXpos() >>6)-16, (ourbot->getYpos() >>6)-16, 32, 32);
        lastpaintX = (ourbot->getXpos() >>6)-16;
        lastpaintY = (ourbot->getYpos() >>6)-16;
        ispainted = true;
    }
}

/**
	* paint shield black
	*/
void Shield::erasegfx (QPainter *painter)
{
    if (ispainted == true)
    {
        painter->setPen (QColor (0,0,0));
        painter->drawEllipse (lastpaintX,lastpaintY,32,32);
        ispainted = false;
    }
}
