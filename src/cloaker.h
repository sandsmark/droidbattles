/***************************************************************************
                          cloaker.h  -  description
                             -------------------
    begin                : Wed Jan 31 2001
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

#ifndef CLOAKER_H
#define CLOAKER_H

#include "device.h"
#include "screenobject.h"

/**
  *@author Andreas Agorander
  */

class cloaker : public device
{

public:
    cloaker (screenobject &object, int arg1);
    ~cloaker();
    void execute();
private:
    bool cloakon;
};

#endif
