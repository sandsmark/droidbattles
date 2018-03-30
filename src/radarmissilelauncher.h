/***************************************************************************
                          radarmissilelauncher.h  -  description
                             -------------------
    begin                : Fri Aug 11 2000
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

#ifndef RADARMISSILELAUNCHER_H
#define RADARMISSILELAUNCHER_H

#include "device.h"
#include "screenobject.h"
#include "ram.h"
/**
	* Device that launches radarmissiles
  *@author Andreas Agorander
  */

class RadarMissileLauncher : public Device
{

public:
    RadarMissileLauncher(ScreenObject &object, int level, Ram *memdevice,
                         int offset);
    ~RadarMissileLauncher() override;
    int readPort(uint8_t port) override;
    void execute() override;

private:
    int reloadtime;
    uint16_t bootmem;
    uint16_t stackmem;
    Ram *memd;
};

#endif
