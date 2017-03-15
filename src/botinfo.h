/***************************************************************************
                          botinfo.h  -  description
                             -------------------
    begin                : Tue Apr 4 2000
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

#ifndef BOTINFO_H
#define BOTINFO_H

#include <QLabel>
#include <QCheckBox>
#include <QString>
#include <QProgressBar>
#include "screenobject.h"

/** Holds the info about one bot
	* and shows it in the infowindow
  *@author Andreas Agorander
	*/
class BotInfo : public QWidget
{
    Q_OBJECT

public:
    BotInfo (const QString &botname, ScreenObject *rb, int armor, QWidget *parent);
    ~BotInfo();

private slots:
    void armorupdated (int x);
    void updatefuel (int x,int y);
    void statch (bool x);
    void newmessage (char *msg);

signals:
    void changeinset (bool x);

private:
    QLabel *botnam;
    QProgressBar *armorlevel;
    QProgressBar *heatlevel;
    QLabel *armormsg;
    QLabel *heatmsg;
    QLabel *msgmsg;
    QLabel *message;
    QCheckBox *ifscanner;
    QLabel *showgfx;
    ScreenObject *bot;
};

#endif
