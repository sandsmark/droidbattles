/***************************************************************************
                          missile.h  -  description
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

#ifndef MISSILE_H
#define MISSILE_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include <qwidget.h>
#include "commonsymbols.h"
#include "pixmapholder.h"

/**
	* the shots from the plasmagun
  *@author Andreas Agorander
  */

class Missile : public ScreenObject
{

public:
    Missile(int X, int Y, int dir, int owner, int mnum, TextmodeBattleArea &area, bool ui = true);
    ~Missile() override;
    int execute() override;
    void eraseObject(QPainter *painter) override;
    void drawObject(QPainter *painter, int opt) override;
    ObjectType type() override;
    int collisionType() override;
    int collisionStrength() override;
    int setPosition(double X, double Y) override;
    int objectHit(int type, int strength) override;
    int returnRadar() override;

private:
    int strength;
    TextmodeBattleArea *ourarea;
};

#endif
