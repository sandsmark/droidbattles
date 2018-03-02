/***************************************************************************
                          radarmissilelauncher.cpp  -  description
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

#include "radarmissilelauncher.h"

radarmissilelauncher::radarmissilelauncher( screenobject &object, int level,
																					  RAM *memdevice, int offset )
{
	ourlevel = level;
	memd = memdevice;
	relang = offset*4;
	int count,count2;
	ourbot = &object;
	reloadtime=1;
	for( count=0;count<3;count++ )
	{
		for( count2=0;count2<4;count2++ )
		{
			stacktaken[count][count2]=false;
			portstack[count][count2]=0;
		}
	}
}

radarmissilelauncher::~radarmissilelauncher( )
{
}

	/**
		* Commit port orders
		*/
void radarmissilelauncher::execute( )
{
	if( reloadtime>0 )reloadtime--;
	//Set boot mem
	if( stacktaken[0][0] == true )
	{
		bootmem = portstack[0][0];
		moveportstack( 0 );
	}
	//Set stack mem
	if( stacktaken[1][0] == true )
	{
		stackmem = portstack[1][0];
		moveportstack( 1 );
	}
	//Fire a missile
	if( stacktaken[2][0] == true )
	{
		if( reloadtime <= 0 )
		{
			ourbot->addscrobject( ourbot->getXpos( ),ourbot->getYpos( ),
				ourbot->getdir( )+relang,4,bootmem,stackmem,memd );
			moveportstack( 2 );
			reloadtime = ourlevel;
		}
	}
}

	/**
		* return reloadtime
		*/
int radarmissilelauncher::getfromport( unsigned char port )
{
	switch( port )
	{
		case 0 :
			return reloadtime;
		break;
	}
	return 0;	
}
