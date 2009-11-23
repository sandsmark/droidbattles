/***************************************************************************
                          cpu.h  -  description
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

#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include "screenobject.h"
#include "commonsymbols.h"
#include "debugcontents.h"
#include <stdlib.h>
#include <math.h>
#include "device.h"
#include "qfile.h"

/**
	*Baseclass for all the CPU:s
  *@author Andreas Agorander
  */
class CPU : public device
{
public:

    CPU();
    CPU (RAM &ramdev,screenobject &object);
    virtual ~CPU();
    virtual void callobout (unsigned char one, unsigned short two);
    virtual int callobin (unsigned char one);
    virtual void sendmsg (char *msg);
    virtual int writefile (int start,int length,int adress);
    virtual int readfile (int start,int length,int adress);
    virtual void execinstr();
    virtual int getfromport (unsigned char port);

protected:

    RAM *mem;
    unsigned short *registers;
    unsigned char *bit8reg;
    signed short *iregisters;
    signed char *ibit8reg;
    int speed;
    char cyclesleft;
    int bootmem;
    unsigned short stackmem;
    //Table over latencies for different opcodes
    char instrlatency[256];
    //List of adresses executed last cycle
    int lastexecmem[30];
};

#endif
