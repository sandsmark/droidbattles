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
#include "battleconfig.h"
//Added by qt3to4:
#include <QCloseEvent>
/**
	* Dialog to start a league tournament
  *@author Andreas Agorander
  */

class PixButton;

class StartTournament : public QDialog
{

    Q_OBJECT

public:
    StartTournament(const QString &type);
    ~StartTournament() override;
    int getnumofbots();
    QString getbotfile(int x);
    void closeEvent(QCloseEvent *e) override;
    int getnumfights();
    int getlength();
    int getxsize();
    int getysize();
    bool getiffast();
    uint getseed();
    void setseed(uint s);

    BattleConfig getBattleConfig();

private slots:
    void choosefile();
    void dechoosefile();
    void ocl();
    void ccl();

signals:
    void okclicked();
    void cancelclicked();

protected:
    int numofbots;
    QListWidget *botfiles;
    QLabel *tnumfights;
    QSpinBox *wnumfights;
    QLabel *lengthfight;
    QSpinBox *length;
    PixButton *press[2];
    PixButton *readyb;
    PixButton *cancelb;
    QLabel *maxxinfo;
    QLabel *maxyinfo;
    QSpinBox *maxx;
    QSpinBox *maxy;
    QLabel *seedinfo;
    QLineEdit *seed;
    QCheckBox *iffast;

private:
    void save();
    void load();
    QString m_type;

    std::shared_ptr<std::mt19937> m_randomDevice;
};

#endif
