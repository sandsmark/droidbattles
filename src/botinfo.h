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
#include <QPointer>

//#include "screenobject.h"
class Robots;
class ScreenObject;

class QGridLayout;

/** Holds the info about one bot
    * and shows it in the infowindow
  *@author Andreas Agorander
    */
class BotInfo : public QObject
{
    Q_OBJECT

public:
    ~BotInfo() override;
    static BotInfo *addBotInfo(QGridLayout *layout, int index, const QString &name, ScreenObject *screenObject);

    int score();

private slots:
    void armorupdated(int x);
    void updatefuel(int fuel, int heat);
    void statch(bool x);
    void newmessage(char *msg);

signals:
    void changeinset(bool x);

private:
    BotInfo(const QString &botname, ScreenObject *rb);

    QLabel botnam;
    QProgressBar armorlevel;
    QProgressBar heatlevel;
    QProgressBar m_fuelLevel;
    QLabel armormsg;
    QLabel heatmsg;
    QLabel m_fuelLabel;
    QLabel message;
    QCheckBox ifscanner;
    QLabel showgfx;
    QPointer<Robots> bot;
    int m_cost;
};

#endif
