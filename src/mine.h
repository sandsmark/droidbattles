/***************************************************************************
                          mine.h  -  description
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

#ifndef MINE_H
#define MINE_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include <qwidget.h>
#include "pixmapholder.h"
/**
	* The small explosive devices that lays on the ground
  *@author Andreas Agorander
  */

class Mine : public ScreenObject
{

public:
    Mine(int, int, TextmodeBattleArea &, int owner, bool ui = true);
    ~Mine() override;
    ObjectType type() override;
    int execute() override;
    int collisionType() override;
    int collisionStrength() override;
    int objectHit(int, int) override;
    void drawObject(QPainter *painter, int) override;
    void eraseObject(QPainter *painter) override;
    int returnRadar() override;

private:
    int time1;
    TextmodeBattleArea *ourarea;
};

#endif
