/***************************************************************************
                          confstruct.h  -  description
                             -------------------
    begin                : Wed Apr 19 2000
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

#ifndef CONFSTRUCT_H
#define CONFSTRUCT_H

class QString;

//Structure for holding the currently active configuration
//(Generally read from current.cfg)
struct ConfStruct
{
    void load(const QString &filename);
    void save(const QString &filename);

    int maxdev;
    int maxcost;
    int maxram;
    int ramcost[9];
    bool enabled[25];
    int cost[5][25];
    int values[5][25];
};

#endif
