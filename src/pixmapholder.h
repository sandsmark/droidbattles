/***************************************************************************
                          pixmapholder.h  -  description
                             -------------------
    begin                : Thu Mar 1 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#ifndef PIXMAPHOLDER_H
#define PIXMAPHOLDER_H

#include <qpixmap.h>

/**
	*This class adds functions for dealing with application global pixmaps
  *@author Andreas Agorander
  */

class PixmapHolder
{
public:
    enum PixmapId {
        MainMenu = 0,
        BackButton = 1,
        Metal = 2,
        MetalBackground = 3,
        RadarMissile = 4,
        Chaff = 5,
        Mine = 6,
        Missile = 7
    };

    PixmapHolder();
    ~PixmapHolder();
    static void addpm (QString name, PixmapId num);
    static QPixmap & getpm (PixmapId num);
    static QPixmap * getpmp (PixmapId num);

private:
    static void load();
    static bool initialized;
};

#endif

