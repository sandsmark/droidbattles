/***************************************************************************
                          explosion.h  -  description
                             -------------------
    begin                : Sun Jul 16 2000
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

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "screenobject.h"
#include <qpainter.h>
#include <qwidget.h>
#include "battlearea.h"
/**
	* The yellow circle that on the battlefield symbolizes an explosion
  *@author Andreas Agorander
  */

class Explosion : public ScreenObject
{

public:
    Explosion(int X, int Y, BattleArea &area);
    ~Explosion();
    int execute();
    void eraseObject(QPixmap *buffer);
    void drawObject(QPixmap *buffer, int opt);
    ObjectType type();

private:
    int cycle;
    BattleArea *ourarea;
};

#endif
