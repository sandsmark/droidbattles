/***************************************************************************
                          chaff.cpp  -  description
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

#include "chaff.h"
//Added by qt3to4:
#include <QPixmap>

/**
	* Constructor, Init object
	*/
chaff::chaff (int X,int Y,int d,int spd, textmodeBattleArea &area, bool ui)
{
    direction = d;
    Xpos = X;
    Ypos = Y;
    speed = spd;
    useUI = ui;
    if (useUI)
    {
        erasegfx = new QPixmap(12, 12);
        erasegfx->fill(Qt::black);
        graphics = Pixmapholder::getpmp (5);
    }
    timeleft = 159;
    ourarea = &area;
    maxx = ourarea->getareainfo (0);
    maxy = ourarea->getareainfo (1);
}

/**
	* Destructor, deallocate pixmaps
	*/
chaff::~chaff()
{
    if (useUI) delete erasegfx;
//	delete graphics;
}

/**
	* Paint object
	*/
void chaff::showobject (QPixmap *buffer,int opt)
{

//	int x;
    if (opt == 0) {
        QPainter painter(buffer);
        const int width = 12;
        const int height = 12;
        const int x = (getXpos() >>6)-6;
        const int y = (getYpos() >>6)-6;
        const int sourceX = 84- (int (timeleft/20) * 12);
        painter.drawPixmap(x, y, width, height, *graphics, sourceX, 0, width, height);
//        bitBlt (buffer, (getXpos() >>6)-6, (getYpos() >>6)-6, graphics,picpos, 0, 12,12);
    }
    oldX = getXpos();
    oldY = getYpos();
}

/**
	* Paint object black
	*/
void chaff::eraseobject (QPixmap *buffer)
{
    QPainter painter(buffer);
    painter.drawPixmap((oldX>>6)-6, (oldY>>6)-6, *erasegfx);
//    bitBlt (buffer, (oldX>>6)-6, (oldY>>6)-6,erasegfx);
}

/**
	* Moves object, and deletes self when time runs out
	*/
int chaff::execute()
{
    double dira = getdir() * pi / 512;
    double tempX,tempY;
    tempX = cos (dira) * getspeed();
    tempY = sin (dira) * getspeed();
    changepos (tempX,tempY);
    timeleft--;
    if (!timeleft)
        return destroyself;
    else
        return 0;
}

/**
	* Return "exists" id that tells he's a non-colliding object
	*/
int chaff::returntype()
{
    return noncollobject;
}

/**
	* Return "is visible on radar" id
	*/
int chaff::returnradar()
{
    return 5;
}
