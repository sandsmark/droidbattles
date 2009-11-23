/***************************************************************************
                          device.h  -  description
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

#ifndef DEVICE_H
#define DEVICE_H

#include "screenobject.h"
#include "debugcontents.h"

/**Baseclass for all sub-bot-devices
  *@author Andreas Agorander
  */

class device
{

public:

    device();
    virtual ~device();
    device (screenobject &object);
    void addinport (unsigned char port,unsigned short value);
    void setrelang (int);
    virtual void execute();
    virtual int getfromport (unsigned char port);
    virtual int absorbhit (int str,int ifint);
    virtual void erasegfx (QWidget *buffer);
    virtual void showgfx (QWidget *buffer);
    virtual int returntype();
    virtual int returnspecial();
    virtual struct debugcontents returndbg();
    virtual void dospecial (int, int=0);
protected:

    void moveportstack (int port);

    int portstack[4][4];
    bool stacktaken[4][4];
    screenobject *ourbot;
    int relang;
    int ourlevel;
    bool intenabled;
    bool intenabled2;

};


#endif
