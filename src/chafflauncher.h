/***************************************************************************
                          chafflauncher.h  -  description
                             -------------------
    begin                : Fri Dec 1 2000
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

#ifndef CHAFFLAUNCHER_H
#define CHAFFLAUNCHER_H

#include "device.h"
#include "screenobject.h"

/**
	* Device that sends out chaff
  *@author Andreas Agorander
  */

class ChaffLauncher : public Device
{

public:
    ChaffLauncher(ScreenObject &object, int level);
    ~ChaffLauncher();
    void execute();
    int readPort(uint8_t port);

private:
    int chaffleft;
};

#endif
