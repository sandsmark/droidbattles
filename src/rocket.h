/***************************************************************************
                          rocket.h  -  description
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

#ifndef ROCKET_H
#define ROCKET_H

#include "screenobject.h"
#include "textmodebattlearea.h"

/**
	* AS-rocket object
  *@author Andreas Agorander
  */

class Rocket : public ScreenObject
{

public:
    Rocket();
    ~Rocket() override;
    Rocket(int X, int Y, int dir, int leng, int mnum, TextmodeBattleArea &area,
           int owner, bool ui = true);
    int objectHit(int type, int strength) override;
    ObjectType type() override;
    void eraseObject(QPainter *painter) override;
    void drawObject(QPainter *painter, int opt) override;
    int execute() override;
    int setPosition(double X, double Y) override;
    int collisionType() override;
    int collisionStrength() override;
    bool areaExplosionAffects() override;
    int returnRadar() override;

private:
    int length;
    int uX;
    int uY;
    int pointX[50];
    int pointY[50];
    int pointD[50];
    int countpoint;
    TextmodeBattleArea *ourarea;
};

#endif
