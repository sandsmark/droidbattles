/***************************************************************************
                          installdir.cpp  -  description
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

#include "installdir.h"
//Added by qt3to4:
#include <Q3TextStream>

QString returninstalldir( )
{
	/**
		* Get the installation dir
		*/

	//Open config file
	QString temp = "/etc/droidbattles.conf";
	QString insdir;
	QFile f3( temp );
	//If no config file exists, take the default location
	if( !f3.exists( ) )
	{
		temp = "/usr/local/droidbattles";
		return temp;
	}	
	f3.open( QIODevice::ReadOnly );
  Q3TextStream s( &f3 );
	s >> temp;   //Read from file
	s >> insdir;
	f3.close( );
	return insdir;
}
