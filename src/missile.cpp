/***************************************************************************
                          missile.cpp  -  description
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

#include "missile.h"
//Added by qt3to4:
#include <QPixmap>

/**
	* Init position, graphics and such
	*/
Missile::Missile (int X,int Y,int dir,int owner,int mnum, TextmodeBattleArea &area, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    mynum = mnum;
    strength = 20;
    direction = dir;
    speed = 256;
    noncollid = owner;
    Xpos = X;
    Ypos = Y;
    double dira = getdir() * pi / 512;
    changepos (cos (dira) * 1500,sin (dira) * 1500);
    size = 1<<6;
    if (useUI)
    {
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill (Qt::black);
        graphics = PixmapHolder::getpmp (7);
    }
}

Missile::~Missile()
{
//	delete graphics;
    if (useUI) delete erasegfx;
}

/**
	* Move the shot one step
	*/
int Missile::execute()
{
    double dir = getdir() * pi / 512;
    return changepos (cos (dir) * getspeed(),sin (dir) * getspeed());
}

/**
	* Paint the shot black
	*/
void Missile::eraseobject (QPixmap *buffer)
{
    QPainter painter(buffer);
    painter.drawPixmap((oldX>>6)-4, (oldY>>6)-4, *erasegfx);
}

/**
	* Paint the shot on the screen
	*/
void Missile::showobject (QPixmap *buffer,int opt)
{
    QPainter painter(buffer);
    if (opt == 0) {
        painter.drawPixmap ((getXpos() >>6)-4, (getYpos() >>6)-4, *graphics);
    } else {
        painter.drawPixmap((getXpos() >>6)-4, (getYpos() >>6)-4, *erasegfx);
    }
    oldX = int (Xpos);
    oldY = int (Ypos);
}

int Missile::returntype()
{
    return 2;
}

int Missile::getcollisiontype()
{
    return 2;
}

int Missile::getcollisionstrength()
{
    return 15;
}

int Missile::objhit (int /*type*/, int /*strength*/)
{
    return objhitdestroyed;
}

/**
	* If the shot gets outside the battlefield
	* it deletes itself
	*/
int Missile::changepos (double X,double Y)
{
    oldX = int (Xpos);
    oldY = int (Ypos);
    Xpos += X;
    Ypos += Y;
    if (Xpos < 0) return destroyself;
    if (Xpos > ourarea->getareainfo (0)) return destroyself;
    if (Ypos < 0) return destroyself;
    if (Ypos > ourarea->getareainfo (1)) return destroyself;
    return 0;
}

int Missile::getsize()
{
    return 2;
}

int Missile::returnradar()
{
    return 1;
}
