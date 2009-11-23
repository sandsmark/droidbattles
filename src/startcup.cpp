/***************************************************************************
                          startcup.cpp  -  description
                             -------------------
    begin                : Mon Jan 1 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#include "startcup.h"

startcup::startcup()
{
}

startcup::~startcup()
{
}

void startcup::ocl()
{
    int x = getnumofbots();
    if (x==4 || x==8 || x==16 || x==32 || x==64)
        emit okclicked();
    else
    {
        QMessageBox::information (this,"Battlebots","Number of bots must be 4,8,"
                                  "16,32 or 64");
    }
}