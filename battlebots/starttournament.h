/***************************************************************************
                          starttournament.h  -  description
                             -------------------
    begin                : Sat Aug 5 2000
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

#ifndef STARTTOURNAMENT_H
#define STARTTOURNAMENT_H

#include <qwidget.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qcheckbox.h>
/**
	* Dialog to start a league tournament
  *@author Andreas Agorander
  */

class starttournament : public QWidget
{

Q_OBJECT

	public:

		starttournament( );
		~starttournament( );
		int getnumofbots( );
		const char* getbotfile( int bot );
		void closeEvent( QCloseEvent *e );
		int getnumfights( );
		int getlength( );
		int getxsize( );
		int getysize( );
		bool getiffast( );
		int getseed( );
//		bool getifteams( );
//		int getbotteam( int bot );

	private slots:

		void choosefile( );
		void dechoosefile( );
		virtual void ocl( );
		void ccl( );

	signals:

		void okclicked( );
		void cancelclicked( );

	private:

		int numofbots;
//		QString botfiles[8];
//		QLabel *shownames[8];
//		QComboBox *team[8];
		QListBox *botfiles;
		QLabel *tnumfights;
		QLineEdit *wnumfights;
		QLabel *lengthfight;
		QLineEdit *length;
		QIntValidator *numfix;
		QPushButton *press[2];
		QPushButton *readyb;
		QPushButton *cancelb;
		QLabel *maxxinfo;
		QLabel *maxyinfo;
		QSpinBox *maxx;
		QSpinBox *maxy;
		QLabel *seedinfo;
		QLineEdit *seed;
		QCheckBox *iffast;
//		QCheckBox *ifteams;
};

#endif
