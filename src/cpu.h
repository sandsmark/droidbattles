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
#include "device.h"
#include "qfile.h"

/**
	*Baseclass for all the CPU:s
  *@author Andreas Agorander
  */
class CPU : public Device
{
public:
    CPU();
    CPU(Ram &ramdev, ScreenObject &object);
    virtual ~CPU();
    virtual void callobout(uint8_t one, uint16_t two);
    virtual int callobin(uint8_t one);
    virtual void sendmsg(char *msg);
    virtual int writefile(int start, int length, int adress);
    virtual int readfile(int start, int length, int adress);
    virtual void execinstr();
    virtual int readPort(uint8_t port);

protected:
    Ram *mem;
    uint16_t *registers;
    uint8_t *bit8reg;
    int16_t *iregisters;
    int8_t *ibit8reg;
    int speed;
    int8_t cyclesleft;
    int bootmem;
    uint16_t stackmem;
    //Table over latencies for different opcodes
    uint8_t instrlatency[256];
    //List of adresses executed last cycle
    int lastexecmem[30];
};

#endif
