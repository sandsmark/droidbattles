/***************************************************************************
                          pixbutton.cpp  -  description
                             -------------------
    begin                : Thu Mar 1 2001
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

#include "pixbutton.h"

PixButton::PixButton (QString text,int pix,QWidget *parent,char *name)
        : QPushButton (parent,name)
{
    whichpix = pix;
    tex = text;
}

PixButton::~PixButton()
{
}

void PixButton::drawButtonLabel (QPainter *paint)
{
    paint->drawPixmap (2,2,Pixmapholder::getpm (whichpix),
                       0,0,width()-5,height()-5);
    paint->drawText (2, 2, width()-5, height()-5, Qt::AlignCenter, tex, -1);
}
