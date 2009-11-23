/***************************************************************************
                          docbrowser.cpp  -  description
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

#include "docbrowser.h"
//Added by qt3to4:
#include <QCloseEvent>

Docbrowser::Docbrowser (QString src)
{
    setSource (src);
    resize (800,600);
    show();
}

Docbrowser::~Docbrowser()
{
}

void Docbrowser::closeEvent (QCloseEvent*)
{
    delete this;
}
