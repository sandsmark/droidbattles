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
#include <QListWidget>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <QFileDialog>
#include <qcheckbox.h>
#include <QTextStream>
//Added by qt3to4:
#include <QCloseEvent>
#include "starttournament.h"

/**
	* The dialog for starting a KOTH tournament
	* Lays resident in memory during the hole tournament
	* as a keeper of the settings info, but isn't visible
	* then.
  *@author Andreas Agorander
  */

class PixButton;

class KothTournament : public StartTournament
{
    Q_OBJECT

public:
    KothTournament();

private slots:
    void chooselist();

private:
    PixButton *loadlist;
};

#endif
