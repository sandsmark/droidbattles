/***************************************************************************
                          myqmultilineedit.h  -  description
                             -------------------
    begin                : Sun Jun 3 2001
    copyright            : (C) 2001 by Peter Schmidt
    email                : peter.z.schmidt@compaq.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MYQMULTILINEEDIT_H
#define MYQMULTILINEEDIT_H

#include <qmultilineedit.h>

/**
  *@author Peter Schmidt
  */

//TODO : add syntax highlighting
class myQMultiLineEdit : public QMultiLineEdit
{
	public:
		myQMultiLineEdit( QWidget * parent=0 ) : QMultiLineEdit( parent ) {}
		QScrollBar *myVerticalScrollBar () const { return verticalScrollBar( ); }
};

#endif
