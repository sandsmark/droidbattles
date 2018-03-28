/***************************************************************************
                          ram.h  -  description
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

#ifndef RAM_H
#define RAM_H

#include <cstdint>

/**
	* The memmodule for bots and others, mainly used by CPU devices
	* contains functions for reading/writing to memory
	* @author Andreas Agorander
	*/

class Ram
{
public:
    const int s_amounts[9] = {
        1024,
        2048,
        4096,
        8192,
        16384,
        24576,
        32768,
        49152,
        65536,
    };

    Ram();
    Ram(int amount, const uint8_t *buf);
    ~Ram();
    uint8_t getbyte(int adress);
    int8_t getibyte(int adress);
    uint16_t getword(int adress);
    int16_t getiword(int adress);
    void setbyte(int adress, uint8_t value);
    void setibyte(int adress, int8_t value);
    void setword(int adress, uint16_t value);
    void setiword(int adress, int16_t value);
    int returnsize();
    int getowners();
    void addowner();
    void removeowner();

private:
    uint8_t *mem;
    int16_t *sret;
    uint16_t RAMamount;
    int numowners;
};

#endif
