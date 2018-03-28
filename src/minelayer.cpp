/***************************************************************************
                          minelayer.cpp  -  description
                             -------------------
    begin                : Fri Aug 11 2000
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

#include "minelayer.h"
#include <QDebug>

MineLayer::MineLayer(ScreenObject &object, int ourlevel)
{
    qDebug() << "Mine layer has" << ourlevel << "mines";
    minesleft = ourlevel;
    ourbot = &object;
    int count, count2;
    for (count = 0; count < 4; count++) {
        for (count2 = 0; count2 < 4; count2++) {
            stacktaken[count][count2] = false;
            portstack[count][count2] = 0;
        }
    }
}

MineLayer::~MineLayer()
{
}

void MineLayer::execute()
{
    if (stacktaken[0][0]) {
        moveportstack(0);
        if (minesleft > 0) {
            ourbot->addScreenObject(ourbot->xPos(), ourbot->yPos(),
                                    ourbot->direction(), 3);
            minesleft--;
            qDebug() << minesleft;
        }
    }
}

/**
	* Returns mines left to in instruction
	*/
int MineLayer::readPort(unsigned char /*port*/)
{
    return minesleft;
}
