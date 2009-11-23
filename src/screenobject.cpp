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

screenobject::screenobject()
{
    Xpos = -100000;
    Xpos = -100000;
    noncollid = 256;
    heatval = 0;
}

screenobject::~screenobject()
{
}

void screenobject::showobject (QWidget *buffer, int opt)
{
}

void screenobject::eraseobject (QWidget *buffer)
{
}

int screenobject::changepos (double X,double Y)
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

void screenobject::changedir (int Z)
{
    direction += Z;
    if (direction >= 1024) direction -= 1024;
    if (direction < 0) direction += 1024;
}

void screenobject::changespeed (int Z)
{
    speed += Z;
    if (speed < -75) speed = -75;
    if (speed > 100) speed = 100;
}

const int screenobject::getXpos()
{
    return int (Xpos);
}

const int screenobject::getYpos()
{
    return int (Ypos);
}

const int screenobject::getdir()
{
    return direction;
}

const int screenobject::getspeed()
{
    return speed;
}

void screenobject::setspeed (int x)
{
    speed = x;
}

int screenobject::execute()
{
    return 0;
}

int screenobject::getdevport (unsigned char port)
{
    return 0;
}

const int screenobject::getnum()
{
    return mynum;
}

void screenobject::putdevport (unsigned char port,unsigned short value)
{
}

int screenobject::objhit (int type,int strength)
{
    return 0;
}

void screenobject::addscrobject (int X,int Y,int dir,int type, int arg1,
                                 int arg2,void *arg3)
{
}

int screenobject::returntype()
{
    return 0;
}

int screenobject::iodevtobatt (int bot,int dev,int choice,int arg1,int arg2)
{
    return 0;
}

int screenobject::iodevtodev (int dev,int action,int value)
{
    return 0;
}

int screenobject::getsize()
{
    return 1;
}

int screenobject::getcollisiontype()
{
    return 0;
}

int screenobject::getcollisionstrength()
{
    return 0;
}

const char* screenobject::getdebug1()
{
    return 0;
}

const char* screenobject::getdebug2()
{
    return 0;
}

void screenobject::setdebug1 (int msg)
{
}

void screenobject::setdebug2 (int msg)
{
}

void screenobject::setextragfx (bool x)
{
    showextragfx = x;
}

void screenobject::setfuel (int x)
{
    fuelval += x;
}

int screenobject::getfuel()
{
    return fuelval;
}

int screenobject::getarmor()
{
    return armorval;
}

void screenobject::changeheat (int x)
{
    heatval += x;
    if (heatval < 0) heatval = 0;
}

int screenobject::getheat()
{
    return heatval;
}

void screenobject::setheat (int x)
{
    heatval = x;
}

int screenobject::getteam()
{
    return team;
}

void screenobject::receiveradio (int sig)
{
}

int screenobject::getmem()
{
    return 0;
}

void screenobject::addinterrupt (int inter)
{
}

struct debugcontents screenobject::returndbgcont()
{
}

bool screenobject::areaexplosionaffects()
{
    return true;
}

int screenobject::returnradar()
{
    return 0;
}

int screenobject::getcollid()
{
    return noncollid;
}

void screenobject::sendmsg (char *msg)
{
    if (useUI) emit messagechanged (msg);
}

void screenobject::objscanned (int intensity,int dir)
{
}

int screenobject::getowner()
{
    return myowner;
}

QPixmap & screenobject::getgfx()
{
    return *graphics;
}

void screenobject::setradar (int x)
{
}

void screenobject::dumpRAM()
{
}