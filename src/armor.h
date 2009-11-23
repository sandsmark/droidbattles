/***************************************************************************
                          armor.h  -  description
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

#ifndef ARMOR_H
#define ARMOR_H

#include "device.h"
#include "screenobject.h"

/**The protection of the bots
  *@author Andreas Agorander
  */

class armor : public device
{

public:

    armor (screenobject &object,int);
    ~armor();
    void execute();
    int absorbhit (int str,int ifint);
    int returntype();
    int returnspecial();
    int getfromport (unsigned char port);
    void dospecial (int,int=0);
private:

    int strength;
    int orstrength;
    int armorintlevel;
    int heatintlevel;
};

#endif
