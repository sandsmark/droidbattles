/***************************************************************************
                          robots.h  -  description
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

#ifndef ROBOTS_H
#define ROBOTS_H

#include "screenobject.h"
#include <qdatastream.h>
#include <q3textstream.h>
#include <qstring.h>
#include <qwidget.h>
#include "textmodebattlearea.h"
#include "ram.h"
#include "device.h"
#include <math.h>
#include <qfile.h>
#include "commonsymbols.h"
#include "robcpu.h"
#include "engine.h"
#include "steering.h"
#include "plasma.h"
#include "armor.h"
#include "scanner.h"
#include "fuel.h"
#include "turret.h"
#include <qbitmap.h>
#include <math.h>
#include <stdlib.h>
#include <qmessagebox.h>
#include "timedev.h"
#include "shield.h"
#include "repair.h"
#include <qstring.h>
#include "communication.h"
#include "minelayer.h"
#include "beamer.h"
#include "rocketlauncher.h"
#include "chafflauncher.h"

#ifndef __USE_GNU
#define __USE_GNU
#include <unistd.h>
#endif

#include "confstruct.h"
#include "installdir.h"
#include "radarmissilelauncher.h"
#include "scandetect.h"
#include "chiller.h"
#include "cloaker.h"

#include "debugcontents.h"
#include <list>
/**The bot that is programmed...
  *@author Andreas Agorander
  */

class robots : public screenobject
{

	Q_OBJECT

	public:

		robots( char *name,textmodeBattleArea &area,int mnum, confstruct,int tm,
						bool er=true, bool ui = true );
		~robots( );
		int execute( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer, int opt = 0 );
		void ifhit( );
		int getdevport( unsigned char port );
		void putdevport( unsigned char port,unsigned short value );
		int objhit( int type,int strength );
		void objscanned( int intensity, int dir );
		void addscrobject( int X,int Y,int dir,int type, int arg1=0,int arg2=0,
											 void *arg3=0 );
		int iodevtobatt( int bot,int dev,int choice,int arg1,int arg2 );
		int iodevtodev( int dev, int action, int value );
		int returntype( );
		int getcollisiontype( );
		int getcollisionstrength( );
		int getsize( );
		void receiveradio( int );
		const char* getdebug1( );
		const char* getdebug2( );
		void setdebug1( int );
		void setdebug2( int );
		void error( char *,char * );
		int getmem( );
		void addinterrupt( int );
		struct debugcontents returndbgcont( );
    int numCPUs();
    // the caller has to delete the returned pointer
		std::list<struct debugcontents> *returndbgcont2( );
		int returnradar( );
		void setradar( int x );
		void dumpRAM( );

	private:

		int RAMamount;
		RAM *ramdevice;
		int radarsignature;
		device *devicelist[32];
		char hitabsorborder[32];
		textmodeBattleArea *ourarea;
		bool gfxin;
		QMessageBox *rulebreak;
		int ourradiodev;
		bool showerror;
		int currentradar;
		int piccols;
		int picrows;
		int currentrow;
		int rowchangeval;
		int degreesperpic;
};

#endif
