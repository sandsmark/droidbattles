/***************************************************************************
                          chaff.h  -  description
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

#ifndef CHAFF_H
#define CHAFF_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include "pixmapholder.h"

/**
	* Chaff screenobject, made to fool scanners
  *@author Andreas Agorander
  */

class Chaff : public ScreenObject
{

public:
    Chaff(int X, int Y, int d, int spd, TextmodeBattleArea &area, bool ui = true);
    ~Chaff() override;
    void eraseObject(QPainter *painter) override;
    void drawObject(QPainter *painter, int opt) override;
    ObjectType type() override;
    int execute() override;
    int returnRadar() override;

private:
    int timeleft;
    TextmodeBattleArea *ourarea;
};

#endif
