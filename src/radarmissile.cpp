/***************************************************************************
                          radarmissile.cpp  -  description
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

#include "radarmissile.h"
//Added by qt3to4:
#include <QPixmap>

	/**
		* Init positions, devices and load gfx
		*/
radarmissile::radarmissile( int X,int Y,int dir,int bootm,int stm,int mnum,
														textmodeBattleArea &area, RAM *mem,int owner, bool ui )
{
	useUI = ui;
	myowner = owner;
	ourarea = &area;
	mynum = mnum;
	strength = 175;
	direction = dir;
	speed = 150;
	Xpos = X;
	Ypos = Y;
	noncollid = 256;
	double dira = getdir( ) * pi / 512;
	changepos( cos( dira ) * 1500,sin( dira ) * 1500 );
	size = 1<<6;
	if( useUI )
	{
		erasegfx = new QPixmap;
		erasegfx->resize( 8,8 );
		erasegfx->fill( Qt::black );
		graphics = Pixmapholder::getpmp( 4 );
	}
	ramdevice = mem;	
	ramdevice->addowner( );
	devices[1] = new steering( *this,4 );
	devices[2] = new scanner( *this,20000,0 );
	devices[0] = new robCPU( *ramdevice,*this,2,bootm%256,bootm/256,stm%256,
														stm/256 );

	fuelval = 300;
  dbgWindow = NULL;
}

radarmissile::~radarmissile( )
{
//	delete graphics;
  if (dbgWindow) delete dbgWindow;
	if( useUI )delete erasegfx;
	delete devices[0];
	delete devices[1];
	delete devices[2];
	ramdevice->removeowner( );
	if( ramdevice->getowners( ) == 0 )delete ramdevice;
}

int radarmissile::objhit( int type,int strength )
{
	return objhitdestroyed;
}

int radarmissile::returntype( )
{
	return 2;
}

	/**
		* Paint object black
		*/
void radarmissile::eraseobject( QWidget *buffer )
{
	bitBlt( buffer,( oldX>>6 )-4,( oldY>>6 )-4,erasegfx );
	devices[2]->erasegfx( buffer );
}

	/**
		* Paint object gfx
		*/
void radarmissile::showobject( QWidget *buffer, int opt )
{
	if( opt == 0 )
		bitBlt( buffer,( getXpos( )>>6 )-4,( getYpos( )>>6 )-4,graphics );
	else
		bitBlt( buffer,( getXpos( )>>6 )-4,( getYpos( )>>6 )-4,erasegfx );
	oldX = int( Xpos );
	oldY = int( Ypos );
	devices[2]->showgfx( buffer );
}

	/**
		* Execute devices, move and use fuel
		*/
int radarmissile::execute( )
{
	int x;
	for( x=0;x<3;x++ )             //Execute all devices
		devices[x]->execute( );
  if (dbgWindow)
		dbgWindow->updatedata(devices[0]->returndbg());
	double dir = getdir( ) * pi / 512;
	if( --fuelval <= 0 )return -1;
	return changepos( cos( dir ) * speed,sin( dir ) * speed ); //Update position
}

int radarmissile::changepos( double X,double Y )
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

int radarmissile::getcollisiontype( )
{
	return 2;
}

int radarmissile::getcollisionstrength( )
{
	return 175;
}

int radarmissile::getsize( )
{
	return 1;
}

	/**
		* Inbetween function if the device want to call the
		* batlearea
		*/
int radarmissile::iodevtobatt( int bot,int dev,int choice,int arg1,int arg2 )
{
	return ourarea->devio( bot,dev,choice,arg1,arg2 );
}

	/**
		* Get value from device port
		*/
int radarmissile::getdevport( unsigned char port )
{
	int tempport = port%4;
	int tempdevice = int( port/4 );
	int temp;
	if( tempdevice < 3 )temp = devices[tempdevice]->getfromport( tempport );
	//setdebug1( temp );
	return temp;
}

	/**
		* Put value in device port
		*/
void radarmissile::putdevport( unsigned char port, unsigned short value )
{
	int tempport = port%4;
	int tempdevice = int( port/4 );
	if( tempdevice < 3 )devices[tempdevice]->addinport( tempport,value );
}

int radarmissile::returnradar( )
{
	return 4;
}

void radarmissile::createDbgWindow(int id, Q3MultiLineEdit* e,int* l,int* m)
{
  if (dbgWindow) delete dbgWindow;
  dbgWindow = new debugwindow( e,&l[0],&m[0]);
  dbgWindow->resize(300,405);
  dbgWindow->show();
  QString title;
  title.sprintf("Missile #%d",id);
  dbgWindow->setCaption(title);  // set title
}

