/***************************************************************************
                          scandetect.h  -  description
                             -------------------
    begin                : Sat Dec 9 2000
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

#ifndef SCANDETECT_H
#define SCANDETECT_H

#include "device.h"
#include "screenobject.h"

/**
	* Device that counts the times you've been scanned and can give you some
	* info about the last scan
  *@author Andreas Agorander
  */

class scandetect : public device
{
public:
    scandetect (screenobject &object);
    ~scandetect();
    int getfromport (unsigned char port);
    void execute();
    int returntype();
    void dospecial (int,int);
private:
    int numscans;
    int lastscanintensity;
    int lastscandir;
};

#endif
