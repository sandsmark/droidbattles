/***************************************************************************
                          communication.h  -  description
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "device.h"
#include "screenobject.h"

/**
	* This device enables communication between bots in the same team
  *@author Andreas Agorander
  */

class communication : public device
{

public:
    communication (screenobject &object);
    ~communication();
    int getfromport (unsigned char port);
    void execute();
    void dospecial (int x,int y);

private:
    int msglist[32];
    int nummsg;
    int receiver;
};

#endif
