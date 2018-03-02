/***************************************************************************
                          beam.h  -  description
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

#ifndef BEAM_H
#define BEAM_H

#include "screenobject.h"
#include "textmodebattlearea.h"
/**
	* The "beam" screenobject, (lazerlike shot)
  *@author Andreas Agorander
  */

class beam : public screenobject
{

	public:
		beam( int X,int Y,int dir,int l,textmodeBattleArea &area, int owner, bool ui = true );
		~beam( );
		int execute( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer,int opt=0 );
		int objhit( int type, int strength );
		int returntype( );
		int getcollisionstrength( );
		int getcollisiontype( );
	private:
		int length;
		int lastpaintX;
		int lastpaintY;
		int effect;
		bool ispainted;
		textmodeBattleArea *ourarea;
		int uX;
		int uY;
};

#endif
