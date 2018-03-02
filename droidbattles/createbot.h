/***************************************************************************
                          createbot.h  -  description
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

#ifndef CREATEBOT_H
#define CREATEBOT_H

#include <qwidget.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <myqmultilineedit.h>
#include <qscrollview.h>
#include <qstring.h>
#include <qcombobox.h>
#include "commonsymbols.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <qtextstream.h>
#include "instruktion.h"
#include <qregexp.h>
#include <unistd.h>
#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include "battlearea.h"
#include "quickconf.h"
#include "confstruct.h"
#include "pixmapholder.h"
#include "assert.h"
/**The base widget for the bot editor, contains an editor, an assembler
  *@author Andreas Agorander
  */

class devchoice;

class createbot : public QWidget
{
  Q_OBJECT

	public:

		createbot( );
		~createbot( );
		void closeEvent( QCloseEvent *e );
		void error( char *string, int line );
		void addint( QString & str,int integ );
		int devnum( int sort,int num );

	private slots:

		void assemble( );
		void newb( );
		void open( );
		void save( );
		void saveas( );
		void closec( );
		void cut( );
		void copy( );
		void paste( );
		void choosepic( );
		void startquick( );
		void confquick( );
		void stopconf( );
		void checkconf( );
		void devchanged( );
		void scrollview( int );
		void resizeEvent( QResizeEvent *e );
		void setEdittxtScrollValue( int i );
		void setShowlatencyScrollValue( int i );

	private:

		unsigned int RAMAMOUNT;
		QMessageBox *ermsg;
		unsigned char *mem;
		myQMultiLineEdit *edittxt;
		QScrollView *scroller;
		myQMultiLineEdit *showlatency;
		devchoice* devices[32];
		QPopupMenu *File;
		QPopupMenu *Edit;
		QPopupMenu *Assemble;
		QPopupMenu *Config;
		QPopupMenu *tests;
		QMenuBar *menb;
		QComboBox *amountRAM;
		QScrollView *scrvw;
		QWidget *boxarea;
		QString botname;
		char *dirname;
		QPushButton *gfxbutton;
		QPixmap gfx;
//		QPixmap *backpm;
		battlearea *batt;
		quickconf *qc;
		confstruct curconfig;
		bool changed;
		int instrlatency[256];
		int debuglines[4096];
		int debugmem[4096];
		int debugentry;
};
#include "devchoice.h"

#endif
