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

#include <installdir.h>

QString returninstalldir( )
{
	/**
		* Get the installation dir
		*/
	QString temp = "/etc/battlebots.conf";
	QString insdir;
	QFile f3( temp );
	if( !f3.exists( ) )
	{
		temp = "/usr/local/battlebots";
		return temp;
	}	
	f3.open( IO_ReadOnly );
  QTextStream s( &f3 );
	s >> temp;
	s >> insdir;
	f3.close( );
	return insdir;
}