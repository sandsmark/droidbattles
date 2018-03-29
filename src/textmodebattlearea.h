/***************************************************************************
                          textmodebattlearea.h  -  description
                             -------------------
    begin                : Fri Nov 23 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@bluefire.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TEXTMODEBATTLEAREA_H
#define TEXTMODEBATTLEAREA_H

/**
  *@author Andreas Agorander
  */
#include "ram.h"
#include "commonsymbols.h"
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QPointer>
#include <array>
#include "confstruct.h"
#include "screenobject.h"
#include "battleconfig.h"

class TextmodeBattleArea
{
public:
    TextmodeBattleArea();
    virtual ~TextmodeBattleArea();
    TextmodeBattleArea(const BattleConfig &battleConfig);
    virtual void addscrobject(int owner, int X, int Y, int dir, int type, int arg1 = 0,
                              int arg2 = 0, void *arg3 = 0);
    int devio(int bot, int dev, int choice, int arg1, int arg2);
    virtual void startonebattle(int);
    int getareainfo(int);
    virtual void explosions(int x, int y, int rad, int strength, int whichobject);
    int getstartx(int);
    int getstarty(int);

    int execround();

protected:
    QPointer<ScreenObject> objects[256];
    std::array<QString, 8> names;
    int numfights;
    int fightswon[8];
    std::array<uint64_t, 8> m_scorePoints;
    int fightsfought;
    ConfStruct config;
    int roundsrun;
    int m_maxRounds;
    int m_xSize;
    int m_ySize;
    bool m_isTeams;
    bool checkwin;
    int botteams[8];
    int alive[4];
    bool ifdelete;
    int radiosignals[4][8];
    bool radsigexist[4][8];
    bool m_showResults;
    bool m_fastMode;
    int xstarts[8];
    int ystarts[8];
    bool m_debugEnabled;
    int m_battleMode; //0 - normal, 1 - survival, 2 - Deathmatch
    int runmode; //0 - not running, 1 - running
    int m_maxPoints;
};
#include "robots.h"
#include "mine.h"
#include "radarmissile.h"
#include "missile.h"
#include "radarmissile.h"
#include "beam.h"
#include "rocket.h"
#include "chaff.h"
//#include "explosion.h"

#endif
