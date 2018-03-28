/***************************************************************************
                          fuel.h  -  description
                             -------------------
    begin                : Mon Apr 17 2000
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

#ifndef FUEL_H
#define FUEL_H

#include "device.h"
#include "screenobject.h"

/**The fuel for the engines, shields and beam
  *@author Andreas Agorander
  */

class Fuel : public Device
{

public:
    Fuel(ScreenObject &, int);
    ~Fuel();
    int readPort(unsigned char port);
    void execute();

private:
    int fuelintlevel;
};

#endif
