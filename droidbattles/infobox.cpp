/***************************************************************************
                          infobox.cpp  -  description
                             -------------------
    begin                : Wed Feb 28 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#include "infobox.h"

infobox::infobox( QString msg, QWidget *parent, const char *name )
 : QWidget( parent,name )
{
	text = new QLabel( msg,this );
	text->setGeometry( 0,0,0,0 );
	text->resize( text->sizeHint( ) );
	resize( text->sizeHint( ) );
	show( );
}

infobox::~infobox( )
{
}

void infobox::closeEvent( QCloseEvent *e )
{
	delete this;
}