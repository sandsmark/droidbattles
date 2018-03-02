/***************************************************************************
                          turret.cpp  -  description
                             -------------------
    begin                : Mon Apr 17 2000
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

#include "turret.h"

turret::turret( screenobject &object, int arg1,int dev )
{
	ourlevel = arg1;
	ourbot = &object;
	ourdev = dev;
	offset = 0;
	wantedoffset = 0;
	int count;
	int count2;
	for( count=0;count<4;count++ )
	{
		for( count2=0;count2<4;count2++ )
		{
			stacktaken[count][count2]=false;
			portstack[count][count2]=0;
		}
	}
}

turret::~turret( )
{
}

int turret::getfromport( unsigned char port )
{
	switch( port )
	{
   	case 0 :
			return offset;
		break;
		case 1 :
			return wantedoffset;
		break;
	}
	return 0;
}

void turret::execute( )
{
	if( stacktaken[0][0] == true )
	{
		wantedoffset = portstack[0][0];
		if( wantedoffset >1024 )wantedoffset %= 1024;
		if( wantedoffset <0 )wantedoffset += 1024;
		moveportstack( 0 );
	}
	if( stacktaken[1][0] == true )
	{
		wantedoffset += portstack[1][0];
		if( wantedoffset >1023 )wantedoffset %= 1024;
		if( wantedoffset <0 )wantedoffset += 1024;
		moveportstack( 1 );
	}
	if( stacktaken[2][0] == true )
	{
		wantedoffset = offset + portstack[2][0];
		if( wantedoffset >1023 )wantedoffset %= 1024;
		if( wantedoffset <0 )wantedoffset += 1024;
		moveportstack( 2 );
	}

	///Turn the turret

  //Find shortest way
  int left,right;
	if( wantedoffset < offset )
	{
		left = offset - wantedoffset;
		right = wantedoffset + 1024 - offset;
	}
	else
	{
		left = offset + 1024 - wantedoffset;
		right = wantedoffset - offset;
	}

	if( right > left )
	{
		if( left < ourlevel )
			offset = wantedoffset;
		else
			offset -= ourlevel;
	}
	else
	{
		if( right < ourlevel )
			offset = wantedoffset;
		else
			offset += ourlevel;
	}

	if( offset >= 1024 )
		offset -= 1024;
	if( offset < 0 )
		offset += 1024;

	ourbot->iodevtodev( ourdev,1,offset );

}
