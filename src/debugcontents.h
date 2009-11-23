/***************************************************************************
                          debugcontents.h  -  description
                             -------------------
    begin                : Fri Nov 3 2000
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

#ifndef DEBUGCONTENTS_H
#define DEBUGCONTENTS_H

//Structure constructed to contain info about a CPU in a special instant
//(For the debug window in a "quick battle")

struct debugcontents
{

    unsigned short flags;

    unsigned short ax;
    unsigned short bx;
    unsigned short cx;
    unsigned short dx;
    unsigned short sp;
    unsigned short si;
    unsigned short di;
    unsigned short bp;
    unsigned short ip;

    unsigned char ipcontents[9];
    unsigned char spcontents[9];
    unsigned char sicontents[9];
    unsigned char dicontents[9];

    int execmem[30];

};


#endif
