/***************************************************************************
                          steering.cpp  -  description
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

#include "steering.h"

Steering::Steering(ScreenObject &object, int arg1)
{
    ourlevel = arg1;
    ourbot = &object;
    aimatdir = ourbot->direction();
    int count;
    int count2;
    for (count = 0; count < 4; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

Steering::~Steering()
{
}

/**
	* See if ports orders change in heading, the check which way is
	* faster to that heading (left / right )
	*/
void Steering::execute()
{
    if (stacktaken[0][0]) {
        aimatdir += portstack[0][0];
        if (aimatdir > 1024) {
            aimatdir %= 1024;
        }
        if (aimatdir < 0) {
            aimatdir += 1024;
        }
        moveportstack(0);
    }

    if (stacktaken[1][0]) {
        aimatdir = portstack[1][0];
        if (aimatdir > 1024) {
            aimatdir %= 1024;
        }
        if (aimatdir < 0) {
            aimatdir += 1024;
        }
        moveportstack(1);
    }

    if (stacktaken[2][0]) {
        aimatdir = ourbot->direction() + portstack[2][0];
        if (aimatdir > 1024) {
            aimatdir %= 1024;
        }
        if (aimatdir < 0) {
            aimatdir += 1024;
        }
        moveportstack(2);
    }

    int diff1, diff2;

    if (aimatdir != ourbot->direction()) {
        if (aimatdir < ourbot->direction()) {
            diff1 = ourbot->direction() - aimatdir;
            diff2 = 1024 - ourbot->direction() + aimatdir;
        } else {
            diff1 = ourbot->direction() + 1024 - aimatdir;
            diff2 = aimatdir - ourbot->direction();
        }

        if (diff1 < diff2) {
            if (diff1 < ourlevel) {
                ourbot->changeDirection(-diff1);
            } else {
                ourbot->changeDirection(-(ourlevel));
            }
        } else {
            if (diff2 < ourlevel) {
                ourbot->changeDirection(diff2);
            } else {
                ourbot->changeDirection((ourlevel));
            }
        }
    }
}

int Steering::readPort(uint8_t port)
{
    switch (port) {
    case 0:
        return ourbot->direction();
        break;
    case 1:
        return aimatdir;
        break;
    case 2:
        return ourbot->xPos();
        break;
    case 3:
        return ourbot->yPos();
        break;
    }

    return 0;
}
