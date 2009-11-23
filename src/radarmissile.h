/***************************************************************************
                          radarmissile.h  -  description
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

#ifndef RADARMISSILE_H
#define RADARMISSILE_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include "ram.h"
#include "robcpu.h"
#include "steering.h"
#include "scanner.h"
#include "device.h"
#include <q3multilineedit.h>
#include "debugwindow.h"
/**
	* A programmable missile
  *@author Andreas Agorander
  */

class radarmissile : public screenobject
{

	public:

		radarmissile( int,int,int,int,int,int,textmodeBattleArea &,RAM *,int owner, bool ui=true );
		~radarmissile( );
		int execute( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer, int opt = 0 );
		int returntype( );
		int getcollisiontype( );
		int getcollisionstrength( );
		int changepos( double X,double Y );
		int objhit( int type,int strength );
		int getsize( );
		int getdevport( unsigned char port );
		void putdevport( unsigned char port,unsigned short value );
		int iodevtobatt( int bot,int dev,int choice,int arg1,int arg2 );
		int returnradar( );
    void createDbgWindow(int, Q3MultiLineEdit*, int*, int*);

	private:

		textmodeBattleArea *ourarea;
		int strength;
		RAM *ramdevice;
		device *devices[3];
    debugwindow* dbgWindow;
};

#endif
