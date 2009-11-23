/***************************************************************************
                          quickconf.h  -  description
                             -------------------
    begin                : Mon Oct 30 2000
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

#ifndef QUICKCONF_H
#define QUICKCONF_H

#include <qwidget.h>
#include "startsbatt.h"
/**
	* Dialog that configs quick battle
  *@author Andreas Agorander
  */

class quickconf : public startsbatt
{

    Q_OBJECT

public:
    quickconf();
    ~quickconf();

private slots:

    void ocl();
    void ccl();

signals:
    void cancelclicked();
};

#endif
