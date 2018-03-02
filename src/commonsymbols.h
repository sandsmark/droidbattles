/***************************************************************************
                          commonsymbols.h  -  description
                             -------------------
    begin                : Mon Apr 3 2000
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

#ifndef COMMONSYMBOLS_H
#define COMMONSYMBOLS_H

#include <qstring.h>

//global variabel for textmode...


//This file contains all Constants used

//constants for cpu registers
const int eip=5;
const int ax=1;
const int bx=2;
const int cx=3;
const int dx=4;
const int sp=9;
const int bp=8;
const int al=2;
const int ah=3;
const int bl=4;
const int bh=5;
const int cl=6;
const int ch=7;
const int dl=8;
const int dh=9;
const int di=6;
const int si=7;
const int flags=0;


const double pi=3.14159265358979;
const int portsperdev = 4;

//Indexes for the interrupts
const int hitinterrupt = 0;
const int timeinterrupt = 1;
const int msginterrupt = 2;
const int armlevelint = 3;
const int fuellevelint = 4;

//Flag register operation constants
const int setequalflag = 0x8000;
const int setaboveflag = 0x2000;
const int setbelowflag = 0x4000;
const int setinterruptflag = 0x0400;

const int aboveflag = 0x2000;
const int belowflag = 0x4000;
const int equalflag = 0x8000;

const int clearequalflags = 0x9FFF;
const int clearaboveflags = 0x3FFF;
const int clearbelowflags = 0x5FFF;
const int setunequalflag = 0x7FFF;
const int clearinterruptflag = 0xFBFF;

//Device type-code constants
const int armortype = 99;
const int CPUtype = 9;
const int CPUwithint = 5;
const int scanwarntype = 11;
const int collenabled = 256;

const int maxobjects = 255;
const int maxbots = 8;
const int maxteams = 4;

const int firstrun = 0;
const int notfirstround = 1;

const int minstartdistance = 2000;

const double toradians = pi/512;
const double tobotgrades = 512/pi;
const int doesexist = 1;
const int doesnotexist = 0;
const int debugbot = 7;

//Assembler Instruction declaration constants
const int none = 0;
const int val = 3;
const int memc = 4;
const int reg = 5;
const int mreg = 13;
const int bit8 = 8;
const int bit16 = 16;
const int bit0 = 0;
const int NUMDEV = 20;
const int numdev = 20;

//Miscellaneous
const int maxbeamlength = 8000;
const int minbeamlength = 1100;
const int beamdamage = 7;

const int objhitdestroyed = 1;
const int objhitnotdestroyed = 0;
const int destroyself = -1;
const int seenbyradar = 1;

const int noncollobject = -1;

#endif
