/***************************************************************************
                          confedit.h  -  description
                             -------------------
    begin                : Tue Apr 18 2000
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

#ifndef CONFEDIT_H
#define CONFEDIT_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qscrollview.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <unistd.h>
#include "installdir.h"

/**edits and sets current config file
  *@author Andreas Agorander
  */

#define numdev 20

class confedit : public QWidget
{

	Q_OBJECT

	public:

		confedit( );
		~confedit( );

	private:

		// The "menu" buttons
		QPushButton *closebutton;
		QPushButton *helpbutton;
		QPushButton *openbutton;
		QPushButton *makecurrentbutton;
		QPushButton *savebutton;
		QPushButton *defaultbutton;
		
		// Area covering all - menu buttons
		QWidget *setarea;
		QScrollView *scroll;

		//Used for all numeric input
		QIntValidator *valid;

		//Global settings
		QLabel *maxdevl;
		QSpinBox *maxdevv;
		QLabel *maxcostl;
		QSpinBox *maxcostv;

		QLabel *maxraml;
		QComboBox *maxramv;
		QLabel *ramcostl;
		QComboBox *ramcostv;

		//Device specific settings
		QGroupBox *devicegroup[numdev];
		QCheckBox *devicesenabled[numdev];
		QLabel *costs[numdev];
		QComboBox *levelcosts[numdev];
		QLabel *values[numdev];
		QComboBox *levelvalues[numdev];

	private slots:

		void closec( );
		void helpc( );
		void openc( );
		void makecurrc( );
		void savec( );
		void defaultc( );
		void openfile( QString &tempname );

};

#endif
