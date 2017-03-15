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
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <unistd.h>
#include "installdir.h"
#include "pixmapholder.h"

/**
	* the shots from the plasmagun
  *@author Andreas Agorander
  */

class Missile : public ScreenObject
{

public:

    Missile (int X,int Y,int dir,int owner,int mynum,TextmodeBattleArea &area, bool ui = true);
    ~Missile();
    int execute();
    void eraseObject (QPixmap *buffer);
    void drawObject (QPixmap *buffer, int opt = 0);
    int type();
    int collisionType();
    int collisionStrength();
    int setPosition (double X,double Y);
    int objectHit (int type,int strength);
    int size();
    int returnRadar();

private:

    int strength;
    TextmodeBattleArea *ourarea;

};

#endif
