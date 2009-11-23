/***************************************************************************
                          matchresult.h  -  description
                             -------------------
    begin                : Thu Nov 2 2000
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

//Structure for holding results during tournaments

#ifndef MATCHRESULT_H
#define MATCHRESULT_H

struct matchresult
{
    int secbot;
    int mainbotwins;
    int secbotwins;
    int mainbot;
};

#endif