/***************************************************************************
                          explosion.cpp  -  description
                             -------------------
    begin                : Sun Jul 16 2000
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

#include "explosion.h"

	/**
		* Init position
		*/
explosion::explosion( int X, int Y, battlearea &area )
{
	ourarea = &area;
	maxx = ourarea->getareainfo( 0 );
	maxy = ourarea->getareainfo( 1 );
	Xpos = X>>6;
	Ypos = Y>>6;
	cycle = 1;
}

explosion::~explosion( )
{
}

	/**
		* Explosion timecounter, life 32 cycles
		*/
int explosion::execute( )
{
	if( ++cycle > 32 ) return destroyself;
	return 0;
}

	/**
		* Paints the circle on the screen, with size affected by
		* the counter
		*/
void explosion::showobject( QWidget *buffer,int opt=0 )
{
	QPainter p( buffer );
	p.setPen( QColor( 255,255,0 ) );
	p.drawEllipse( Xpos-(cycle/2),Ypos-(cycle/2),cycle,cycle );
	oldX = int( Xpos-(cycle/2) );
	oldY = int( Ypos-(cycle/2) );
}

	/**
		* Paints a black circle where the yellow was painted before
		*/
void explosion::eraseobject( QWidget *buffer )
{
	QPainter p( buffer );
	p.setPen( QColor( 0,0,0 ) );
	p.drawEllipse( oldX,oldY,(cycle),(cycle) );
}

	/**
		* Returns : object that's not collidable
		*/
int explosion::returntype( )
{
	return noncollobject;
}