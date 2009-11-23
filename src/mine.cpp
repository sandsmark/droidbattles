/***************************************************************************
                          mine.cpp  -  description
                             -------------------
    begin                : Fri Aug 11 2000
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

#include "mine.h"
//Added by qt3to4:
#include <QPixmap>

/**
	* Init position and load gfx
	*/
mine::mine (int x,int y, textmodeBattleArea &area,int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    time1 = 0;
    ourarea = &area;
    Xpos = x;
    Ypos = y;
    size = 1<<6;
    noncollid = 256;
    if (useUI)
    {
        erasegfx = new QPixmap;
        erasegfx->resize (8,8);
        erasegfx->fill (Qt::black);
        graphics = Pixmapholder::getpmp (6);
    }

}

/**
	* delete the graphics used
	*/
mine::~mine()
{
    if (useUI) delete erasegfx;
//	delete graphics;
}

/**
	* Returns damage inflicted
	*/
int mine::getcollisionstrength()
{
    return 70;
}

int mine::getcollisiontype()
{
    return 2;
}

/**
	* If time < 100 cycles mine is "noncolliding"
	* ie doesn't explode
	*/
int mine::returntype()
{
    if (time1 < 100)
        return noncollobject;
    else
        return 2;
}

int mine::objhit (int type,int strength)
{
    return objhitdestroyed;
}

/**
	* Show the graphics on the battlefield
	*/
void mine::showobject (QWidget *buffer,int opt=0)
{
    if (opt == 0)
        bitBlt (buffer, (getXpos() >>6)-4, (getYpos() >>6)-4,graphics);
    else
        bitBlt (buffer, (getXpos() >>6)-4, (getYpos() >>6)-4,erasegfx);
    oldX = int (Xpos);
    oldY = int (Ypos);
}

/**
	* Paint it black
	*/
void mine::eraseobject (QWidget *buffer)
{
    bitBlt (buffer, (oldX>>6)-4, (oldY>>6)-4,erasegfx);
}

/**
	* It only lives for 1000 cycles...
	*/
int mine::execute()
{
    if (time1++ > 1000)
        return destroyself;
    else
        return 0;
}

int mine::returnradar()
{
    return 3;
}
