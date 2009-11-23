/***************************************************************************
                          rocket.cpp  -  description
                             -------------------
    begin                : Wed Nov 1 2000
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

#include "rocket.h"

rocket::rocket()
{
}

rocket::~rocket()
{
}
/**
	* Init position, gfx
	*/
rocket::rocket (int X,int Y,int dir,int leng,int mnum, textmodeBattleArea &area,
                int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    mynum = mnum;
    direction = dir;
    speed = 220;
    noncollid = 256;
    Xpos = X;
    Ypos = Y;
    uX = X;
    uY = Y;
    double dira = getdir() * pi / 512;
    changepos (cos (dira) * 1500,sin (dira) * 1500);
    size = 1<<6;
    countpoint = 0;
    length = leng;
    if (useUI)
    {
        for (int x=0; x<50; x++)
        {
            pointX[x] = int (Xpos);
            pointY[x] = int (Ypos);
            pointD[x] = getdir() +512 + (rand() %128)-64;
        }
    }
}

int rocket::objhit (int type,int strength)
{
    return 1;
}

/**
	* Non colliding object...
	*/
int rocket::returntype()
{
    return noncollobject;
}

/**
	* Paint gfx black
	*/
void rocket::eraseobject (QWidget *buffer)
{
    QPainter p (buffer);
    p.setPen (QColor (0,0,0));
    int x;
    for (x=0; x<50; x++)
    {
        p.drawPoint (pointX[x]>>6,pointY[x]>>6);
    }
}

/**
	* Paint the flame from the rocket
	*/
void rocket::showobject (QWidget *buffer, int opt)
{
    QPainter p (buffer);
    p.setPen (QColor (255,0,0));
    pointD[countpoint] = getdir() +512 + (rand() %128)-64;
    if (pointD[countpoint] > 1024) pointD[countpoint] -= 1024;
    pointX[countpoint] = int (Xpos);
    pointY[countpoint] = int (Ypos);
    if (++countpoint >= 50) countpoint = 0;
    int x;
    for (x=0; x<50; x++)
    {
        double dira = pointD[x] * pi / 512;
        pointX[x] += int (cos (dira) * 64);
        pointY[x] += int (sin (dira) * 64);
        p.drawPoint (pointX[x]>>6,pointY[x]>>6);
    }
}

/**
	* Move rocket, and if he is at the correct position,
	* cause the explosion
	*/
int rocket::execute()
{
    double dir = getdir() * pi / 512;
    int ret = changepos (cos (dir) * speed,sin (dir) * speed);       //Update position
    int dist = int (sqrt ( (Xpos-uX) * (Xpos-uX) + (Ypos-uY) * (Ypos-uY)));
    if (dist > length)
    {
        ourarea->explosions (Xpos,Ypos,3500,120,mynum);
        return destroyself;
    }
    return ret;
}

/**
	* Move, and if he moved outside, destroy self
	*/
int rocket::changepos (double X,double Y)
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

int rocket::getcollisiontype()
{
    return 2;
}

int rocket::getcollisionstrength()
{
    return 0;
}

int rocket::getsize()
{
    return 2;
}

/**
	* Is not himself affected by other rockets explosions
	*/
bool rocket::areaexplosionaffects()
{
    return false;
}

int rocket::returnradar()
{
    return 2;
}
