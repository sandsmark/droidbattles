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

class engine : public device
{

public:

    ~engine();
    engine (screenobject &object,int);
    int getfromport (unsigned char port);
    void execute();

private:

    int thrust;

};

#endif
