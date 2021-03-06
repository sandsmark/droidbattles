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
#include <QtMath>

/**
	* Init position, graphics and such
	*/
Missile::Missile(int X, int Y, int dir, int owner, int mnum, TextmodeBattleArea &area, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    mynum = mnum;
    strength = 20;
    m_direction = dir;
    m_speed = 256;
    noncollid = owner;

    oldX = X;
    oldY = Y;
    double dira = direction() * M_PI / 512;
    Xpos = X + cos(dira) * 1500;
    Ypos = Y + sin(dira) * 1500;

    if (useUI) {
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill(Qt::black);
        graphics = PixmapHolder::getpmp(PixmapHolder::Missile);
    }
}

Missile::~Missile()
{
    //	delete graphics;
    if (useUI) {
        delete erasegfx;
    }
}

/**
	* Move the shot one step
	*/
int Missile::execute()
{
    double dir = direction() * M_PI / 512;
    return setPosition(cos(dir) * speed(), sin(dir) * speed());
}

/**
	* Paint the shot black
	*/
void Missile::eraseObject(QPainter *painter)
{
    painter->drawPixmap((oldX >> 6) - 4, (oldY >> 6) - 4, *erasegfx);
}

/**
	* Paint the shot on the screen
	*/
void Missile::drawObject(QPainter *painter, int opt)
{
    if (opt > 0) {
        return;
    }

    painter->drawPixmap((xPos() >> 6) - 4, (yPos() >> 6) - 4, *graphics);
    oldX = int(Xpos);
    oldY = int(Ypos);
}

ScreenObject::ObjectType Missile::type()
{
    return ScreenObject::Collidable;
}

int Missile::collisionType()
{
    return 2;
}

int Missile::collisionStrength()
{
    return 15;
}

int Missile::objectHit(int /*type*/, int /*strength*/)
{
    return objhitdestroyed;
}

/**
	* If the shot gets outside the battlefield
	* it deletes itself
	*/
int Missile::setPosition(double X, double Y)
{
    oldX = int(Xpos);
    oldY = int(Ypos);
    Xpos += X;
    Ypos += Y;
    if (Xpos < 0) {
        return destroyself;
    }
    if (Xpos > ourarea->getareainfo(0)) {
        return destroyself;
    }
    if (Ypos < 0) {
        return destroyself;
    }
    if (Ypos > ourarea->getareainfo(1)) {
        return destroyself;
    }
    return 0;
}

int Missile::returnRadar()
{
    return 1;
}
