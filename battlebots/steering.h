/***************************************************************************
                          steering.h  -  description
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

#ifndef STEERING_H
#define STEERING_H

#include "device.h"
#include "screenobject.h"

/**
	* Device that adjusts the heading of the bot
  *@author Andreas Agorander
  */

class steering : public device
{

	public:

		steering( screenobject &object,int );
		~steering( );
		int getfromport( unsigned char port );
		void execute( );

	private:

		int aimatdir;

};

#endif
