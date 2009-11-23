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

RAM::RAM()
{
    mem = new unsigned char[1];
    numowners=1;
    RAMamount=1;
}

/**
	* Constructs RAM and fills the RAM
	* with contents
	*/
RAM::RAM (int amount,unsigned char *buf)
{
    RAMamount = amount;
    mem = new unsigned char[RAMamount];
    int x;
    for (x=0; x<RAMamount; x++)
        mem[x] = buf[x+256];
    numowners=1;
}

/**
	* Destructor, deletes contents
	*/
RAM::~RAM()
{
    delete mem;
}

/**
	* Returns byte at adress adress
	*/
unsigned char RAM::getbyte (int adress)
{
    if (adress < RAMamount)
        return mem[adress];
    else
        return 0xFF;
}

/**
	* Returns signed byte
	*/
char RAM::getibyte (int adress)
{
    if (adress < RAMamount)
    {
        cret = (char *) &mem[adress];
        return *cret;
    }
    else
        return 0xFF;

}

/**
	* Returns word
	*/
unsigned short RAM::getword (int adress)
{
    if (adress < RAMamount-1)
    {
//		usret = (unsigned short *)&mem[adress];
//		return *usret;
        return mem[adress] + mem[adress+1]*256;
    }
    else
        return 0xFFFF;
}

/**
	* Returns signed word
	*/
short RAM::getiword (int adress)
{
    if (adress < RAMamount-1)
    {
        sret = (short *) &mem[adress];
        return *sret;
    }
    else
        return 0xFFFF;
}

/**
	* Sets byte
	*/
void RAM::setbyte (int adress,unsigned char value)
{
    if (adress < RAMamount)
        mem[adress] = value;
}

/**
	* Sets word
	*/
void RAM::setword (int adress,unsigned short value)
{
    if (adress < RAMamount-1)
    {
        mem[adress] = value%256;
        mem[adress + 1] = value/256;
//		usret = (unsigned short *)&mem[adress];
//		*usret = value;
    }
}

/**
	* Sets signed byte
	* (Obsolete?)
	*/
void RAM::setibyte (int adress,char value)
{
    if (adress < RAMamount)
    {
        cret = (char *) &mem[adress];
        *cret = value;
    }
}

/**
	* Sets signed word
	* (Obsolete?)
	*/
void RAM::setiword (int adress,short value)
{
    if (adress < RAMamount-1)
    {
        sret = (short *) &mem[adress];
        *sret = value;
    }
}

/**
	* Returns size of self
	*/
int RAM::returnsize()
{
    return RAMamount;
}

/**
	* Returns number of objects using this RAM
	*/
int RAM::getowners()
{
    return numowners;
}

/**
	* Add one user
	*/
void RAM::addowner()
{
    numowners++;
}

/**
	* Remove one user
	*/
void RAM::removeowner()
{
    numowners--;
}
