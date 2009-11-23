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


/**
	* The memmodule for bots and others, mainly used by CPU devices
	* contains functions for reading/writing to memory
	* @author Andreas Agorander
	*/

class RAM
{

public:

    RAM();
    RAM (int amount,unsigned char *buf);
    ~RAM();
    unsigned char getbyte (int adress);
    char getibyte (int adress);
    unsigned short getword (int adress);
    short getiword (int adress);
    void setbyte (int adress, unsigned char value);
    void setibyte (int adress, char value);
    void setword (int adress, unsigned short value);
    void setiword (int adress, short value);
    int returnsize();
    int getowners();
    void addowner();
    void removeowner();

private:

    unsigned char *mem;
    unsigned char *ucret;
    char *cret;
    unsigned short *usret;
    short *sret;
    unsigned short RAMamount;
    int numowners;

};

#endif
