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

class Pixmapholder
{
public:
    Pixmapholder();
    ~Pixmapholder();
    static void addpm (QString name, int num);
    static QPixmap & getpm (int num);
    static QPixmap * getpmp (int num);
};

#endif
