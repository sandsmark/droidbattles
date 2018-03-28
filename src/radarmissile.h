/***************************************************************************
                          radarmissile.h  -  description
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

#ifndef RADARMISSILE_H
#define RADARMISSILE_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include "ram.h"
#include "robcpu.h"
#include "steering.h"
#include "scanner.h"
#include "device.h"
#include "debugwindow.h"
/**
	* A programmable missile
  *@author Andreas Agorander
  */

class RadarMissile : public ScreenObject
{

public:

    RadarMissile (int,int,int,int,int,int,TextmodeBattleArea &,Ram *,int owner, bool ui=true);
    ~RadarMissile();
    int execute();
    void eraseObject (QPixmap *buffer);
    void drawObject (QPixmap *buffer, int opt);
    ObjectType type();
    int collisionType();
    int collisionStrength();
    int setPosition (double X,double Y);
    int objectHit (int type,int strength);
    int readDevicePort (unsigned char port);
    void writeDevicePort (unsigned char port,unsigned short value);
    int writetoBattleArea (int bot,int dev,int choice,int arg1,int arg2);
    int returnRadar();
    void createDbgWindow (int, QPlainTextEdit *, int*, int*);

private:

    TextmodeBattleArea *ourarea;
    int strength;
    Ram *ramdevice;
    Device *devices[3];
    DebugWindow* dbgWindow;
};

#endif
