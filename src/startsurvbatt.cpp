/***************************************************************************
                          startsurvbatt.cpp  -  description
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

#include "startsurvbatt.h"
#include <QLabel>

StartSurvBatt::StartSurvBatt() :
    StartsBatt("survbattle.save")
{
    ifteams->setText("Fast battle");
    for (int x = 0; x < 8; x++) {
        team[x]->hide();
    }
    tnumfights->setText("Number of lives:");
}
