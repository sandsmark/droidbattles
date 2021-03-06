/***************************************************************************
                          engine.h  -  description
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

#ifndef ENGINE_H
#define ENGINE_H

#include "device.h"
#include "screenobject.h"

/**propulsion of the bots,makes the bot move
  *@author Andreas Agorander
  */

class Engine : public Device
{

public:
    ~Engine() override;
    Engine(ScreenObject &object, int);
    int readPort(uint8_t port) override;
    void execute() override;

private:
    int thrust;
};

#endif
