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

#include <cstdint>

//Structure constructed to contain info about a CPU in a special instant
//(For the debug window in a "quick battle")

struct DebugContents
{

    uint16_t flags;

    uint16_t ax;
    uint16_t bx;
    uint16_t cx;
    uint16_t dx;
    uint16_t sp;
    uint16_t si;
    uint16_t di;
    uint16_t bp;
    uint16_t ip;

    uint8_t ipcontents[9];
    uint8_t spcontents[9];
    uint8_t sicontents[9];
    uint8_t dicontents[9];

    int execmem[30];
};

#endif
