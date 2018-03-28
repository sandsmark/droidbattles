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
    mem = new unsigned char[1];
    numowners = 1;
    RAMamount = 1;
}

/**
	* Constructs RAM and fills the RAM
	* with contents
	*/
Ram::Ram(int amount, const unsigned char *buf)
{
    RAMamount = amount;
    mem = new unsigned char[RAMamount];
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
unsigned char Ram::getbyte(int adress)
{
    if (adress > 0 && adress < RAMamount) {
        return mem[adress];
    }
    return 0xFF;
}

/**
	* Returns signed byte
	*/
char Ram::getibyte(int adress)
{
    if (adress < RAMamount) {
        cret = (char *)&mem[adress];
        return *cret;
    }
    return 0xFF;
}

/**
	* Returns word
	*/
unsigned short Ram::getword(int adress)
{
    if (adress < RAMamount - 1) {
        //		usret = (unsigned short *)&mem[adress];
        //		return *usret;
        return mem[adress] + mem[adress + 1] * 256;
    }
    return 0xFFFF;
}

/**
	* Returns signed word
	*/
short Ram::getiword(int adress)
{
    if (adress < RAMamount - 1) {
        sret = (short *)&mem[adress];
        return *sret;
    }
    return 0xFFFF;
}

/**
	* Sets byte
	*/
void Ram::setbyte(int adress, unsigned char value)
{
    if (adress < RAMamount) {
        mem[adress] = value;
    }
}

/**
	* Sets word
	*/
void Ram::setword(int adress, unsigned short value)
{
    if (adress < RAMamount - 1) {
        mem[adress] = value % 256;
        mem[adress + 1] = value / 256;
        //		usret = (unsigned short *)&mem[adress];
        //		*usret = value;
    }
}

/**
	* Sets signed byte
	* (Obsolete?)
	*/
void Ram::setibyte(int adress, char value)
{
    if (adress < RAMamount) {
        cret = (char *)&mem[adress];
        *cret = value;
    }
}

/**
	* Sets signed word
	* (Obsolete?)
	*/
void Ram::setiword(int adress, short value)
{
    if (adress < RAMamount - 1) {
        sret = (short *)&mem[adress];
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
