/***************************************************************************
                          missile.h  -  description
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

#ifndef MISSILE_H
#define MISSILE_H

#include "screenobject.h"
#include "textmodebattlearea.h"
#include <qwidget.h>
#include "commonsymbols.h"
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <unistd.h>
#include "installdir.h"
#include "pixmapholder.h"

/**
	* the shots from the plasmagun
  *@author Andreas Agorander
  */

class missile : public screenobject
{

	public:

		missile( int X,int Y,int dir,int owner,int mynum,textmodeBattleArea &area, bool ui = true );
		~missile( );
		int execute( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer, int opt = 0 );
		int returntype( );
		int getcollisiontype( );
		int getcollisionstrength( );
		int changepos( double X,double Y );
		int objhit( int type,int strength );
		int getsize( );
		int returnradar( );

	private:

		int strength;
		textmodeBattleArea *ourarea;

};

#endif
