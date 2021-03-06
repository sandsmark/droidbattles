/***************************************************************************
                          armor.cpp  -  description
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

#include "armor.h"

//#include <qmessagebox.h>
/**
	* Constructor ,inits device
	*/
Armor::Armor(ScreenObject &object, int arg1)
{
    ourbot = &object;
    strength = arg1;
    orstrength = strength;
    ourbot->armorval += strength;
    ourlevel = arg1;
    intenabled = false;
    intenabled2 = false;
    heatintlevel = 1000;
    int count;
    int count2;
    for (count = 0; count < 4; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

/**
	* Destructor, does nothing
	*/
Armor::~Armor()
{
}

/**
	* Checks if interrupt shall be issued, and if
	* any ports orders some actions
	*/
void Armor::execute()
{
    if (intenabled2) {
        if (ourbot->armorval < armorintlevel) {
            ourbot->addInterrupt(3);
        }
    }
    if (ourbot->heat() > heatintlevel) {
        ourbot->addInterrupt(5);
    }
    if (stacktaken[0][0]) {
        intenabled = portstack[0][0];
        moveportstack(0);
    }
    if (stacktaken[1][0]) {
        intenabled2 = portstack[1][0];
        moveportstack(1);
    }
    if (stacktaken[2][0]) {
        armorintlevel = portstack[2][0];
        moveportstack(2);
    }
    if (stacktaken[3][0]) {
        heatintlevel = portstack[3][0];
        moveportstack(3);
    }
}

/**
	* Takes in the strength of the hit and
	*	returns the amount of hitpoints it couldn't absorb
	*/
int Armor::absorbHit(int str, int ifint)
{
    if (strength >= str) {
        strength -= str;
        ourbot->armorval -= str;
        if (intenabled && ifint == 1) {
            ourbot->addInterrupt(hitinterrupt);
        }
        return 0;
    }
    str -= strength;
    ourbot->armorval -= strength;
    strength = 0;
    return str;
}

/**
	* Returns armor id-code
	*/
int Armor::type()
{
    return armortype;
}

/**
	* Returns original armor value - current value
	*/
int Armor::specialValue()
{
    return (orstrength - strength);
}

/**
	* Returns value to CPU instruktion IN
	*/
int Armor::readPort(uint8_t port)
{
    switch (port) {
    case 0:
        return ourbot->armor();
        break;
    case 1:
        return ourbot->heat();
        break;
    }
    return 0;
}
/**
	* Lowers the amount of RAM the bot with x (negative x means increase)
	* The repair unit uses this function in order to not issue an interrupt
	* every time he repairs.
	*/
void Armor::doSpecial(int x, int /*y*/)
{
    ourbot->armorval -= x;
    strength -= x;
}
