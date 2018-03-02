/***************************************************************************
                          armor.cpp  -  description
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

#include "armor.h"

//#include <qmessagebox.h>
	/**
		* Constructor ,inits device
		*/
armor::armor( screenobject &object, int arg1 )
{
	ourbot = &object;
	strength = arg1;
	orstrength = strength;
	ourbot->armorval += strength;
	ourlevel = arg1;
	intenabled = false;
	intenabled2 = false;
	heatintlevel = 1000;
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

	/**
		* Destructor, does nothing
		*/
armor::~armor( )
{
}

	/**
		* Checks if interrupt shall be issued, and if
		* any ports orders some actions
		*/
void armor::execute( )
{
	if( intenabled2 )
	{
		if( ourbot->armorval < armorintlevel )
			ourbot->addinterrupt( 3 );
	}
	if( ourbot->getheat( ) > heatintlevel )
	{
		ourbot->addinterrupt( 5 );
	}
	if( stacktaken[0][0] == true )
	{
		intenabled = portstack[0][0];
		moveportstack( 0 );
	}
	if( stacktaken[1][0] == true )
	{
		intenabled2 = portstack[1][0];
		moveportstack( 1 );
	}
	if( stacktaken[2][0] == true )
	{
		armorintlevel = portstack[2][0];
		moveportstack( 2 );
	}
	if( stacktaken[3][0] == true )
	{
		heatintlevel = portstack[3][0];
		moveportstack( 3 );
	}
}

	/**
		* Takes in the strength of the hit and
		*	returns the amount of hitpoints it couldn't absorb
		*/
int armor::absorbhit( int str,int ifint )
{
	if( strength >= str )
	{
		strength -= str;
		ourbot->armorval -= str;
		if( intenabled==true && ifint==1 )ourbot->addinterrupt( hitinterrupt );
		return 0;
	}
	else
	{
		str -= strength;
		ourbot->armorval -= strength;
		strength = 0;
		return str;
	}
}

	/**
		* Returns armor id-code
		*/
int armor::returntype( )
{
	return armortype;
}

	/**
		* Returns original armor value - current value
		*/
int armor::returnspecial( )
{
	return (orstrength-strength);
}

	/**
		* Returns value to CPU instruktion IN
		*/
int armor::getfromport( unsigned char port )
{
	switch ( port )
	{
		case 0 :
			return ourbot->getarmor( );
		break;
		case 1 :
			return ourbot->getheat( );
		break;
	}
	return 0;
}
	/**
		* Lowers the amount of RAM the bot with x (negative x means increase)
		* The repair unit uses this function in order to not issue an interrupt
		* every time he repairs.
		*/
void armor::dospecial( int x,int y )
{
		ourbot->armorval -= x;
		strength -= x;
}