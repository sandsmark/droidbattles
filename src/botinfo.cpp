/***************************************************************************
                          botinfo.cpp  -  description
                             -------------------
    begin                : Tue Apr 4 2000
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

#include "botinfo.h"

	/**
		* Constructor, create all GUI elements
		*/
botinfo::botinfo( const char *botname, screenobject *rb,int armor,
									QWidget *parent, const char *name) : QWidget( parent,name )
{
	QString tn = botname;
	bot = rb;
	if( !tn.isEmpty( ) )
	{
		int pos = tn.findRev( "/",tn.length( ) );
		QString temp = tn.right( tn.length( )-pos-1 );
		botnam = new QLabel( temp,this );
		botnam->setGeometry( 5,5,70,15 );

		armorlevel = new QProgressBar( armor,this );
		armorlevel->setGeometry( 95,5,100,25 );
		armorlevel->setProgress( armor );

		armormsg = new QLabel( "A:",this );
		armormsg->setGeometry( 75,5,15,15 );

		heatlevel = new QProgressBar( 850,this );
		heatlevel->setGeometry( 220,5,100,25 );
		heatlevel->setProgress( 0 );

		heatmsg = new QLabel( "H:",this );
		heatmsg->setGeometry( 200,5,15,15 );

	
		msgmsg = new QLabel( "F: ",this );
		msgmsg->setGeometry( 330,5,70,15 );

		message = new QLabel( "M: ",this );
		message->setGeometry( 400,5,100,15 );

		ifscanner = new QCheckBox( "Show device gfx",this );
		ifscanner->setGeometry( 5,35,120,15 );
		ifscanner->setChecked( true );
		QObject::connect( ifscanner, SIGNAL( toggled( bool ) ), this,
											SLOT(statch( bool )) );

		showgfx = new QWidget( this );
		showgfx->setGeometry( 500,0,32,32 );
		showgfx->setBackgroundPixmap( rb->getgfx( ) );
	}
	show( );
}

	/**
		* Destructor, does nothing
		*/
botinfo::~botinfo( )
{
}

	/**
		* Updates armor progressbar
		* Connected to armorchanged signal that the bot emits
		*/
void botinfo::armorupdated( int x )
{
	armorlevel->reset( );
	armorlevel->setProgress( x );
}

	/**
		* emits signal that makes the bots show/not show device gfx
		*/
void botinfo::statch( bool x )
{
	emit( changeinset( x ) );
}

	/**
		* Updates fuel value
		*/
void botinfo::updatefuel( int x,int y )
{
	QString temp;
	temp.setNum( x );
	QString t2 = "F: ";
	t2 += temp;
	msgmsg->setText( t2 );
	heatlevel->reset( );
	heatlevel->setProgress( y );
}

	/**
		* Shows new message
		*/
void botinfo::newmessage( char *msg )
{
	QString temp;
	temp = "M : ";
	temp += msg;
	message->setText( temp );
}