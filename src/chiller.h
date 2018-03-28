/***************************************************************************
                          chiller.h  -  description
                             -------------------
    begin                : Sat Jan 13 2001
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

#ifndef CHILLER_H
#define CHILLER_H

#include "device.h"

/**
  *@author Andreas Agorander
  */

class Chiller : public Device
{
public:
    Chiller(ScreenObject &object, int arg1);
    ~Chiller();
    void execute();

private:
    bool ison;
    int heatdiss;
};

#endif
