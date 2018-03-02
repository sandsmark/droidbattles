/***************************************************************************
                          debugwindow.cpp  -  description
                             -------------------
    begin                : Fri Nov 3 2000
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

#include "debugwindow.h"

#include <qmessagebox.h>
	/**
		* Constructor, create GUI elements
		*/
debugwindow::debugwindow( QMultiLineEdit *Medit, int *dbl, int *dbm )
{
//	int x;

	registercontents[0] = new QLabel( "ax :",this );
	registercontents[1] = new QLabel( "bx :",this );
	registercontents[2] = new QLabel( "cx :",this );
	registercontents[3] = new QLabel( "dx :",this );
	registercontents[4] = new QLabel( "bp :",this );
	registercontents[5] = new QLabel( "sp :",this );
	registercontents[6] = new QLabel( "si :",this );
	registercontents[7] = new QLabel( "di :",this );
	registercontents[8] = new QLabel( "ip :",this );

	flagcontents[0] = new QLabel( "Equal :",this );
	flagcontents[1] = new QLabel( "Above :",this );
	flagcontents[2] = new QLabel( "Below :",this );
	flagcontents[3] = new QLabel( "Interrupt Enable :",this );

	memcontents[0] = new QLabel( "Mem contents @ip :",this );
	memcontents[1] = new QLabel( "Mem contents @sp :",this );
	memcontents[2] = new QLabel( "Mem contents @si :",this );
	memcontents[3] = new QLabel( "Mem contents @di :",this );

	execlines = new QMultiLineEdit( this );

	dumpmemb = new QPushButton( "Dump mem-map", this );

	registercontents[0]->setGeometry( 0,0,80,20 );
	registercontents[1]->setGeometry( 100,0,80,20 );
	registercontents[2]->setGeometry( 200,0,80,20 );
	registercontents[3]->setGeometry( 0,30,80,20 );
	registercontents[4]->setGeometry( 100,30,80,20 );
	registercontents[5]->setGeometry( 200,30,80,20 );
	registercontents[6]->setGeometry( 0,60,80,20 );
	registercontents[7]->setGeometry( 100,60,80,20 );
	registercontents[8]->setGeometry( 200,60,80,20 );

	flagcontents[0]->setGeometry( 0,90,80,20 );
	flagcontents[1]->setGeometry( 100,90,80,20 );
	flagcontents[2]->setGeometry( 0,120,80,20 );
	flagcontents[3]->setGeometry( 100,120,110,20 );

	memcontents[0]->setGeometry( 0,150,280,20 );
	memcontents[1]->setGeometry( 0,180,280,20 );
	memcontents[2]->setGeometry( 0,210,280,20 );
	memcontents[3]->setGeometry( 0,240,280,20 );

	execlines->setGeometry( 5,260,285,100 );
	dumpmemb->setGeometry( 100,370,100,30 );

	maineditor = Medit;
	debuglines = &dbl[0];
	debugmem = &dbm[0];

	QObject::connect( dumpmemb,SIGNAL( clicked( ) ),this,SLOT( distsignal() ) );
	
}

debugwindow::~debugwindow( )
{
}

	/**
		* Updates the debug info
		*/
void debugwindow::updatedata( struct debugcontents contents )
{
	QString tmp;
	tmp = "ax :";
	addint( tmp,contents.ax );
	registercontents[0]->setText( tmp );
	tmp = "bx :";
	addint( tmp,contents.bx );
	registercontents[1]->setText( tmp );
	tmp = "cx :";
	addint( tmp,contents.cx );
	registercontents[2]->setText( tmp );
	tmp = "dx :";
	addint( tmp,contents.dx );
	registercontents[3]->setText( tmp );
	tmp = "bp :";
	addint( tmp,contents.bp );
	registercontents[4]->setText( tmp );
	tmp = "sp :";
	addint( tmp,contents.sp );
	registercontents[5]->setText( tmp );
	tmp = "si :";
	addint( tmp,contents.si );
	registercontents[6]->setText( tmp );
	tmp = "di :";
	addint( tmp,contents.di );
	registercontents[7]->setText( tmp );
	tmp = "ip :";
	addint( tmp,contents.ip );
	registercontents[8]->setText( tmp );

	tmp = "Mem contents @ip :";
	int x;
	for( x=0;x<4;x++ )
	{
		tmp += " ";
		addint( tmp,contents.ipcontents[x] );
	}
	tmp += " ip:";
	for( x=4;x<9;x++ )
	{
		tmp += " ";
		addint( tmp,contents.ipcontents[x] );
	}
	memcontents[0]->setText( tmp );

	tmp = "Mem contents @sp :";

	for( x=0;x<4;x++ )
	{
		tmp += " ";
		addint( tmp,contents.spcontents[x] );
	}
	tmp += " sp:";
	for( x=4;x<9;x++ )
	{
		tmp += " ";
		addint( tmp,contents.spcontents[x] );
	}
	memcontents[1]->setText( tmp );

	tmp = "Mem contents @si :";

	for( x=0;x<4;x++ )
	{
		tmp += " ";
		addint( tmp,contents.sicontents[x] );
	}
	tmp += " si:";
	for( x=4;x<9;x++ )
	{
		tmp += " ";
		addint( tmp,contents.sicontents[x] );
	}
	memcontents[2]->setText( tmp );

	tmp = "Mem contents @di :";

	for( x=0;x<4;x++ )
	{
		tmp += " ";
		addint( tmp,contents.dicontents[x] );
	}
	tmp += " di:";
	for( x=4;x<9;x++ )
	{
		tmp += " ";
		addint( tmp,contents.dicontents[x] );
	}
	memcontents[3]->setText( tmp );


	tmp = "Equal Flag: ";
	if( (contents.flags & 0x8000) == 0x8000 )
		tmp += "1";
	else
		tmp += "0";
	flagcontents[0]->setText( tmp );

	tmp = "Above Flag: ";
	if( (contents.flags & 0x2000) == 0x2000 )
		tmp += "1";
	else
		tmp += "0";
	flagcontents[1]->setText( tmp );

	tmp = "Below Flag: ";
	if( (contents.flags & 0x4000) == 0x4000 )
		tmp += "1";
	else
		tmp += "0";
	flagcontents[2]->setText( tmp );

	tmp = "Interrupt Enable: ";
	if( (contents.flags & 0x0400) == 0x0400 )
		tmp += "1";
	else
		tmp += "0";
	flagcontents[3]->setText( tmp );

	execlines->clear( );
	for( x=0;x<30;x++ )
	{
		int z = contents.execmem[x];
		if( z >= 0 )
		{
			int x2;
			for( x2=0;x2<4095;x2++ )
			{
				if( debugmem[x2] == z )
				{
					execlines->insertLine( maineditor->textLine( debuglines[x2] ),-1 );
					break;
				}
			}
		}
	}

	repaint( );
}

	/**
		* Adds an integer to a string
		*/
void debugwindow::addint( QString &str,unsigned short integ )
{
	bool ready=false;
	QString temp;
	QString t2;
	while( !ready )
	{
		t2 = ((char)(integ%10+'0'));
		temp = t2 + temp;
		integ /= 10;
		if( !integ )ready=true;
	}
	str += temp;
}

void debugwindow::distsignal( )
{
	emit( dumpmem( ) );
}