/***************************************************************************
                          robcpu.h  -  description
                             -------------------
    begin                : Mon Apr 3 2000
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

#ifndef ROBCPU_H
#define ROBCPU_H

#include "cpu.h"
#include "screenobject.h"
#include <qfile.h>

/**CPU adapted for bot
  *@author Andreas Agorander
  */

class robCPU : public CPU
{
	public:
		robCPU( );
		robCPU( RAM &ramdev,screenobject &object,int arg1,int arg2,int arg3,
						int arg4,int arg5 );
		~robCPU( );
		void execute( );
		int returntype( );
		int returnspecial( );
		void sendmsg( char *msg );
		struct debugcontents returndbg( );
		void execinstr( );
};

#endif
