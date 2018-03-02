/***************************************************************************
                          pixmapholder.cpp  -  description
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

#include "pixmapholder.h"

static QPixmap *pm[20];

Pixmapholder::Pixmapholder( )
{
}

Pixmapholder::~Pixmapholder( )
{
}

void Pixmapholder::addpm( QString &name,int num )
{
	pm[num] = new QPixmap( name );
}

QPixmap & Pixmapholder::getpm( int num )
{
	return *pm[num];
}

QPixmap * Pixmapholder::getpmp( int num )
{
	return pm[num];
}
