/***************************************************************************
                          scanner.h  -  description
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

#ifndef SCANNER_H
#define SCANNER_H

#include "device.h"
#include "screenobject.h"
#include <math.h>
#include <stdlib.h>
#include "commonsymbols.h"
#include <qpainter.h>
#include <qwidget.h>

/**A radar device
  *@author Andreas Agorander
  */
class scanner : public device
{
public:
    scanner (screenobject &object,int arg1,int offset);
    ~scanner();
    void execute();
    int getfromport (unsigned char port);
    void erasegfx (QWidget *buffer);
    void showgfx (QWidget *buffer);

private:
    int threshold;
    int scanshow;
    int lastpaintX;
    int lastpaintY;
    int lastpaintsize;
    int lastpaintang;
    int width;
    int maxscandist;
    int lastscandist;
    int lastscanang;
    int scantimes;
    int scantimes2;
    bool ispainted;

    int wret;
    int lastscanfreq;
    int lastscanid;
    int lastscandir;
    int lastscanspeed;

};

#endif
