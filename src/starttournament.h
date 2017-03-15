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
#include <QListWidget>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <QFileDialog>
#include <qcheckbox.h>
//Added by qt3to4:
#include <QCloseEvent>
/**
	* Dialog to start a league tournament
  *@author Andreas Agorander
  */

class StartTournament : public QWidget
{

    Q_OBJECT

public:

    StartTournament();
    ~StartTournament();
    int getnumofbots();
    QString getbotfile(int bot);
    void closeEvent (QCloseEvent *e);
    int getnumfights();
    int getlength();
    int getxsize();
    int getysize();
    bool getiffast();
    int getseed();

private slots:

    void choosefile();
    void dechoosefile();
    virtual void ocl();
    void ccl();

signals:

    void okclicked();
    void cancelclicked();

private:

    int numofbots;
    QListWidget *botfiles;
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
};

#endif
