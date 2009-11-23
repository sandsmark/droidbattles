/***************************************************************************
                          communication.cpp  -  description
                             -------------------
    begin                : Sun Jul 16 2000
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

#include "communication.h"

/**
	* Constructor, inits device
	*/
communication::communication (screenobject &object)
{
    ourbot = &object;
    int x;
    for (x=0; x<32; x++)
        msglist[x] = 0;
    nummsg = 0;
    int count;
    int count2;
    intenabled = false;
    for (count=0; count<4; count++)
    {
        for (count2=0; count2<4; count2++)
        {
            stacktaken[count][count2]=false;
            portstack[count][count2]=0;
        }
    }
}

/**
	* Destructor, does nothing
	*/
communication::~communication()
{
}

/**
	* Checks for port orders
	*/
void communication::execute()
{
    //First port, set receiver
    if (stacktaken[0][0] == true)
    {
        receiver = portstack[0][0];
        moveportstack (0);
    }

    //Second port... send number
    if (stacktaken[1][0] == true)
    {
        int numbertosend = portstack[1][0];
        moveportstack (1);
        ourbot->iodevtobatt (ourbot->getteam(),0,7,numbertosend,receiver);
    }

    //Third port, set interrupt enable/disable
    if (stacktaken[2][0] == true)
    {
        intenabled = portstack[2][0];
        moveportstack (2);
    }

}

/**
	* Returns messages to CPU instruktion IN
	*/
int communication::getfromport (unsigned char port)
{
    int msg;
    switch (port)
    {
    case 0 :
        return nummsg;
        break;
    case 1 :
        msg = msglist[0];
        for (int x=0; x<31; x++)
            msglist[x] = msglist[x+1];
        nummsg--;
        return msglist[0];
        break;
    case 2 :
        return intenabled;
        break;
    case 3 :
        return ourbot->getnum();
        break;
    }
    return 0;
}

void communication::dospecial (int x,int y)
{
    if (nummsg < 32)
        msglist[nummsg++] = x;
    if (intenabled)
        ourbot->addinterrupt (msginterrupt);
}