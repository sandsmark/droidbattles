/***************************************************************************
                          rocket.h  -  description
                             -------------------
    begin                : Wed Nov 1 2000
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

#ifndef ROCKET_H
#define ROCKET_H

#include "screenobject.h"
#include <math.h>
#include "textmodebattlearea.h"

/**
	* AS-rocket object
  *@author Andreas Agorander
  */

class rocket : public screenobject
{

	public:

		rocket( );
		~rocket( );
		rocket( int X,int Y,int dir,int leng,int mnum, textmodeBattleArea &area,
						int owner, bool ui=true );
		int objhit( int type,int strength );
		int returntype( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer, int opt=0 );
		int execute( );
		int changepos( double X,double Y );
		int getcollisiontype( );
		int getcollisionstrength( );
		int getsize( );
		bool areaexplosionaffects( );
		int returnradar( );

	private:

		int length;
		int uX;
		int uY;
		int pointX[50];
		int pointY[50];
		int pointD[50];
		int countpoint;
		textmodeBattleArea *ourarea;
};

#endif
