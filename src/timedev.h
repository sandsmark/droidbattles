/***************************************************************************
                          timedev.h  -  description
                             -------------------
    begin                : Tue Jul 11 2000
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

#ifndef TIMEDEV_H
#define TIMEDEV_H

#include "device.h"
#include "screenobject.h"
/**
	* Device that keeps track of time
  *@author Andreas Agorander
  */

class TimeDev : public Device
{

public:
    TimeDev(ScreenObject &);
    ~TimeDev();
    void execute();
    int readPort(uint8_t port);

private:
    int timecount;
    int interrupttime;
};

#endif
