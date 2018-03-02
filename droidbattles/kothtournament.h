/***************************************************************************
                          kothtournament.h  -  description
                             -------------------
    begin                : Thu Nov 2 2000
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

#ifndef KOTHTOURNAMENT_H
#define KOTHTOURNAMENT_H

#include <qwidget.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qcheckbox.h>
#include <qtextstream.h>
#include "pixbutton.h"
#include "pixmapholder.h"
/**
	* The dialog for starting a KOTH tournament
	* Lays resident in memory during the hole tournament
	* as a keeper of the settings info, but isn't visible
	* then.
  *@author Andreas Agorander
  */

class kothtournament : public QWidget
{

	Q_OBJECT

	public:
		kothtournament( );
		~kothtournament( );
		int getnumofbots( );
		const char* getbotfile( int bot );
		void closeEvent( QCloseEvent *e );
		int getnumfights( );
		int getlength( );
		int getxsize( );
		int getysize( );
		bool getiffast( );
		int getseed( );

	private slots:

		void choosefile( );
		void dechoosefile( );
		void ocl( );
		void ccl( );
		void chooselist( );

	signals:

		void okclicked( );
		void cancelclicked( );

	private:

		int numofbots;
		QListBox *botfiles;
		QLabel *tnumfights;
		QLineEdit *wnumfights;
		QLabel *lengthfight;
		QLineEdit *length;
		QIntValidator *numfix;
		PixButton *press[2];
		PixButton *readyb;
		PixButton *cancelb;
		PixButton *loadlist;
		QLabel *maxxinfo;
		QLabel *maxyinfo;
		QSpinBox *maxx;
		QSpinBox *maxy;
		QLabel *seedinfo;
		QLineEdit *seed;
		QCheckBox *iffast;

};

#endif
