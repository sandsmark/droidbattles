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
Mine::Mine (int x,int y, TextmodeBattleArea &area,int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    time1 = 0;
    ourarea = &area;
    Xpos = x;
    Ypos = y;
    m_size = 1<<6;
    noncollid = 256;
    if (useUI)
    {
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill (Qt::black);
        graphics = PixmapHolder::getpmp (6);
    }

}

/**
	* delete the graphics used
	*/
Mine::~Mine()
{
    if (useUI) delete erasegfx;
//	delete graphics;
}

/**
	* Returns damage inflicted
	*/
int Mine::collisionStrength()
{
    return 70;
}

int Mine::collisionType()
{
    return 2;
}

/**
	* If time < 100 cycles mine is "noncolliding"
	* ie doesn't explode
	*/
int Mine::type()
{
    if (time1 < 100)
        return noncollobject;
    else
        return 2;
}

int Mine::objectHit (int /*type*/,int /*strength*/)
{
    return objhitdestroyed;
}

/**
	* Show the graphics on the battlefield
	*/
void Mine::drawObject (QPixmap *buffer,int opt=0)
{
    QPainter painter(buffer);

    if (opt == 0) {
        painter.drawPixmap((xPos() >>6)-4, (yPos() >>6)-4, *graphics);
    } else {
        painter.drawPixmap((xPos() >>6)-4, (yPos() >>6)-4, *erasegfx);
    }
    oldX = int (Xpos);
    oldY = int (Ypos);
}

/**
	* Paint it black
	*/
void Mine::eraseObject (QPixmap *buffer)
{
    QPainter painter(buffer);
    painter.drawPixmap((oldX>>6)-4, (oldY>>6)-4, *erasegfx);
}

/**
	* It only lives for 1000 cycles...
	*/
int Mine::execute()
{
    if (time1++ > 1000)
        return destroyself;
    else
        return 0;
}

int Mine::returnRadar()
{
    return 3;
}
