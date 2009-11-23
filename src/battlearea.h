/***************************************************************************
                          battlearea.h  -  description
                             -------------------
    begin                : Sun Apr 2 2000
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

#ifndef BATTLEAREA_H
#define BATTLEAREA_H

#include <qwidget.h>
#include <qtimer.h>
#include <qlabel.h>
#include <qmessagebox.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QCloseEvent>
//#include "screenobject.h"
//#include "commonsymbols.h"
#include "botinfo.h"
//#include "confstruct.h"
//#include <qfile.h>
//#include <qtextstream.h>
//#include <qstring.h>
//#include <qdir.h>
#include <q3scrollview.h>
#include "pixbutton.h"
//#include <commonsymbols.h>
//#include "ram.h"
#include "debugwindow.h"
#include <q3multilineedit.h>
#include <qpixmap.h>
#include "pixmapholder.h"

#include "textmodebattlearea.h"

#include <list>
#include <assert.h>

/**
	* The class that takes care of showing and computing the actual fight
  * @author Andreas Agorander
  */

class battlearea : public QWidget, public textmodeBattleArea
{

	Q_OBJECT

	public:

		battlearea( char *name1,char *name2,char *name3,char *name4,char *name5,
								char *name6,char *name7,char *name8,int numf,int ,int xs,
								int ys,bool ifteams,int *bteams, bool tourney,bool iffast,
								int mode = 0, int maxp=10,bool ifdebug=false,
								Q3MultiLineEdit *dbedit=NULL, int *dbl=0, int *dbm=0 );
		~battlearea( );
		void closeEvent( QCloseEvent *e );
		void addscrobject(  int owner,int X,int Y,int dir,int type,int arg1=0,
												int arg2=0, void *arg3=0 );
		//int devio( int bot,int dev,int choice,int arg1,int arg2 );
		void startonebattle( int );
		//int	getareainfo( int );
		void explosions( int x,int y, int rad, int strength, int whichobject );
		//int getstartx( int );
		//int getstarty( int );

	private slots:

		void execute( );
		void play( );
		void pause( );
		void singlestep( );
		void dmem( );

	signals:

		void battledone( int,int );

	protected:
		void resizeEvent ( QResizeEvent * );

	private:

		std::list<debugwindow*> dbgwindows;
    Q3MultiLineEdit *_dbedit;
    int *_dbl;
    int *_dbm;

    int missilesLaunched;

//		screenobject *objects[256];
		QWidget *mydrw;
		Q3ScrollView *scrolling;
		QWidget *infowindow;
		QTimer *eventH;
		QLabel *debug1;
		QLabel *debug2;
		QMessageBox *ermsg;

		PixButton *playb;
		PixButton *pauseb;
		PixButton *singles;

		debugwindow *dbgwindow;
		QPixmap *dumm;

		int updatescreen;
		botinfo *binfo[8];
/*		QString names[8];
		//QPixmap *backpm;
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
		int maxpoints;*/
		// the following flag is true in single step mode
		// and will be used by robCPU::execinstr()
};
		extern bool SingleStepMode;

//#include "robots.h"
//#include "mine.h"
//#include "radarmissile.h"
//#include "missile.h"
//#include "radarmissile.h"
//#include "beam.h"
//#include "rocket.h"
//#include "chaff.h"
#include "explosion.h"

#endif
