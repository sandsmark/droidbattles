/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Apr  1 17:40:01 CEST 2000
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

#ifndef MAIN_CPP
#define MAIN_CPP

#include <qapplication.h>
#include <qfont.h>
#include <qplatinumstyle.h>
#include "battlebots.h"

int main( int argc, char *argv[] )
{
  QApplication a( argc, argv );

	//If you want another look change QPlatinumStyle to
	//one of: QCDEStyle, QWindowsStyle, QMotifStyle
  a.setStyle( new QPlatinumStyle );
  a.setFont( QFont( "helvetica", 12 ) );

  BattleBots *battlebots=new BattleBots( );
  a.setMainWidget( battlebots );

  battlebots->show( );

  return a.exec( );
}

#endif