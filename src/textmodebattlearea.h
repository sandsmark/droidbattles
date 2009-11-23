/***************************************************************************
                          textmodebattlearea.h  -  description
                             -------------------
    begin                : Fri Nov 23 2001
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

#ifndef TEXTMODEBATTLEAREA_H
#define TEXTMODEBATTLEAREA_H


/**
  *@author Andreas Agorander
  */
#include "ram.h"
#include "commonsymbols.h"
#include <qdir.h>
#include <qstring.h>
#include <q3textstream.h>
#include <qfile.h>
#include "confstruct.h"
#include "screenobject.h"
#include <iostream>

class textmodeBattleArea
{
	public:
		textmodeBattleArea( );
		virtual ~textmodeBattleArea( );
		textmodeBattleArea( const char *name1,const char *name2,const char *name3,const char *name4,const char *name5,
								const char *name6,const char *name7,const char *name8,int numf,int ,int xs,
								int ys,bool ifteams,int *bteams, bool tourney,
								int mode = 0 );
		virtual void addscrobject(  int owner,int X,int Y,int dir,int type,int arg1=0,
												int arg2=0, void *arg3=0 );
		int devio( int bot,int dev,int choice,int arg1,int arg2 );
		virtual void startonebattle( int );
		int	getareainfo( int );
		virtual void explosions( int x,int y, int rad, int strength, int whichobject );
		int getstartx( int );
		int getstarty( int );

		int execround( );

	protected:

/*		list<debugwindow*> dbgwindows;
    QMultiLineEdit *_dbedit;
    int *_dbl;
    int *_dbm;

    int missilesLaunched;*/

		screenobject *objects[256];
//		QWidget *mydrw;
//		QScrollView *scrolling;
//		QWidget *infowindow;
//		QTimer *eventH;
//		QLabel *debug1;
//		QLabel *debug2;
//		QMessageBox *ermsg;

//		PixButton *playb;
//		PixButton *pauseb;
//		PixButton *singles;

//		debugwindow *dbgwindow;
//		QPixmap *dumm;

//		int updatescreen;
//		botinfo *binfo[8];
		QString names[8];
//		QPixmap *backpm;
		int numfights;
		int fightswon[8];
		int fightsfought;
		confstruct config;
		int roundsrun;
		int maxrounds;
		int xsize;
		int ysize;
		bool isteams;
		bool checkwin;
		int botteams[8];
		int alive[4];
		bool ifdelete;
		int radiosignals[4][8];
		bool radsigexist[4][8];
		bool hideresmsg;		
		bool iffast;
		int xstarts[8];
		int ystarts[8];
		bool debugenabled;
		int battlemode; //0 - normal, 1 - survival, 2 - Deathmatch
		int runmode; //0 - not running, 1 - running
		int maxpoints;
};
#include "robots.h"
#include "mine.h"
#include "radarmissile.h"
#include "missile.h"
#include "radarmissile.h"
#include "beam.h"
#include "rocket.h"
#include "chaff.h"
//#include "explosion.h"

#endif
