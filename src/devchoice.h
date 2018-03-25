/***************************************************************************
                          devchoice.h  -  description
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

#ifndef DEVCHOICE_H
#define DEVCHOICE_H

#include <qwidget.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <QButtonGroup>
#include <qradiobutton.h>
#include <qvalidator.h>
#include <qstring.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "confstruct.h"
#include <QTextStream>
#include <qfile.h>
#include "commonsymbols.h"
#include <qdir.h>
#include "createbot.h"
#include "infobox.h"
#include <QGroupBox>

/**
	* This class is the one making up the choice
	* of devices for the bot.
	* It right now only contains a device combobox
	* 5 level buttons and an extra argument white edit box
	*
  * @author Andreas Agorander
  */

class DevChoice : public QGroupBox
{

    Q_OBJECT

public:

    DevChoice (CreateBot *cre, QWidget *parent=0,
               int num=0);
    ~DevChoice();
    unsigned short getitem();
    int getlevel();
    int getarg1();
    void setitem (int x);
    void setarg1 (const QString &value);

private:

    QComboBox *comb;
    QLineEdit *arg1;
    QButtonGroup *level;
    QRadioButton *levels[5];
    QIntValidator *valid;
    int dev;
    int chosenlevel;
    int mynum;
    QLabel *showcost;
    QPushButton *info;
    CreateBot *callb;
    InfoBox *showbox;

public slots:

    void levelchosen (int);
    void costchanged();
    void showinfo();

signals:

    void change();

};

#endif
