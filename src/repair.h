/***************************************************************************
                          repair.h  -  description
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

#ifndef REPAIR_H
#define REPAIR_H

#include "device.h"
#include "screenobject.h"

/**
	* Device that repairs your bot
  *@author Andreas Agorander
  */

class Repair : public Device
{

public:
    Repair (ScreenObject &object,int arg1);
    ~Repair();
    void execute();
    int getfromport (unsigned char port);
private:
    int repaircycles;
};

#endif
