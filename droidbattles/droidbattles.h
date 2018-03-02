/***************************************************************************
                          droidbattles.h  -  description
                             -------------------
    begin                : Sat Apr  1 17:40:01 CEST 2000
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

#ifndef DROIDBATTLES_H
#define DROIDBATTLES_H
#include "matchresult.h"

// include files for QT
#include <qstring.h>
#include <qpopupmenu.h>
#include <qaccel.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include <qapp.h>
#include <qstatusbar.h>
#include <qwidget.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qiconset.h>
#include <qdatetime.h>
#include <qpixmapcache.h>

// application specific includes
//#include "resource.h"
#ifndef __USE_GNU
#define __USE_GNU
#endif
//#include <unistd.h>

class createbot;
class startsbatt;
class startsurvbatt;
class startdeathbatt;
class battlearea;
class confedit;
class starttournament;
class kothtournament;

class startcup;
class Docbrowser;
class PixButton;
/**
  * This Class is the base class for the application. It sets up the main
  * window and providing buttons for starting other parts of the program
  */
class DroidBattles : public QWidget
{
  Q_OBJECT

  public:
    DroidBattles( );
    ~DroidBattles( );

  private:

		void enabletourneys( );
		void disabletourneys( );
		void enablebattles( );
		void disablebattles( );

		/** The buttons that are in the main widget */
		PixButton *menubuttons[12];
//		QPixmap *menupm;
		QPixmap *bnpm;
		/** Pointers to the various types of objects the menu object can start */
		// Editor for creating the bots
		createbot *cre;
		// Base widget for battles
		battlearea *batt;
		// Widget for showing info about bots
    QWidget *infobox;
		// Widget for startup of battle (ie determine which bots should fight)
		startsbatt *ssb;
		// Message box showing some 'about' info about the application
		QMessageBox *aboutb;

		kothtournament *kotht;
		startcup *cuptournament;
		starttournament *stment;

		Docbrowser *browser;

		confedit *ccf;
    char *currentdir;
		/** Status variables */
		bool editrunning;
		bool battlerunning;

		// State variables for battle and tournament management
		int teams[8];
		int wingames[64];
		int winmatches[64];
		QString newlist[64];
		struct matchresult results[128];
		int nextround[64];
		int resultcounter;
		int nextroundcount;
		int gamecounter;
		int botsleft;
		int curmainbot;
		int cursecbot;
		int seed;

	private slots:

		//Menu Item functions
		void createb( );
		void about( );
		void showb( );
    void quit( );
		void editconf( );

 		void skirmish( );
		void startskirmish( );
		void stopskirmish( );

		void survival( );
		void startsurvival( );
		void stopsurvival( );

		void death( );
		void startdeath( );
		void stopdeath( );

		void tournament( );
		void starttourney( );
		void stoptourney( );
		void managetourney( int wins1, int wins2 );

		void koth( );
		void startkoth( );
		void stopkoth( );
		void mankothtourney( int wins1, int wins2 );

		void cup( );
		void startcupt( );
		void stopcup( );
		void mancuptourney( int wins1,int wins2 );

		void showdoc( );
};

#endif

