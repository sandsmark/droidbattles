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

void ScreenObject::showobject (QPixmap * /*buffer*/, int /*opt*/)
{
}

void ScreenObject::eraseobject (QPixmap * /*buffer*/)
{
}

int ScreenObject::changepos (double X,double Y)
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

void ScreenObject::changedir (int Z)
{
    direction += Z;
    if (direction >= 1024) direction -= 1024;
    if (direction < 0) direction += 1024;
}

void ScreenObject::changespeed (int Z)
{
    speed += Z;
    if (speed < -75) speed = -75;
    if (speed > 100) speed = 100;
}

int ScreenObject::getXpos()
{
    return int (Xpos);
}

int ScreenObject::getYpos()
{
    return int (Ypos);
}

int ScreenObject::getdir()
{
    return direction;
}

int ScreenObject::getspeed()
{
    return speed;
}

void ScreenObject::setspeed (int x)
{
    speed = x;
}

int ScreenObject::execute()
{
    return 0;
}

int ScreenObject::getdevport (unsigned char /*port*/)
{
    return 0;
}

int ScreenObject::getnum()
{
    return mynum;
}

void ScreenObject::putdevport (unsigned char /*port*/, unsigned short /*value*/)
{
}

int ScreenObject::objhit (int /*type*/, int /*strength*/)
{
    return 0;
}

void ScreenObject::addscrobject (int /*X*/, int /*Y*/, int /*dir*/, int /*type*/, int /*arg1*/,
                                 int /*arg2*/, void* /*arg3*/)
{
}

int ScreenObject::returntype()
{
    return 0;
}

int ScreenObject::iodevtobatt (int /*bot*/, int /*dev*/, int /*choice*/, int /*arg1*/, int /*arg2*/)
{
    return 0;
}

int ScreenObject::iodevtodev (int /*dev*/, int /*action*/, int /*value*/)
{
    return 0;
}

int ScreenObject::getsize()
{
    return 1;
}

int ScreenObject::getcollisiontype()
{
    return 0;
}

int ScreenObject::getcollisionstrength()
{
    return 0;
}

QString ScreenObject::getdebug1()
{
    return 0;
}

QString ScreenObject::getdebug2()
{
    return 0;
}

void ScreenObject::setdebug1 (int /*msg*/)
{
}

void ScreenObject::setdebug2 (int /*msg*/)
{
}

void ScreenObject::setextragfx (bool x)
{
    showextragfx = x;
}

void ScreenObject::setfuel (int x)
{
    fuelval += x;
}

int ScreenObject::getfuel()
{
    return fuelval;
}

int ScreenObject::getarmor()
{
    return armorval;
}

void ScreenObject::changeheat (int x)
{
    heatval += x;
    if (heatval < 0) heatval = 0;
}

int ScreenObject::getheat()
{
    return heatval;
}

void ScreenObject::setheat (int x)
{
    heatval = x;
}

int ScreenObject::getteam()
{
    return team;
}

void ScreenObject::receiveradio (int /*sig*/)
{
}

int ScreenObject::getmem()
{
    return 0;
}

void ScreenObject::addinterrupt (int /*inter*/)
{
}

struct DebugContents ScreenObject::returndbgcont()
{
    return DebugContents();
}

bool ScreenObject::areaexplosionaffects()
{
    return true;
}

int ScreenObject::returnradar()
{
    return 0;
}

int ScreenObject::getcollid()
{
    return noncollid;
}

void ScreenObject::sendmsg (char *msg)
{
    if (useUI) emit messagechanged (msg);
}

void ScreenObject::objscanned (int /*intensity*/, int /*dir*/)
{
}

int ScreenObject::getowner()
{
    return myowner;
}

QPixmap & ScreenObject::getgfx()
{
    return *graphics;
}

void ScreenObject::setradar (int /*x*/)
{
}

void ScreenObject::dumpRAM()
{
}
