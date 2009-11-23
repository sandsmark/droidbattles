/***************************************************************************
                          startsbatt.h  -  description
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

#ifndef STARTSBATT_H
#define STARTSBATT_H

#include <qwidget.h>
#include <qlabel.h>
#include <qstring.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QCloseEvent>
#include "commonsymbols.h"
#include <qlineedit.h>
#include <q3filedialog.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <q3textstream.h>
#include "pixmapholder.h"
#include "pixbutton.h"

/**A simple dialog for choosing which bots should fight
  *@author Andreas Agorander
  */

class startsbatt : public QWidget
{

	Q_OBJECT

	public:

		startsbatt();
		~startsbatt();
		int getnumofbots( );
		char* getbotfile( int bot );
		void closeEvent( QCloseEvent *e );
		int getnumfights( );
		int getlength( );
		int getxsize( );
		int getysize( );
		bool getifteams( );
		int getbotteam( int bot );

	private slots:

		void choosefile( );
		void dechoosefile( );
		virtual void ocl( );
		virtual void ccl( );

	signals:

		virtual void okclicked( );
		void cancelclicked( );

	protected:

		virtual void loadfilesettings( );
		virtual void resizeEvent( QResizeEvent *e );
		int numofbots;
		QString botfiles[8];
		QLabel *shownames[8];
		QComboBox *team[8];
		QLabel *tnumfights;
		QLineEdit *wnumfights;
		QLabel *lengthfight;
		QLineEdit *length;
		QIntValidator *numfix;
		PixButton *press[2];
		PixButton *readyb;
		PixButton *cancelb;
		QLabel *maxxinfo;
		QLabel *maxyinfo;
		QSpinBox *maxx;
		QSpinBox *maxy;
		QCheckBox *ifteams;
};

#endif
