/***************************************************************************
                          shield.h  -  description
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

#ifndef SHIELD_H
#define SHIELD_H

#include "device.h"
#include <qpainter.h>
#include "screenobject.h"
#include <qwidget.h>

/**
	* Shield device that absorbs damage
  *@author Andreas Agorander
  */

class Shield : public Device
{

public:
    Shield(ScreenObject &object, int arg1);
    ~Shield();
    int absorbHit(int strength, int ifint);
    void execute();
    int readPort(uint8_t port);
    void draw(QPainter *painter);
    void erase(QPainter *painter);

private:
    int ourlevel;
    bool Isup;
    int lastpaintX;
    int lastpaintY;
    bool ispainted;
};

#endif
