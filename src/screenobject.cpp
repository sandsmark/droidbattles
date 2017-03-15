/***************************************************************************
                          screenobject.cpp  -  description
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

#include "screenobject.h"
//Added by qt3to4:
#include <QPixmap>

ScreenObject::ScreenObject()
{
    Xpos = -100000;
    Xpos = -100000;
    noncollid = 256;
    heatval = 0;
}

ScreenObject::~ScreenObject()
{
}

void ScreenObject::drawObject (QPixmap * /*buffer*/, int /*opt*/)
{
}

void ScreenObject::eraseObject (QPixmap * /*buffer*/)
{
}

int ScreenObject::setPosition (double X,double Y)
{
    oldX = int (Xpos);
    oldY = int (Ypos);
    Xpos += X;                   //Update position
    Ypos += Y;
    if (Xpos < 0) Xpos = 0;        //Check if we went over the borders of
    if (Xpos > maxx) Xpos = maxx;   //The battlefield
    if (Ypos < 0) Ypos = 0;
    if (Ypos > maxy) Ypos = maxy;
    return 0;
}

void ScreenObject::changeDirection (int Z)
{
    m_direction += Z;
    if (m_direction >= 1024) m_direction -= 1024;
    if (m_direction < 0) m_direction += 1024;
}

void ScreenObject::changeSpeed (int Z)
{
    m_speed += Z;
    if (m_speed < -75) m_speed = -75;
    if (m_speed > 100) m_speed = 100;
}

int ScreenObject::xPos()
{
    return int (Xpos);
}

int ScreenObject::yPos()
{
    return int (Ypos);
}

int ScreenObject::direction()
{
    return m_direction;
}

int ScreenObject::speed()
{
    return m_speed;
}

void ScreenObject::setSpeed (int x)
{
    m_speed = x;
}

int ScreenObject::execute()
{
    return 0;
}

int ScreenObject::readDevicePort (unsigned char /*port*/)
{
    return 0;
}

int ScreenObject::number()
{
    return mynum;
}

void ScreenObject::writeDevicePort (unsigned char /*port*/, unsigned short /*value*/)
{
}

int ScreenObject::objectHit (int /*type*/, int /*strength*/)
{
    return 0;
}

void ScreenObject::addScreenObject (int /*X*/, int /*Y*/, int /*dir*/, int /*type*/, int /*arg1*/,
                                 int /*arg2*/, void* /*arg3*/)
{
}

int ScreenObject::type()
{
    return 0;
}

int ScreenObject::writetoBattleArea (int /*bot*/, int /*dev*/, int /*choice*/, int /*arg1*/, int /*arg2*/)
{
    return 0;
}

int ScreenObject::writeToDevice (int /*dev*/, int /*action*/, int /*value*/)
{
    return 0;
}

int ScreenObject::size()
{
    return 1;
}

int ScreenObject::collisionType()
{
    return 0;
}

int ScreenObject::collisionStrength()
{
    return 0;
}

QString ScreenObject::getDebugMessage1()
{
    return 0;
}

QString ScreenObject::getDebugMessage2()
{
    return 0;
}

void ScreenObject::setDebugVariable1 (int /*msg*/)
{
}

void ScreenObject::setDebugVariable2 (int /*msg*/)
{
}

void ScreenObject::setextragfx (bool x)
{
    showextragfx = x;
}

void ScreenObject::setFuel (int x)
{
    fuelval += x;
}

int ScreenObject::fuel()
{
    return fuelval;
}

int ScreenObject::armor()
{
    return armorval;
}

void ScreenObject::changeHeat (int x)
{
    heatval += x;
    if (heatval < 0) heatval = 0;
}

int ScreenObject::heat()
{
    return heatval;
}

void ScreenObject::setHeat (int x)
{
    heatval = x;
}

int ScreenObject::team()
{
    return m_team;
}

void ScreenObject::writeRadio (int /*sig*/)
{
}

int ScreenObject::memorySize()
{
    return 0;
}

void ScreenObject::addInterrupt (int /*inter*/)
{
}

struct DebugContents ScreenObject::debugContents()
{
    return DebugContents();
}

bool ScreenObject::areaExplosionAffects()
{
    return true;
}

int ScreenObject::returnRadar()
{
    return 0;
}

int ScreenObject::collisionId()
{
    return noncollid;
}

void ScreenObject::sendMessage (char *msg)
{
    if (useUI) emit messagechanged (msg);
}

void ScreenObject::objectScanned (int /*intensity*/, int /*dir*/)
{
}

int ScreenObject::owner()
{
    return myowner;
}

QPixmap & ScreenObject::getgfx()
{
    return *graphics;
}

void ScreenObject::setRadar (int /*x*/)
{
}

void ScreenObject::dumpRam()
{
}
