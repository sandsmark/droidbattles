/***************************************************************************
                          battlearea.h  -  description
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

#ifndef BATTLEAREA_H
#define BATTLEAREA_H

#include <QWidget>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include "botinfo.h"
#include <QScrollArea>
#include "pixbutton.h"
#include "debugwindow.h"
#include <QPlainTextEdit>
#include <QPixmap>
#include "pixmapholder.h"

#include "textmodebattlearea.h"

#include <QList>

class BattleArea;

class Drawable : public QWidget
{
    Q_OBJECT

public:
    Drawable(BattleArea *area);

    void onRedrawRequested();

protected:
    void paintEvent(QPaintEvent * /*event*/);

private:
    BattleArea *m_area;
    QTimer *m_redrawTimer;
};

/**
	* The class that takes care of showing and computing the actual fight
  * @author Andreas Agorander
  */

class BattleArea : public QDialog, public TextmodeBattleArea
{

    Q_OBJECT

public:
    BattleArea(const BattleConfig &battleConfig, bool ifdebug = false,
               QPlainTextEdit *dbedit = NULL, int *dbl = 0, int *dbm = 0);
    ~BattleArea() override;
    void addscrobject(int owner, int X, int Y, int dir, int type, int arg1 = 0,
                      int arg2 = 0, void *arg3 = 0) override;
    //int devio( int bot,int dev,int choice,int arg1,int arg2 );
    void startonebattle(int) override;
    //int	getareainfo( int );
    void explosions(int x, int y, int rad, int strength, int whichobject) override;
    //int getstartx( int );
    //int getstarty( int );

public slots:
    void play();

private slots:

    void execute();
    void pause();
    void singlestep();
    void dmem();

signals:
    void battledone(int, int);
    void closed();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    friend class Drawable;

    void storeScores();

    QList<DebugWindow *> dbgwindows;
    QPlainTextEdit *_dbedit;
    int *_dbl;
    int *_dbm;

    int missilesLaunched;

    Drawable *mydrw;
    QWidget *infowindow;
    QTimer eventH;
    QMessageBox *ermsg;

    PixButton *playb;
    PixButton *pauseb;
    PixButton *singles;

    DebugWindow *dbgwindow;
    QPixmap *dumm;

    int updatescreen;
    QPointer<BotInfo> binfo[8];

    QLabel *m_roundCounter;
    /*		QString names[8];
    		//QPixmap *backpm;
    		int numfights;
    		int fightswon[8];
    		int fightsfought;
    		confstruct config;
    		int roundsrun;
    		int maxrounds;
    		int xsize;
    		int ysize;
    		bool isteams;
    		bool checkwin;
    		int botteams[8];
    		int alive[4];
    		bool ifdelete;
    		int radiosignals[4][8];
    		bool radsigexist[4][8];
    		bool hideresmsg;
    		bool iffast;
    		int xstarts[8];
    		int ystarts[8];
    		bool debugenabled;
    		int battlemode; //0 - normal, 1 - survival, 2 - Deathmatch
    		int runmode; //0 - not running, 1 - running
    		int maxpoints;*/
    // the following flag is true in single step mode
    // and will be used by robCPU::execinstr()
};
extern bool SingleStepMode;

#endif
