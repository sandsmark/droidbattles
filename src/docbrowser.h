/***************************************************************************
                          docbrowser.h  -  description
                             -------------------
    begin                : Sat Jan 6 2001
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

#ifndef DOCBROWSER_H
#define DOCBROWSER_H

#include <q3textbrowser.h>
#include <qstring.h>
//Added by qt3to4:
#include <QCloseEvent>
#include "installdir.h"

/**
  *@author Andreas Agorander
  */

class Docbrowser : public Q3TextBrowser
{

	public:
		Docbrowser( QString src );
		~Docbrowser( );
		void closeEvent( QCloseEvent *e );
};

#endif
