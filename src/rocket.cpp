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
#include <QtMath>

Rocket::Rocket()
{
}

Rocket::~Rocket()
{
}
/**
	* Init position, gfx
	*/
Rocket::Rocket (int X,int Y,int dir,int leng,int mnum, TextmodeBattleArea &area,
                int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    mynum = mnum;
    m_direction = dir;
    m_speed = 220;
    noncollid = 256;
    Xpos = X;
    Ypos = Y;
    uX = X;
    uY = Y;
    double dira = direction() * pi / 512;
    setPosition (cos (dira) * 1500,sin (dira) * 1500);
    m_size = 16;
    countpoint = 0;
    length = leng;
    if (useUI)
    {
        for (int x=0; x<50; x++)
        {
            pointX[x] = int (Xpos);
            pointY[x] = int (Ypos);
            pointD[x] = direction() +512 + (rand() %128)-64;
        }
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill (Qt::black);
        graphics = PixmapHolder::getpmp (PixmapHolder::Rocket);
    }
}

int Rocket::objectHit (int /*type*/, int /*strength*/)
{
    return 1;
}

/**
	* Non colliding object...
	*/
ScreenObject::ObjectType Rocket::type()
{
    return ScreenObject::Collidable;
}

/**
	* Paint gfx black
	*/
void Rocket::eraseObject(QPixmap *buffer)
{
    QPainter p (buffer);
    p.setPen (QColor (0,0,0));
    int x;
    for (x=0; x<50; x++)
    {
        p.drawPoint (pointX[x]>>6,pointY[x]>>6);
    }

    p.drawPixmap((oldX>>6)-4, (oldY>>6)-4, *erasegfx);
}

/**
	* Paint the flame from the rocket
	*/
void Rocket::drawObject(QPixmap *buffer, int opt)
{
    if (opt > 0) {
        return;
    }

    QPainter p (buffer);
    pointD[countpoint] = direction() +512 + (rand() %128)-64;
    if (pointD[countpoint] > 1024) pointD[countpoint] -= 1024;
    pointX[countpoint] = int (Xpos);
    pointY[countpoint] = int (Ypos);

    if (++countpoint >= 50) countpoint = 0;
    int x;

    for (x=0; x<50; x++) {
        p.setPen (QColor (255,0,0, (rand() % 128) + 64));
        double dira = pointD[x] * pi / 512;
        pointX[x] += int (cos (dira) * 64);
        pointY[x] += int (sin (dira) * 64);
        p.drawPoint (pointX[x]>>6,pointY[x]>>6);
    }
    p.drawPixmap((int(Xpos) >> 6) - 4, (int(Ypos) >> 6) - 4, *graphics);
}

/**
	* Move rocket, and if he is at the correct position,
	* cause the explosion
	*/
int Rocket::execute()
{
    double dir = direction() * pi / 512;
    int ret = setPosition(cos(dir) * m_speed, sin(dir) * m_speed);       //Update position
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
int Rocket::setPosition(double X,double Y)
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

int Rocket::collisionType()
{
    return 2;
}

int Rocket::collisionStrength()
{
    return 0;
}

/**
	* Is not himself affected by other rockets explosions
	*/
bool Rocket::areaExplosionAffects()
{
    return false;
}

int Rocket::returnRadar()
{
    return 2;
}
