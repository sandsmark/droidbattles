/***************************************************************************
                          infobox.h  -  description
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

#ifndef INFOBOX_H
#define INFOBOX_H

#include <qwidget.h>
#include <qlabel.h>

/**
  *@author Andreas Agorander
  */

class infobox : public QWidget
{
	public:
		infobox( QString msg, QWidget *parent=0, const char *name=0 );
		~infobox( );
		void closeEvent( QCloseEvent * e );
	private:
		QLabel *text;
};

#endif
