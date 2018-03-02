/***************************************************************************
                          chaff.h  -  description
                             -------------------
    begin                : Fri Dec 1 2000
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

#ifndef CHAFF_H
#define CHAFF_H

#include "screenobject.h"
#include "battlearea.h"
#include "pixmapholder.h"

/**
	* Chaff screenobject, made to fool scanners
  *@author Andreas Agorander
  */

class chaff : public screenobject
{

	Q_OBJECT

	public:

		chaff( int X,int Y,int d,int spd, battlearea &area );
		~chaff( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer,int opt=0 );
		int returntype( );
		int execute( );
		int returnradar( );

	private:
		int timeleft;
		battlearea *ourarea;
};

#endif
