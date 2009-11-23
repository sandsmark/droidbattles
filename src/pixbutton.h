/***************************************************************************
                          pixbutton.h  -  description
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

#ifndef PIXBUTTON_H
#define PIXBUTTON_H

#include <qpushbutton.h>
#include <qpainter.h>
#include "pixmapholder.h"
#include <qnamespace.h>

/**
  *@author Andreas Agorander
	* This class is a reimplementation of QPushButton that adds the
	* capability to have a background pixmap AT tHE SAME TIME as a
	* text label...
  */

class PixButton : public QPushButton
{
public:
    PixButton (char *text,int pix,QWidget *parent,char *name=0);
    ~PixButton();
protected:
    void drawButtonLabel (QPainter *paint);
private:
    QString tex;
    int whichpix;
};

#endif
