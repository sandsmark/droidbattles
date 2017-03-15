/***************************************************************************
                          startdeathbatt.h  -  description
                             -------------------
    begin                : Fri Jan 5 2001
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

#ifndef STARTDEATHBATT_H
#define STARTDEATHBATT_H

#include "startsurvbatt.h"

/**
  *@author Andreas Agorander
  */

class StartDeathBatt : public StartSurvBatt
{
    Q_OBJECT
public:
    StartDeathBatt();
    ~StartDeathBatt();

protected:
    void loadfilesettings();

private slots:
    void ocl();
};

#endif
