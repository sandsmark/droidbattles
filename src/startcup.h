/***************************************************************************
                          startcup.h  -  description
                             -------------------
    begin                : Mon Jan 1 2001
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

#ifndef STARTCUP_H
#define STARTCUP_H

#include "starttournament.h"
#include <qmessagebox.h>

/**
  *@author Andreas Agorander
  */

class startcup : public starttournament
{
    Q_OBJECT
public:
    startcup();
    ~startcup();
private slots:
    void ocl();

};

#endif
