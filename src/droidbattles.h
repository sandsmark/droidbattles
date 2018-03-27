/***************************************************************************
                          droidbattles.h  -  description
                             -------------------
    begin                : Sat Apr  1 17:40:01 CEST 2000
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

#ifndef DROIDBATTLES_H
#define DROIDBATTLES_H
#include "matchresult.h"

// include files for QT
#include <qstring.h>
#include <QMenu>
#include <qmenubar.h>
#include <QToolBar>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include <qapplication.h>
#include <qstatusbar.h>
#include <qwidget.h>
#include <QWhatsThis>
#include <qmessagebox.h>
#include <QFileDialog>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qdir.h>
#include <qfile.h>
#include <QTextStream>
#include <qicon.h>
#include <qdatetime.h>
#include <qpixmapcache.h>
#include <QPointer>

// application specific includes
//#include "resource.h"

class CreateBot;
class StartsBatt;
class StartSurvBatt;
class StartDeathBatt;
class BattleArea;
class ConfEdit;
class StartTournament;
class KothTournament;

class StartCup;
class DocBrowser;
class PixButton;
/**
  * This Class is the base class for the application. It sets up the main
  * window and providing buttons for starting other parts of the program
  */
class DroidBattles : public QWidget
{
    Q_OBJECT

public:
    DroidBattles();
    ~DroidBattles();

private:

    void enabletourneys();
    void disabletourneys();

    /** The buttons that are in the main widget */
    QPushButton *menubuttons[12];
    QPixmap *bnpm;
    /** Pointers to the various types of objects the menu object can start */
    // Editor for creating the bots
    QPointer<CreateBot> cre;
    // Base widget for battles
    QPointer<BattleArea> batt;
    // Widget for startup of battle (ie determine which bots should fight)
    QPointer<StartsBatt> ssb;
    // Message box showing some 'about' info about the application
    QMessageBox *aboutb;

    QPointer<KothTournament> kotht;
    QPointer<StartCup> cuptournament;
    QPointer<StartTournament> stment;

    QPointer<DocBrowser> browser;

    ConfEdit *ccf;
    char *currentdir;
    /** Status variables */
    bool editrunning;
    bool battlerunning;

    // State variables for battle and tournament management
    std::array<int, 8> teams;
    int wingames[64];
    int winmatches[64];
    QString newlist[64];
    struct MatchResult results[128];
    int nextround[64];
    int resultcounter;
    int nextroundcount;
    int gamecounter;
    int botsleft;
    int curmainbot;
    int cursecbot;

private slots:
    void enablebattles();
    void disablebattles();

    //Menu Item functions
    void createb();
    void about();
    void showb();
    void quit();
    void editconf();

    void skirmish();
    void startskirmish();
    void stopskirmish();

    void survival();
    void startsurvival();
    void stopsurvival();

    void death();
    void startdeath();
    void stopdeath();

    void tournament();
    void starttourney();
    void stoptourney();
    void managetourney (int wins1, int wins2);

    void koth();
    void startkoth();
    void stopkoth();
    void mankothtourney (int wins1, int wins2);

    void cup();
    void startcupt();
    void stopcup();
    void mancuptourney (int wins1,int wins2);

    void showdoc();
    void onHelpRequested(const QString &word);
    void onConfHelpRequested();
};

#endif

