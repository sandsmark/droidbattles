/***************************************************************************
                          missile.cpp  -  description
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

#include "missile.h"

	/**
		* Init position, graphics and such
		*/
missile::missile( int X,int Y,int dir,int owner,int mnum, textmodeBattleArea &area, bool ui )
{
	useUI = ui;
	myowner = owner;
	ourarea = &area;
	mynum = mnum;
	strength = 20;
	direction = dir;
	speed = 256;
	noncollid = owner;
	Xpos = X;
	Ypos = Y;
	double dira = getdir( ) * pi / 512;
	changepos( cos( dira ) * 1500,sin( dira ) * 1500 );
	size = 1<<6;
	if( useUI )
	{
		erasegfx = new QPixmap;
		erasegfx->resize( 8,8 );
		erasegfx->fill( black );
		graphics = Pixmapholder::getpmp( 7 );
	}
}

missile::~missile( )
{
//	delete graphics;
	if( useUI )delete erasegfx;
}

	/**
		* Move the shot one step
		*/
int missile::execute( )
{
	double dir = getdir( ) * pi / 512;
	return changepos( cos( dir ) * getspeed( ),sin( dir ) * getspeed( ) );
}

	/**
		* Paint the shot black
		*/
void missile::eraseobject( QWidget *buffer )
{
	bitBlt( buffer,( oldX>>6 )-4,( oldY>>6 )-4,erasegfx );
}

	/**
		* Paint the shot on the screen
		*/
void missile::showobject( QWidget *buffer,int opt )
{
	if( opt == 0 )
		bitBlt( buffer,( getXpos( )>>6 )-4,( getYpos( )>>6 )-4,graphics );
	else
		bitBlt( buffer,( getXpos( )>>6 )-4,( getYpos( )>>6 )-4,erasegfx );
	oldX = int( Xpos );
	oldY = int( Ypos );
}

int missile::returntype( )
{
	return 2;
}

int missile::getcollisiontype( )
{
	return 2;
}

int missile::getcollisionstrength( )
{
	return 15;
}

int missile::objhit( int type,int strength )
{
	return objhitdestroyed;
}

	/**
		* If the shot gets outside the battlefield
		* it deletes itself
		*/
int missile::changepos( double X,double Y )
{
	oldX = int( Xpos );
	oldY = int( Ypos );
	Xpos += X;
	Ypos += Y;
	if( Xpos < 0 ) return destroyself;
	if( Xpos > ourarea->getareainfo( 0 ) ) return destroyself;
	if( Ypos < 0 ) return destroyself;
	if( Ypos > ourarea->getareainfo( 1 ) ) return destroyself;
	return 0;
}

int missile::getsize( )
{
	return 2;
}

int missile::returnradar( )
{
	return 1;
}
