/***************************************************************************
                          cpu.cpp  -  description
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

#include "cpu.h"

CPU::CPU()
{
}

CPU::CPU(Ram &ramdev, ScreenObject & /*object*/)
{
    mem = &ramdev;
}

CPU::~CPU()
{
}

void CPU::callobout(unsigned char one, unsigned short two)
{
    ourbot->writeDevicePort(one, two);
}

int CPU::callobin(unsigned char one)
{
    return ourbot->readDevicePort(one);
}

void CPU::sendmsg(char * /*msg*/)
{
}

/**
	* This function executes instruktions until cyclesleft <= 0
	*/
void CPU::execinstr()
{
}

int CPU::writefile(int start, int length, int adress)
{
    char buffer[4096];
    int maxbytes = (mem->returnsize() % 1024) * 64;
    if (start + length > maxbytes)
        return -1;
    for (int x = 0; x < length; x++)
        buffer[x] = mem->getibyte(adress + x);
    QFile f(ourbot->myfile);
    if (!f.open(QIODevice::WriteOnly))
        return -1;
    f.seek(start);
    int ret = f.write(&buffer[0], length);
    f.close();
    return ret;
}

int CPU::readfile(int start, int length, int adress)
{
    char buffer[4096];
    int maxbytes = (mem->returnsize() % 1024) * 64;
    if (start + length > maxbytes)
        return -1;
    QFile f(ourbot->myfile);
    if (!f.open(QIODevice::ReadOnly))
        return -1;
    f.seek(start);
    int ret = f.read(buffer, length);
    for (int x = 0; x < length; x++)
        mem->setibyte(adress + x, buffer[x]);
    f.close();
    return ret;
}

int CPU::readPort(unsigned char port)
{
    switch (port) {
    case 0:
        return ourbot->writetoBattleArea(0, 0, 10, 0, 0); //Xsize of battlearea
        break;
    case 1:
        return ourbot->writetoBattleArea(0, 0, 11, 0, 0); //Ysize of battlearea
        break;
    case 2:
        return ourbot->writetoBattleArea(0, 0, 12, 0, 0); //maxlength of battle
        break;
    case 3:
        return ourbot->team();
        break;
    }
    return 0;
}
