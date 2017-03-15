/***************************************************************************
                          device.cpp  -  description
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

#include "device.h"

Device::Device (ScreenObject &object)
{
    ourbot = &object;
}

Device::Device()
{
}

Device::~Device()
{
}

/**
	* Take in a value in the port (after an out instruktion from the CPU
	* And place it in the stack
	*/
void Device::addinport (unsigned char port, unsigned short value)
{
    for (int count=0; count<4; count++)
    {
        if (stacktaken[port][count] == false)
        {
            stacktaken[port][0] = true;
            portstack[port][0] = value;
            break;
        }
    }
}

void Device::execute()
{
}

int Device::readPort (unsigned char /*port*/)
{
    return 0;
}

int Device::absorbHit (int str, int /*ifint*/)
{
    return str;
}

void Device::erase (QPainter* /*buffer*/)
{
}

void Device::draw (QPainter* /*buffer*/)
{
}

/**
	* Sets relative angle of device (relative to bot)
	* ie. turret calls this function in the device he "turrets"
	*/
void Device::setrelang (int x)
{
    relang = x;
}

int Device::type()
{
    return 0;
}

int Device::specialValue()
{
    return 0;
}

struct DebugContents Device::debugContents()
{
    return DebugContents();
}

void Device::dospecial (int /*x*/, int /*y*/)
{
}

/**
	* Move the sack one step down for port "port"
	*/
void Device::moveportstack (int port)
{
    int count;
    for (count = 0; count < 3; count++)
    {
        portstack[port][count] = portstack[port][count+1];
        stacktaken[port][count] = stacktaken[port][count+1];
    }
    portstack[port][3] = 0;
    stacktaken[port][3] = false;
}
