/***************************************************************************
                          ram.cpp  -  description
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

#include "ram.h"

Ram::Ram()
{
    mem = new uint8_t[1];
    numowners = 1;
    RAMamount = 1;
}

/**
	* Constructs RAM and fills the RAM
	* with contents
	*/
Ram::Ram(int amount, const uint8_t *buf)
{
    RAMamount = amount;
    mem = new uint8_t[RAMamount];
    int x;
    for (x = 0; x < RAMamount; x++) {
        mem[x] = buf[x + 256];
    }
    numowners = 1;
}

/**
	* Destructor, deletes contents
	*/
Ram::~Ram()
{
    delete[] mem;
}

/**
	* Returns byte at adress adress
	*/
uint8_t Ram::getbyte(int adress)
{
    if (adress > 0 && adress < RAMamount) {
        return mem[adress];
    }
    return 0xFF;
}

/**
	* Returns signed byte
	*/
int8_t Ram::getibyte(int adress)
{
    if (adress < RAMamount) {
        int8_t *cret = (int8_t *)&mem[adress];
        return *cret;
    }
    return 0xFF;
}

/**
	* Returns word
	*/
uint16_t Ram::getword(int adress)
{
    if (adress < RAMamount - 1) {
        //		usret = (uint16_t *)&mem[adress];
        //		return *usret;
        return mem[adress] + mem[adress + 1] * 256;
    }
    return 0xFFFF;
}

/**
	* Returns signed word
	*/
int16_t Ram::getiword(int adress)
{
    if (adress < RAMamount - 1) {
        sret = (int16_t *)&mem[adress];
        return *sret;
    }
    return 0xFFFF;
}

/**
	* Sets byte
	*/
void Ram::setbyte(int adress, uint8_t value)
{
    if (adress < RAMamount) {
        mem[adress] = value;
    }
}

/**
	* Sets word
	*/
void Ram::setword(int adress, uint16_t value)
{
    if (adress < RAMamount - 1) {
        mem[adress] = value % 256;
        mem[adress + 1] = value / 256;
        //		usret = (uint16_t *)&mem[adress];
        //		*usret = value;
    }
}

/**
	* Sets signed byte
	* (Obsolete?)
	*/
void Ram::setibyte(int adress, int8_t value)
{
    if (adress < RAMamount) {
        int8_t *cret = (int8_t *)&mem[adress];
        *cret = value;
    }
}

/**
	* Sets signed word
	* (Obsolete?)
	*/
void Ram::setiword(int adress, int16_t value)
{
    if (adress < RAMamount - 1) {
        sret = (int16_t *)&mem[adress];
        *sret = value;
    }
}

/**
	* Returns size of self
	*/
int Ram::returnsize()
{
    return RAMamount;
}

/**
	* Returns number of objects using this RAM
	*/
int Ram::getowners()
{
    return numowners;
}

/**
	* Add one user
	*/
void Ram::addowner()
{
    numowners++;
}

/**
	* Remove one user
	*/
void Ram::removeowner()
{
    numowners--;
}
