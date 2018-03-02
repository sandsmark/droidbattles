/***************************************************************************
                          instruktion.cpp  -  description
                             -------------------
    begin                : Sun Apr 2 2000
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

#include "instruktion.h"

//Contains info about one mnemonic/operand combination for the assembler

instruktion::instruktion( char mnem[],int arg1t,int arg2t,int bit,int arg1b,
													int arg2b,int op )
{
	mnemonic = new char[strlen( mnem )+1];
	for( int x=0;x<strlen( mnem )+1;x++ )
		mnemonic[x] = mnem[x];
	arg1type = arg1t;
	arg2type = arg2t;
	bits = bit;
	arg1bits = arg1b;
	arg2bits = arg2b;
	opcode = op;
}

instruktion::~instruktion( )
{
	delete mnemonic;
}

	/**
		* Compares the mnemonic it has stored
		* with the parameters
		*/
bool instruktion::checkmatch( QString &mnem, int arg1t, int arg2t, int bit )
{
	if( strcmp( mnem.data( ),mnemonic )==0 && arg1type == arg1t && arg2type ==
			arg2t && ((bit == bits || bits == 0 ) || ( bit == 0 && bits == 16 ) ) )
		return true;
	else
		return false;
}

	/**
		* returns the objects opcode
		*/
unsigned char instruktion::getopcode( )
{
	return opcode;
}

	/**
		* Returns the sizes of the operands
		*/

int instruktion::getarg1bits( )
{
	return arg1bits;
}
int instruktion::getarg2bits( )
{
	return arg2bits;
}
