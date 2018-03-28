/***************************************************************************
                          battlearea.cpp  -  description
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

#include "battlearea.h"

#include "explosion.h"

#include <QLabel>
#include <QCloseEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QStandardPaths>
#include <QSettings>

bool SingleStepMode = false;

/**
	* Constructor, inits area and starts first battle round
	*/
BattleArea::BattleArea(const BattleConfig &battleConfig, bool ifdebug, QPlainTextEdit *dbedit, int *dbl, int *dbm)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Dialog);

    m_debugEnabled = ifdebug;
    m_fastMode = battleConfig.fastMode;
    m_battleMode = battleConfig.mode;
    m_maxPoints = battleConfig.maxPoints;

    m_showResults = !battleConfig.isTournament;

    m_isTeams = battleConfig.isTeams;
    m_xSize = battleConfig.xSize;
    m_ySize = battleConfig.ySize;
    ifdelete = false;

    m_maxRounds = battleConfig.maxRounds;

    // OPen the current config file
    config.load(QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    mainLayout->addLayout(horizontalLayout);

    for (int i = 0; i < maxbots; i++) {
        botteams[i] = battleConfig.teams[i];
    }

    //Initialize vars
    numfights = battleConfig.numFights;
    fightsfought = 0;
    for (int x = 0; x < 8; x++) {
        names[x] = battleConfig.names[x];
        fightswon[x] = 0;
    }

    mydrw = new QLabel();
    horizontalLayout->addWidget(mydrw);
    infowindow = new QWidget();
    infowindow->setLayout(new QGridLayout);
    mainLayout->addWidget(infowindow);

    m_pixmap = QPixmap(m_xSize >> 6, m_ySize >> 6);
    mydrw->setMinimumSize(m_pixmap.size());
    mydrw->show();
    mydrw->setPalette(QPalette(QColor(0, 0, 0)));
    playb = new PixButton("Play", this);
    pauseb = new PixButton("Pause", this);
    singles = new PixButton("Singlestep", this);

    QVBoxLayout *sideLayout = new QVBoxLayout;
    sideLayout->addWidget(playb);
    sideLayout->addWidget(pauseb);
    sideLayout->addWidget(singles);
    sideLayout->addStretch();
    horizontalLayout->addLayout(sideLayout);

    connect(playb, &QAbstractButton::clicked, this, &BattleArea::play);
    connect(pauseb, &QAbstractButton::clicked, this, &BattleArea::pause);
    connect(singles, &QAbstractButton::clicked, this, &BattleArea::singlestep);

    connect(&eventH, &QTimer::timeout, this, &BattleArea::execute);
    if (ifdebug) {
        // keep parameters
        _dbedit = dbedit;
        _dbl = dbl;
        _dbm = dbm;
    }
    missilesLaunched = 0;

    startonebattle(firstrun);

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(PixmapHolder::getpm(PixmapHolder::MetalBackground)));
    palette.setColor(foregroundRole(), Qt::white);
    setPalette(palette);

    QSettings settings;
    restoreGeometry(settings.value("BattleAreaGeometry").toByteArray());
}

/**
	* Starts the timer that calls execute (executed by "play" button)
	*/
void BattleArea::play()
{
    if (m_fastMode == true)
        eventH.start(0); //As fast as possible
    else
        eventH.start(20); //20 ms between ticks (50 times/second)
    runmode = 1;
}

/**
	* Stops the timer that calls execute (executed by "pause" button)
	*/
void BattleArea::pause()
{
    eventH.stop();
    runmode = 0;
}

/**
	* Runs a single battle tick
	*/
void BattleArea::singlestep()
{
    if (m_debugEnabled)
        SingleStepMode = true;
    this->execute();
    if (m_debugEnabled)
        SingleStepMode = false;
}

/**
	* Destructor, deletes self
	*/
BattleArea::~BattleArea()
{
    eventH.stop();
    qDeleteAll(dbgwindows);
    dbgwindows.clear();
    //	if( debugenabled )delete dbgwindow;
    //	for( x=0;x<maxobjects;x++ )
    //		delete objects[x];
}

/**
	* start one round of fight
	* In case this isn't the first round, deallocate previous mem
	*/
void BattleArea::startonebattle(int y)
{
    int x;
    //If this isn't the first run, deallocate the memory
    //from the run before this
    if (y == notfirstround) {
        //Deallocate memory
        for (x = 0; x < maxbots; x++)
            delete binfo[x];
        for (x = 0; x < maxobjects; x++)
            delete objects[x];
    }

    //Randomize start positions and make sure the bots don't start to
    //close to each other
    xstarts[0] = qrand() % m_xSize;
    ystarts[0] = qrand() % m_ySize;
    for (x = 1; x < maxbots; x++) {
        int dst = minstartdistance - 1;
        int tries = 0;
        while (dst < minstartdistance && tries < 128) {
            dst = minstartdistance;
            xstarts[x] = qrand() % m_xSize;
            ystarts[x] = qrand() % m_ySize;
            for (y = 0; y < x; y++) {
                int xdiff = abs(xstarts[y] - xstarts[x]);
                int ydiff = abs(ystarts[y] - ystarts[x]);
                int tdist = int(sqrt((xdiff * xdiff) + (ydiff * ydiff)));
                if (tdist < dst)
                    dst = tdist;
            }
            tries++;
        }
    }

    //Load the bots
    QString tn;
    for (x = 0; x < maxbots; x++) {
        tn = names[x];
        if (!tn.isEmpty()) {
            objects[x] = new Robots(tn, *this, x, config, botteams[x]);
        } else {
            objects[x] = new ScreenObject();
        }

        QGridLayout *gl = qobject_cast<QGridLayout *>(infowindow->layout());
        Q_ASSERT(gl);
        binfo[x] = BotInfo::addBotInfo(gl, x, names[x], objects[x]);
    }

    if (m_debugEnabled) {
        qDeleteAll(dbgwindows);
        dbgwindows.clear();
        // the bot to be debugged is objects[debugbot]
        if (objects[debugbot] == nullptr) {
            QMessageBox::critical(this, "Internal error", "Internal error.\nBot object not created!", QMessageBox::Ok);
            return;
        }
        if (objects[debugbot]->type() != ScreenObject::BotObject) {
            QMessageBox::critical(this, "Internal error", "Internal error.\nBot object wrong type!", QMessageBox::Ok);
            return;
        }
        int nCpus = ((Robots *)objects[debugbot])->cpuCount();
        for (int x = 0; x < nCpus; x++) {
            DebugWindow *dw = new DebugWindow(_dbedit, &_dbl[0], &_dbm[0]);
            connect(dw, &DebugWindow::dumpmem, this, &BattleArea::dmem);
            dw->resize(300, 405);
            dw->show();
            QString title;
            title.sprintf("CPU #%d", x);
            dw->setWindowTitle(title); // set title
            dbgwindows.push_back(dw);
        }
    }

    //Make all other positions as "standard" screenobjects
    for (x = maxbots; x < maxobjects; x++)
        objects[x] = new ScreenObject();

    //Create the infoboxes for the bots
    for (x = 0; x < maxbots; x++) {
        QObject::connect(objects[x], SIGNAL(armorchanged(int)), binfo[x],
                         SLOT(armorupdated(int)));
        QObject::connect(binfo[x], SIGNAL(changeinset(bool)), objects[x],
                         SLOT(setextragfx(bool)));
        QObject::connect(objects[x], SIGNAL(fuelchanged(int, int)), binfo[x],
                         SLOT(updatefuel(int, int)));
        QObject::connect(objects[x], SIGNAL(messagechanged(char *)), binfo[x],
                         SLOT(newmessage(char *)));
    }
    roundsrun = 0;
    infowindow->show();
    m_pixmap.fill(Qt::black);
    mydrw->setPixmap(m_pixmap);

    if (m_fastMode == true) {
        eventH.start(0);
        runmode = 1;
    } else {
        if (!m_debugEnabled) {
            eventH.start(20);
            runmode = 1;
        }
    }
}

/**
	* Executed ~50 times a second (normally)
	* each time one "step" is executed in the battle
	*/

void BattleArea::execute()
{
    //	eventH->stop( );
    int x;
    roundsrun++;
    if (roundsrun > m_maxRounds) //If the times up...
    {
        if (m_battleMode == 1 || m_battleMode == 0) {
            for (x = 0; x < maxbots; x++) {
                objects[x]->eraseObject(&m_pixmap); //Erase all bots (to call a draw)
                delete objects[x];
                objects[x] = new ScreenObject();
            }
        }
        if (m_battleMode == 2) {
            checkwin = true;
            m_maxPoints = 0;
        }
    }
    for (x = 0; x < maxobjects; x++) //Remove the gfx from last round
        objects[x]->eraseObject(&m_pixmap);

    for (x = 0; x < maxobjects; x++) {
        int ifdel = objects[x]->execute(); //Let each object execute,
        //move around and things like that
        if (ifdel == -1) //If the object ordered it's own destruction
        { //Example: shot that gets outside of screen
            objects[x]->eraseObject(&m_pixmap);
            delete objects[x];
            objects[x] = new ScreenObject();
            continue;
        }

        objects[x]->drawObject(&m_pixmap, 0); //Let each object paint itself
        int x2;

        if (objects[x]->type() <= 0) { //Check If the object exists and
            continue; //is a "collidable" object
        }

        for (x2 = (x + 1); x2 < maxobjects; x2++) { //Loop through all possible objects
            //(to check for collisions)
            if (objects[x2]->type() <= 0) {
                continue;
            }

            if (objects[x]->owner() == objects[x2]->owner()) {
                continue;
            }
            if (objects[x]->collisionId() != collenabled && objects[x2]->collisionId() != collenabled) {
                continue;
            }

            int xx1, xx2, yy1, yy2, dist, dx, dy;

            xx1 = objects[x]->xPos(); //
            xx2 = objects[x2]->xPos(); // Get positions
            dx = (xx1 - xx2) / 2; // and distances
            yy1 = objects[x]->yPos(); // between each object
            yy2 = objects[x2]->yPos(); //
            dy = (yy1 - yy2) / 2; //
            dist = int(sqrt((dx * dx) + (dy * dy))); //
            dist *= 2;

            if (dist > ((objects[x]->size() << 6) + (objects[x2]->size() << 6))) { //If they're bigger than their distance they have collided
                continue;
            }

            int xxx;
            for (xxx = 254; xxx > 128; xxx--) {
                if (objects[xxx]->type() == ScreenObject::Destroyed) {
                    delete objects[xxx];
                    objects[xxx] = new Explosion((xx1 + xx2) / 2, (yy1 + yy2) / 2, *this);
                    break;
                }
            }
            int type1, type2, str1, str2;
            type1 = objects[x]->collisionType();
            type2 = objects[x2]->collisionType();
            str1 = objects[x]->collisionStrength(); // Get the damage they will
            str2 = objects[x2]->collisionStrength(); // inflict on each other
            if (type1 == 1) // If he collided with a bot
            {
                objects[x2]->setSpeed(-(objects[x2]->speed() / 2));
                double dir = objects[x2]->direction() * toradians; //Change dir
                objects[x2]->setPosition(cos(dir) * objects[x2]->speed(),
                                         sin(dir) * objects[x2]->speed());
            }
            if (type2 == 1) {
                objects[x]->setSpeed(-(objects[x]->speed() / 2));
                double dir = objects[x]->direction() * toradians;
                objects[x]->setPosition(cos(dir) * objects[x]->speed(),
                                        sin(dir) * objects[x]->speed());
            }
            xx1 = objects[x]->xPos(); //
            xx2 = objects[x2]->xPos(); // Get positions
            dx = xx1 - xx2; // and distances between
            yy1 = objects[x]->yPos(); // each object
            yy2 = objects[x2]->yPos(); //
            dy = yy1 - yy2; //
            dist = int(sqrt(dx * dx + dy * dy)); //

            if (dist < ((objects[x]->size() << 6) + (objects[x2]->size() << 6))
                && objects[x]->type() == ScreenObject::BotObject && objects[x2]->type() == ScreenObject::BotObject) //If they're bigger than their distance, move them apart
            {
                double angl = atan2(dy, dx);
                int dst = (objects[x]->size() << 6) + (objects[x2]->size() << 6) - dist;
                objects[x]->setPosition(cos(angl) * ((dst + 16) / 2), sin(angl) * ((dst + 16) / 2));
                objects[x2]->setPosition(cos(angl + pi) * ((dst + 16) / 2),
                                         sin(angl + pi) * ((dst + 16) / 2));
            }
            int x2owner = objects[x2]->owner();
            if (objects[x2]->objectHit(9, str1) == 1) {
                switch (m_battleMode) {
                case 0:
                    objects[x2]->eraseObject(&m_pixmap);
                    delete objects[x2];
                    objects[x2] = new ScreenObject();
                    break;
                case 1:
                    objects[x2]->eraseObject(&m_pixmap);
                    if (x < 8 && objects[x2]->type() == ScreenObject::BotObject) {
                        fightswon[x2]++;
                        delete objects[x2];
                        if (fightswon[x2] < m_maxPoints) {
                            //Calc X and Y position
                            xstarts[x2] = qrand() % m_xSize;
                            ystarts[x2] = qrand() % m_ySize;
                            objects[x2] = new Robots(names[x2],
                                                     *this, x2, config, botteams[x2], false);
                            QObject::connect(objects[x2],
                                             SIGNAL(armorchanged(int)), binfo[x2],
                                             SLOT(armorupdated(int)));
                            QObject::connect(binfo[x2],
                                             SIGNAL(changeinset(bool)), objects[x2],
                                             SLOT(setextragfx(bool)));
                            QObject::connect(objects[x2],
                                             SIGNAL(fuelchanged(int, int)), binfo[x2],
                                             SLOT(updatefuel(int, int)));
                            QObject::connect(objects[x2],
                                             SIGNAL(messagechanged(char *)), binfo[x2],
                                             SLOT(newmessage(char *)));
                            objects[x2]->objectHit(0, 0);
                        } else {
                            objects[x2] = new ScreenObject();
                            fightswon[x2] = roundsrun;
                        }
                    } else {
                        delete objects[x2];
                        objects[x2] = new ScreenObject();
                    }
                    break;
                case 2: //If it's a deathmatch battle
                    objects[x2]->eraseObject(&m_pixmap);
                    if (objects[x2]->type() == ScreenObject::BotObject) {
                        if (objects[x]->owner() < 8 && x2 != objects[x]->owner())
                            fightswon[objects[x]->owner()]++;
                        checkwin = true;
                        //Calc X and Y position
                        xstarts[x2] = qrand() % m_xSize;
                        ystarts[x2] = qrand() % m_ySize;
                        objects[x2] = new Robots(names[x2], *this,
                                                 x2, config, botteams[x2], false);
                        QObject::connect(objects[x2],
                                         SIGNAL(armorchanged(int)), binfo[x2],
                                         SLOT(armorupdated(int)));
                        QObject::connect(binfo[x2],
                                         SIGNAL(changeinset(bool)), objects[x2],
                                         SLOT(setextragfx(bool)));
                        QObject::connect(objects[x2],
                                         SIGNAL(fuelchanged(int, int)), binfo[x2],
                                         SLOT(updatefuel(int, int)));
                        QObject::connect(objects[x2],
                                         SIGNAL(messagechanged(char *)), binfo[x2],
                                         SLOT(newmessage(char *)));
                        objects[x2]->objectHit(0, 0);
                    } else {
                        delete objects[x2];
                        objects[x2] = new ScreenObject();
                    }
                    break;
                }
            }
            if (objects[x]->objectHit(9, str2) == 1) //If the damage killed him
            {
                switch (m_battleMode) {
                case 0: //If it's a normal battle
                    objects[x]->eraseObject(&m_pixmap); //Erase him
                    delete objects[x];
                    objects[x] = new ScreenObject();
                    x2 = maxobjects;
                    continue;
                    break;
                case 1: //If it's a survival battle
                    objects[x]->eraseObject(&m_pixmap);
                    if (x < 8 && objects[x]->type() == ScreenObject::BotObject) {
                        fightswon[x]++;
                        delete objects[x];
                        x2 = maxobjects;
                        if (fightswon[x] < m_maxPoints) {
                            //Calc X and Y position
                            xstarts[x] = qrand() % m_xSize;
                            ystarts[x] = qrand() % m_ySize;
                            objects[x] = new Robots(names[x], *this,
                                                    x, config, botteams[x], false);
                            QObject::connect(objects[x],
                                             SIGNAL(armorchanged(int)), binfo[x],
                                             SLOT(armorupdated(int)));
                            QObject::connect(binfo[x],
                                             SIGNAL(changeinset(bool)), objects[x],
                                             SLOT(setextragfx(bool)));
                            QObject::connect(objects[x],
                                             SIGNAL(fuelchanged(int, int)), binfo[x],
                                             SLOT(updatefuel(int, int)));
                            QObject::connect(objects[x],
                                             SIGNAL(messagechanged(char *)), binfo[x],
                                             SLOT(newmessage(char *)));
                            objects[x]->objectHit(0, 0);
                        } else {
                            objects[x] = new ScreenObject();
                            fightswon[x] = roundsrun;
                        }
                    } else {
                        delete objects[x];
                        objects[x] = new ScreenObject();
                        x2 = maxobjects;
                        continue;
                    }
                    break;
                case 2: //If it's a deathmatch battle
                    objects[x]->eraseObject(&m_pixmap);
                    if (objects[x]->type() == ScreenObject::BotObject) {
                        if (x2owner < 8 && x != x2owner)
                            fightswon[x2owner]++;
                        delete objects[x];
                        x2 = maxobjects;
                        checkwin = true;
                        //Calc X and Y position
                        xstarts[x] = qrand() % m_xSize;
                        ystarts[x] = qrand() % m_ySize;
                        objects[x] = new Robots(names[x], *this, x,
                                                config, botteams[x], false);
                        QObject::connect(objects[x],
                                         SIGNAL(armorchanged(int)), binfo[x],
                                         SLOT(armorupdated(int)));
                        QObject::connect(binfo[x],
                                         SIGNAL(changeinset(bool)), objects[x],
                                         SLOT(setextragfx(bool)));
                        QObject::connect(objects[x],
                                         SIGNAL(fuelchanged(int, int)), binfo[x],
                                         SLOT(updatefuel(int, int)));
                        QObject::connect(objects[x],
                                         SIGNAL(messagechanged(char *)), binfo[x],
                                         SLOT(newmessage(char *)));
                        objects[x]->objectHit(0, 0);
                    } else {
                        delete objects[x];
                        objects[x] = new ScreenObject();
                        x2 = maxobjects;
                        continue;
                    }
                    break;
                }
            }
        }
    }

    //Here, check if the battle has ended (eg. <= 1 bot or <= 1 team is left)

    int numofbots = 0;
    int botnum = 0;
    if (m_isTeams) //If teams
    {
        alive[0] = 0;
        alive[1] = 0;
        alive[2] = 0;
        alive[3] = 0;
        for (x = 0; x < maxbots; x++) //Mark teams with bots left
        {
            if (objects[x]->type() == ScreenObject::BotObject) {
                int yy;
                yy = objects[x]->team();
                if (yy > 3 || yy < 0)
                    yy = 0;
                alive[yy] = 1;
            }
        }
        for (x = 0; x < 4; x++) //Count them
        {
            if (alive[x] == 1) {
                numofbots++;
                botnum = x;
            }
        }
        if (numofbots <= 1) //If battle is over
        {
            eventH.stop();
            if (numofbots == 1)
                fightswon[botnum]++;
            fightsfought++;
            if (fightsfought >= numfights) //If all rounds of battle is over
            {
                int winbot = 0;
                int curval = 0;
                bool draw = false;
                for (x = 0; x < maxteams; x++) {
                    if (fightswon[x] == curval)
                        draw = true;
                    if (fightswon[x] > curval) {
                        curval = fightswon[x];
                        winbot = x;
                        draw = false;
                    }
                }
                QString msg;
                //				ermsg = new QMessageBox( );
                //				ermsg->setCaption( "Fight ended" );
                if (draw == false) {
                    msg = " Team ";
                    msg += int(winbot) + '1';
                    msg += " won!";
                } else
                    msg = "Fight was a draw";
                //				ermsg->setText( msg );
                //				ermsg->setButtonText( 0, "OK" );
                //				int ret = ermsg->exec( );
                //				delete ermsg;
                QMessageBox::information(0, "Fight Ended", msg);
                ifdelete = true;
            } else
                startonebattle(notfirstround); //If we have rounds left, continue
        } // with a new round
    }

    if (!m_isTeams && (m_battleMode == 0 || m_battleMode == 1)) {
        for (x = 0; x < maxbots; x++) {
            if (objects[x]->type() == ScreenObject::BotObject) {
                numofbots++; //Count the number of bots alive
                botnum = x;
            }
        }
        if (numofbots <= 1) //If the current fight has ended
        {
            eventH.stop(); //Stop doing rounds of fight
            if (numofbots == 1) //If we have a winner ,count up his points
                fightswon[botnum]++;
            fightsfought++;
            if (fightsfought >= numfights) //If we have done all the rounds of
            { // fights we should have, Determine the overall winner
                int curval = 0;
                int curval2 = 1000;
                for (x = 0; x < maxbots; x++) {
                    if (fightswon[x] > curval) {
                        curval = fightswon[x];
                    }
                    if (fightswon[x] < curval2 && names[x] != "") {
                        curval2 = fightswon[x];
                        botnum = x;
                    }
                }
                QString msg;
                if (m_showResults) {
                    switch (m_battleMode) {
                    case 0:
                        for (int xx = 0; xx < 8; xx++) {
                            if (names[xx] != "") {
                                msg += " Bot ";
                                msg += QFileInfo(names[xx]).baseName();
                                msg += " won ";
                                msg += QString::number(fightswon[xx]);
                                msg += " fights.\n";
                            }
                        }
                        break;
                    case 1:
                        msg += " Bot ";
                        msg += QFileInfo(names[botnum]).baseName();
                        msg += " won with ";
                        msg += QString::number(m_maxPoints - fightswon[botnum]);
                        msg += " lives left!\n";
                        for (int xx = 0; xx < 8; xx++) {
                            if (names[xx] != "" && xx != botnum) {
                                msg += " Bot ";
                                msg += QFileInfo(names[xx]).baseName();
                                msg += " survived ";
                                msg += QString::number(fightswon[xx]);
                                msg += " cycles.\n";
                            }
                        }
                        break;
                    }
                    QMessageBox::information(0, "Fight ended", msg);
                } else
                    emit battledone(fightswon[0], fightswon[1]);

                ifdelete = true;
            } else
                startonebattle(notfirstround); //If we have fights left,start a new
        }
    }

    if (m_battleMode == 2 && checkwin) {
        checkwin = false;
        for (x = 0; x < 8; x++) {
            if (fightswon[x] >= m_maxPoints) {
                eventH.stop();
                //				ermsg = new QMessageBox( );
                //				ermsg->setCaption( "Fight ended" ); //Show the win message
                QString msg;
                for (int xx = 0; xx < 8; xx++) {
                    if (names[xx] != "") {
                        msg += " Bot ";
                        msg += QFileInfo(names[xx]).baseName();
                        msg += " got ";
                        msg += QString::number(fightswon[xx]);
                        msg += " frags.\n";
                    }
                }
                //				ermsg->setText( msg );
                //				ermsg->setButtonText( 0, "OK" );
                //				int ret = ermsg->exec( );
                //				delete ermsg;
                QMessageBox::information(0, "Fight ended", msg);
                ifdelete = true;
                break;
            }
        }
    }

    if (m_debugEnabled) //If this is a "quick battle", update register content info and such
        if (objects[debugbot]->type() == ScreenObject::BotObject) // for robots only
        {
            QVector<DebugContents> *dc = ((Robots *)objects[debugbot])->allDebugContents();
            if (dc->size() != dbgwindows.size()) {
                QMessageBox::critical(this, "Internal error", "Internal error.\nWrong number of debug windows!", QMessageBox::Ok);
                return;
            }
            QList<DebugWindow *>::iterator i = dbgwindows.begin();
            QVector<DebugContents>::iterator j = dc->begin();
            for (; i != dbgwindows.end(); i++, j++)
                (*i)->updatedata(*j);
            delete dc;
        }
    //		dbgwindow->updatedata( objects[debugbot]->returndbgcont( ) );

    /*	if( runmode == 1 )
    	{
    		if( iffast )
    			eventH->start( 0 );
    		else
    			eventH->start( 20 );
    	}*/

    if (ifdelete == true)
        deleteLater();

    for (x = 0; x < maxobjects; x++) {
        objects[x]->drawObject(&m_pixmap, 1); //Let each object paint itself
    }
    for (x = 0; x < maxobjects; x++) {
        objects[x]->drawObject(&m_pixmap, 2); //Let each object paint itself
    }
    mydrw->setPixmap(m_pixmap.scaled(mydrw->size(), Qt::KeepAspectRatio));
}

/**
	* If a device wants to add a screenobject (as a shot) he calls
	* this function (via his bot)
	*/
void BattleArea::addscrobject(int owner, int X, int Y, int dir, int type,
                              int arg1, int arg2, void *arg3)
{
    int x;
    for (x = 0; x < maxobjects; x++) {
        if (objects[x]->type() == ScreenObject::Destroyed) {
            delete objects[x];
            Ram *temp3 = (Ram *)arg3;
            switch (type) {
            case 0:
                objects[x] = new ScreenObject();
                break;
            case 1:
                //					objects[x] = new robots( "unnamed.bot",*this,x );
                break;
            case 2:
                objects[x] = new Missile(X, Y, dir, arg1, x, *this);
                break;
            case 3:
                objects[x] = new Mine(X, Y, *this, owner);
                break;
            case 4:
                objects[x] = new RadarMissile(X, Y, dir, arg1, arg2, x, *this, temp3, owner);
                ++missilesLaunched;
                if (m_debugEnabled && (owner == debugbot))
                    ((RadarMissile *)objects[x])->createDbgWindow(missilesLaunched, _dbedit, _dbl, _dbm);
                break;
            case 5:
                objects[x] = new Beam(X, Y, dir, arg1, *this, owner);
                break;
            case 6:
                objects[x] = new Rocket(X, Y, dir, arg1, x, *this, owner);
                break;
            case 7:
                objects[x] = new Chaff(X, Y, dir, arg1, *this);
                break;
            default:
                objects[x] = new ScreenObject();
            }
            break;
        }
    }
}

/**
	* If a device (as the scanner) needs info about
	* the other screenobjects it calls this function
	* (via his bot)
	*/
/*int battlearea::devio( int bot,int dev,int choice,int arg1,int arg2 )
{
	switch ( choice )
	{
		case 1 :     //getXpos
			return objects[arg1]->getXpos( );
		break;
		case 2 :     //getYpos
			return objects[arg1]->getYpos( );
		break;
		case 3 :     //getdir
			return objects[arg1]->getdir( );
		break;
		case 4 :     //getspeed
			return objects[arg1]->getspeed( );
		break;
		case 5 :     //delete screenobject
			delete objects[bot];
			objects[bot] = new screenobject( );
		break;
		case 6 :
			return objects[arg1]->returnradar( );
		break;
		case 7 :
			int x;
			for( x=0;x<maxbots;x++ )
			{
				if( objects[x]->returntype( ) == doesexist && objects[x]->getteam( )
						== bot && ( arg2 == 255 || objects[x]->getnum( ) == arg2 ))
					objects[x]->receiveradio( arg1 );
			}
		break;
		case 8 :
			return objects[arg1]->getteam( );
		break;
		case 9 :
			objects[bot]->objscanned( arg1,arg2 );
		break;
		case 10 :
			return getareainfo( 0 );
		break;
		case 11 :
			return getareainfo( 1 );
		break;
		case 12 :
			return getareainfo( 2 );
		break;

	}
	return 0;
} */

/**
	* Returns info about the battlearea
	*/
/*int battlearea::getareainfo( int choice )
{
	switch ( choice )
	{
		case 0 :
			return xsize;
		break;
		case 1 :
			return ysize;
		break;
		case 2 :
			return battlemode;
		break;
	}
	return 0;
} */

/**
	* This function issues special areal (noncollision) hits.
	* The AS-rocket uses it
	*/
void BattleArea::explosions(int x, int y, int rad, int strength, int whichobject)
{
    int X1, Y1, D1, S1, z;
    for (z = 0; z < maxbots; z++) {
        if (z == whichobject)
            continue;
        if (!objects[z]->areaExplosionAffects())
            continue;
        X1 = objects[z]->xPos();
        Y1 = objects[z]->yPos();
        D1 = int(sqrt(((X1 - x) * (X1 - x)) + ((Y1 - y) * (Y1 - y))));
        if (D1 >= rad)
            continue;
        S1 = strength - (D1 * strength / rad);
        if (objects[z]->objectHit(9, S1) == 1) //If the damage killed him
        {
            objects[z]->eraseObject(&m_pixmap); //Erase him
            switch (m_battleMode) {
            case 0:
                delete objects[z];
                objects[z] = new ScreenObject();
                break;
            case 1:
                if (z < 8 && objects[z]->type() == ScreenObject::BotObject) {
                    fightswon[z]++;
                    delete objects[z];
                    if (fightswon[z] < m_maxPoints) {
                        //Calc X and Y position
                        xstarts[z] = qrand() % m_xSize;
                        ystarts[z] = qrand() % m_ySize;
                        objects[z] = new Robots(names[z], *this, z,
                                                config, botteams[z], false);
                        QObject::connect(objects[z], SIGNAL(armorchanged(int)),
                                         binfo[z], SLOT(armorupdated(int)));
                        QObject::connect(binfo[z], SIGNAL(changeinset(bool)),
                                         objects[z], SLOT(setextragfx(bool)));
                        QObject::connect(objects[z], SIGNAL(fuelchanged(int, int)),
                                         binfo[z], SLOT(updatefuel(int, int)));
                        QObject::connect(objects[z], SIGNAL(messagechanged(char *)),
                                         binfo[z], SLOT(newmessage(char *)));
                    } else {
                        objects[z] = new ScreenObject();
                        fightswon[z] = roundsrun;
                    }
                } else {
                    delete objects[z];
                    objects[z] = new ScreenObject();
                }
                break;
            case 2:
                int x = whichobject;
                int x2 = z;
                objects[x2]->eraseObject(&m_pixmap);
                if (objects[x2]->type() == ScreenObject::BotObject) {
                    if (objects[x]->owner() < 8 && x2 != objects[x]->owner())
                        fightswon[objects[x]->owner()]++;
                    checkwin = true;
                    //Calc X and Y position
                    xstarts[x2] = qrand() % m_xSize;
                    ystarts[x2] = qrand() % m_ySize;
                    objects[x2] = new Robots(names[x2], *this, x2,
                                             config, botteams[x2], false);
                    QObject::connect(objects[x2], SIGNAL(armorchanged(int)),
                                     binfo[x2], SLOT(armorupdated(int)));
                    QObject::connect(binfo[x2], SIGNAL(changeinset(bool)),
                                     objects[x2], SLOT(setextragfx(bool)));
                    QObject::connect(objects[x2], SIGNAL(fuelchanged(int, int)),
                                     binfo[x2], SLOT(updatefuel(int, int)));
                    QObject::connect(objects[x2], SIGNAL(messagechanged(char *)),
                                     binfo[x2], SLOT(newmessage(char *)));
                } else {
                    delete objects[x2];
                    objects[x2] = new ScreenObject();
                }
                break;
            }
        }
    }
    int xxx;
    for (xxx = 254; xxx > 128; xxx--) {
        if (objects[xxx]->type() == ScreenObject::Destroyed) {
            delete objects[xxx];
            objects[xxx] = new Explosion(x, y, *this);
            break;
        }
    }
}

/**
	* Gets xposition for one of the random start positions
	*/
/*int battlearea::getstartx( int bot )
{
	return xstarts[bot];
} */

/**
	* Gets yposition for one o the random start positions
	*/
/*int battlearea::getstarty( int bot )
{
	return ystarts[bot];
} */

/**
	* Dump RAM if pressed in debugwindow
	*/
void BattleArea::dmem()
{
    objects[7]->dumpRam();
}

void BattleArea::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.setValue("BattleAreaGeometry", saveGeometry());
    emit closed();
}
