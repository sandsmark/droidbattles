/***************************************************************************
                          textmodefilemanip.h  -  description
                             -------------------
    begin                : Thu Nov 22 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@bluefire.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TEXTMODEFILEMANIP_H
#define TEXTMODEFILEMANIP_H

#include "instruktion.h"
#include "commonsymbols.h"
#include "confstruct.h"
#include <qdir.h>
#include <q3textstream.h>
#include <qdatastream.h>
#include <iostream>
#include <qfile.h>
#include <qregexp.h>
#include <string.h>
/**
  *@author Andreas Agorander
  */

class textmodeFileManip
{
	public:
		textmodeFileManip( );
		~textmodeFileManip( );
		static void assemble( char *filename );
		static void checkConfig( char *filename );
		static void loadConfig( char *filename );
};

#endif
