/***************************************************************************
                          startsurvbatt.h  -  description
                             -------------------
    begin                : Tue Jan 2 2001
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

#ifndef STARTSURVBATT_H
#define STARTSURVBATT_H

#include "startsbatt.h"

/**
  *@author Andreas Agorander
  */


class startsurvbatt : public startsbatt
{
    Q_OBJECT
public:
    startsurvbatt();
    ~startsurvbatt();
private slots:
    virtual void ocl();
    //numfights is numlives
    //ifteams is iffast
protected:
    virtual void loadfilesettings();
};

#endif
