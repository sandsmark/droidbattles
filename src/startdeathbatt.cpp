/***************************************************************************
                          startdeathbatt.cpp  -  description
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

#include "startdeathbatt.h"
#include <QTextStream>
#include <QLabel>

StartDeathBatt::StartDeathBatt() :
    StartsBatt("deathbattle.save")
{
    ifteams->setText ("Fast battle");
    tnumfights->setText ("Number of frags:");
}
