/***************************************************************************
                          quickconf.cpp  -  description
                             -------------------
    begin                : Mon Oct 30 2000
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

#include "quickconf.h"
//Added by qt3to4:
#include <Q3TextStream>
#include <QLabel>

	/**
		* Init GUI and load existing quick config
		*/
quickconf::quickconf( )
{

	int x;
	for( x=0;x<8;x++ )
	{
		botfiles[x] = "";
		shownames[x] = new QLabel( this );
		shownames[x]->setGeometry( 10,50+x*25,190,20 );
		shownames[x]->show( );
		team[x] = new QComboBox( this );
		team[x]->setGeometry( 215,50+x*25,40,20 );
		team[x]->insertItem( "1" );
		team[x]->insertItem( "2" );
		team[x]->insertItem( "3" );
		team[x]->insertItem( "4" );
  }
//	press[0] = new PixButton( "load",1,this );
//	press[0]->setGeometry( 0,0,80,40 );
//	press[1] = new PixButton( "remove",1,this );
//	press[1]->setGeometry( 85,0,80,40 );

	ifteams = new QCheckBox( "Teams",this );
	ifteams->setGeometry( 170,10,70,20 );

	QObject::connect( press[0],SIGNAL( clicked( ) ),this,
		SLOT( choosefile( ) ) );
	QObject::connect( press[1],SIGNAL( clicked( ) ),this,
		SLOT( dechoosefile( ) ) );

	readyb = new PixButton( "write file",1,this );
	readyb->setGeometry( 100,500,80,40 );
	cancelb = new PixButton( "Exit",1,this );
	cancelb->setGeometry( 200,500,80,40 );

	QObject::connect( readyb,SIGNAL( clicked( ) ),this,SLOT( ocl( ) ) );
	QObject::connect( cancelb,SIGNAL( clicked( ) ),this,SLOT( ccl( ) ) );

	tnumfights = new QLabel( "Number of fights:",this );
	tnumfights->setGeometry( 10,300,100,20 );
	wnumfights = new QLineEdit( this );
	wnumfights->setGeometry( 120,300,40,20 );
	numfix = new QIntValidator( this );
	wnumfights->setValidator( numfix );

	lengthfight = new QLabel( "Max length of fight ( 50 ~ 1sec ):",this );
	lengthfight->setGeometry( 10,320,200,20 );
	length = new QLineEdit( this );
	length->setGeometry( 200,320,60,20 );

	maxxinfo = new QLabel( "The xsize of the battlearea: ",this );
	maxxinfo->setGeometry( 10,350,200,20 );
	maxx = new QSpinBox( 8192,65535,512,this );
	maxx->setGeometry( 210,350,80,30 );
	maxx->setValue( 32768 );

	maxyinfo = new QLabel( "The ysize of the battlearea: ",this );
	maxyinfo->setGeometry( 10,380,200,20 );
	maxy = new QSpinBox( 8192,65535,512,this );
	maxy->setGeometry( 210,380,80,30 );
	maxy->setValue( 32768 );


	QString temp = QDir::homeDirPath( );
	temp += "/droidbattles/quick.conf";
	QFile f( temp );
	if( f.exists( ) && f.open( QIODevice::ReadOnly ) )
	{
		Q3TextStream s( &f );
		for( int x=0; x<8;x++ )
		{
			s >> botfiles[x];
			s >> temp;
			if( botfiles[x] == QString( "fff" ) )
				botfiles[x] = "";
			team[x]->setCurrentItem( temp.toInt( ) );
			shownames[x]->setText( botfiles[x] );
		}
		s >> temp;
		ifteams->setChecked( temp.toInt( ) );
		s >> temp;
		wnumfights->setText( temp );
		s >> temp;
		length->setText( temp );
		s >> temp;
		maxx->setValue( temp.toInt( ) );
		s >> temp;
		maxy->setValue( temp.toInt( ) );
		f.close( );
	}
}

quickconf::~quickconf( )
{
	int x;
	for( x=0;x<8;x++ )
  {
		delete shownames[x];
	}
}

	/**
		* Saves the current settings to file
		*/
void quickconf::ocl( )
{
	QString temp = QDir::homeDirPath( );
	temp += "/droidbattles/quick.conf";
	QFile f( temp );
	if( f.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream s( &f );
		for( int x=0; x<8;x++ )
		{
			if( botfiles[x] == QString( "" ) )
				s << "fff" << " " << team[x]->currentItem( ) << "\n";
			else
				s << botfiles[x] << " " << team[x]->currentItem( ) << "\n";
		}
		s << ifteams->isChecked( ) << "\n";
		s << getnumfights( ) << "\n";
		s << getlength( ) << "\n";
		s << getxsize( ) << " " << getysize( ) << "\n";
		f.close( );
	}
}

void quickconf::ccl( )
{
	delete this;
}
