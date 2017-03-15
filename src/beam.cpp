/***************************************************************************
                          beam.cpp  -  description
                             -------------------
    begin                : Tue Oct 31 2000
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

#include "beam.h"

/**
	* Constructor , initializing and positioning beam
	*/
Beam::Beam (int X,int Y,int dir,int l,TextmodeBattleArea &area, int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    noncollid = collenabled;
    length = l;
    if (length > maxbeamlength) length = maxbeamlength;
    if (length < minbeamlength) length = minbeamlength;
    direction = dir;
    Xpos = X;
    Ypos = Y;
    uX = X;
    uY = Y;
    double dira = getdir() * toradians;
    double tempX,tempY;
    tempX = cos (dira) * length;
    tempY = sin (dira) * length;
    maxx = ourarea->getareainfo (0);
    maxy = ourarea->getareainfo (1);
    changepos (tempX,tempY);
    effect = 5;
}

/**
	* Destructor, does nothing
	*/
Beam::~Beam()
{
}

/**
	* ticks time until the effect of the beam
	* and destroys self is time's up and no
	* collision isssued
	*/
int Beam::execute()
{
    if (effect==0) return destroyself;
    if (effect >0) effect--;
    return 0;
}

/**
	* When collision, destroy self
	*/
int Beam::objhit (int type,int strength)
{
    Q_UNUSED(type);
    Q_UNUSED(strength);
    return objhitdestroyed;
}

/**
	* Returns 2 if it's time for collision
	* -1 else
	*/
int Beam::returntype()
{
    if (effect <= 1)
        return 2;
    else
        return -1;
}

/**
	* Paint object
	*/
void Beam::showobject (QPixmap *buffer, int /*opt*/)
{
    QPainter p (buffer);
    p.setPen (QColor (0,0,255));
    p.drawLine (uX>>6, uY>>6, getXpos() >>6, getYpos() >>6);
    ispainted = true;
}

/**
	* Paint object black
	*/
void Beam::eraseobject (QPixmap *buffer)
{
    QPainter p (buffer);
    p.setPen (QColor (0,0,0));
    p.drawLine (uX>>6, uY>>6, getXpos() >>6, getYpos() >>6);
    ispainted = false;
}

/**
	* Return the beams damage
	*/
int Beam::getcollisionstrength()
{
    return beamdamage;
}

/**
	* Return type (for future use)
	*/
int Beam::getcollisiontype()
{
    return 2;
}
