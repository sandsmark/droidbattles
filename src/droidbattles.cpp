/***************************************************************************
                          droidbattles.cpp  -  description
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

#include "droidbattles.h"
#include "battlearea.h"
#include "commonsymbols.h"
#include "confedit.h"
#include "createbot.h"
#include "docbrowser.h"
#include "kothtournament.h"
#include "pixbutton.h"
#include "pixmapholder.h"
#include "startcup.h"
#include "startdeathbatt.h"
#include "startsbatt.h"
#include "startsurvbatt.h"
#include "starttournament.h"
#include <QDebug>
#include <ctime>
//Added by qt3to4:
#include <QStandardPaths>
#include <QTextStream>

#define VERSION "2.0.0"
/**
	* Constructor, creates the main menu, it's buttons
	* and connects them
	*/
DroidBattles::DroidBattles()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("DroidBattles " VERSION);

    qsrand(time(nullptr)); //Initialize random seed

    /**
        * If the base dir doesn't exist, create it
        * Same with the file current.cfg
    	*/
    QDir baseDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if (!baseDir.exists()) {
        baseDir.mkpath(baseDir.absolutePath());
    }

    QString defaultConfPath = baseDir.absoluteFilePath("current.cfg");
    if (!QFileInfo::exists(defaultConfPath)) {
        QFile::copy(":/misc/current.cfg", defaultConfPath);
        QFile::setPermissions(defaultConfPath, QFileDevice::WriteOwner | QFileDevice::ReadOwner);
    }

    resize(500, 350); //Set size of window
    setFixedSize(500, 350);

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(PixmapHolder::getpm(PixmapHolder::MainMenu)));
    setPalette(palette);

    QAction *creatorAction = new QAction(this);
    creatorAction->setShortcut(Qt::Key_F2);
    connect(creatorAction, &QAction::triggered, this, &DroidBattles::createb);
    addAction(creatorAction);

    QAction *documentationAction = new QAction(this);
    documentationAction->setShortcut(Qt::Key_F1);
    connect(documentationAction, &QAction::triggered, this, &DroidBattles::showdoc);
    addAction(documentationAction);

    QAction *quitAction = new QAction(this);
    quitAction->setShortcut(Qt::Key_F10);
    connect(quitAction, &QAction::triggered, this, &DroidBattles::quit);
    addAction(quitAction);

    m_createButton = new PixButton("Bot Creator (F2)", this);
    m_configButton = new PixButton("Config editor", this);
    m_skirmishButton = new PixButton("Normal battle", this);
    m_deathmatchButton = new PixButton("Deathmatch battle", this);
    m_survivalButton = new PixButton("Survival battle", this);
    m_leagueButton = new PixButton("League tournament", this);
    m_kothButton = new PixButton("KOTH tournament", this);
    m_cupButton = new PixButton("Cup tournament", this);
    m_creditsButton = new PixButton("About DroidBattles", this);
    m_docButton = new PixButton("Documentation (F1)", this);
    m_quitButton = new PixButton("Quit (F10)", this);

    m_createButton->setGeometry(88, 18, 324, 34);
    m_configButton->setGeometry(68, 58, 364, 34);

    m_skirmishButton->setGeometry(58, 98, 184, 34);
    m_deathmatchButton->setGeometry(58, 138, 184, 34);
    m_survivalButton->setGeometry(58, 178, 184, 34);

    m_leagueButton->setGeometry(258, 98, 184, 34);
    m_kothButton->setGeometry(258, 138, 184, 34);
    m_cupButton->setGeometry(258, 178, 184, 34);
    m_creditsButton->setGeometry(68, 218, 364, 34);
    m_docButton->setGeometry(88, 258, 324, 34);
    m_quitButton->setGeometry(118, 298, 264, 34);

    //Connect the buttons
    connect(m_createButton, &PixButton::clicked, this, &DroidBattles::createb);
    connect(m_configButton, &PixButton::clicked, this, &DroidBattles::editconf);
    connect(m_skirmishButton, &PixButton::clicked, this, &DroidBattles::skirmish);
    connect(m_deathmatchButton, &PixButton::clicked, this, &DroidBattles::death);
    connect(m_survivalButton, &PixButton::clicked, this, &DroidBattles::survival);
    connect(m_leagueButton, &PixButton::clicked, this, &DroidBattles::tournament);
    connect(m_kothButton, &PixButton::clicked, this, &DroidBattles::koth);
    connect(m_cupButton, &PixButton::clicked, this, &DroidBattles::cup);
    connect(m_creditsButton, &PixButton::clicked, this, &DroidBattles::about);
    connect(m_docButton, &PixButton::clicked, this, &DroidBattles::showdoc);
    connect(m_quitButton, &PixButton::clicked, this, &DroidBattles::quit);
}

/**
	*	Destructor, currently does nothing
	*/
DroidBattles::~DroidBattles()
{
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void DroidBattles::showdoc()
{
    browser = new DocBrowser("qrc:/doc/index.html");
}

void DroidBattles::onHelpRequested(const QString &word)
{
    if (!browser) {
        browser = new DocBrowser("qrc:/doc/index.html");
    }
    browser->lookUp(word);
}

/**
	* Executed when the user presses start single battle
	* in the main menu
	*/
void DroidBattles::skirmish()
{
    disablebattles();
    //Start the dialog where you can choose which bots should fight
    ssb = new StartsBatt("singlebattle.save");
    ssb->resize(300, 570);
    ssb->show();
    QObject::connect(ssb, SIGNAL(okclicked()), this,
                     SLOT(startskirmish()));
    QObject::connect(ssb, SIGNAL(cancelclicked()), this,
                     SLOT(stopskirmish()));
}

/**
	* Executed when the user presses OK in the dialog created
	* above, checks file names for the bots and launches battlearea
	* TODO: check that all the files really exist
	*/
void DroidBattles::startskirmish()
{
    std::array<QString, 8> names; //Array for the filenames
    int x, numf, ln, xs, ys;
    int numbo = 0; //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x = 0; x < 8; x++) {
        names[x] = ssb->getbotfile(x);
        if (!names[x].isEmpty()) {
            numbo++;
        }
        teams[x] = ssb->getbotteam(x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1) {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength(); //Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();

        BattleConfig battleConfig;
        battleConfig.names = names;
        battleConfig.numFights = numf;
        battleConfig.maxRounds = ln;
        battleConfig.xSize = xs;
        battleConfig.ySize = ys;
        battleConfig.isTeams = ifteamfight;
        battleConfig.teams = teams;
        battleConfig.isTournament = false;
        battleConfig.random_seed = BattleConfig::seedingDevice();

        batt = new BattleArea(battleConfig);
        batt->show();
    }
    delete ssb;
    enablebattles();
}

/**
	* Executed if the user presses CANCEL in the dialog
	*/
void DroidBattles::stopskirmish()
{
    delete ssb;
    enablebattles();
}

void DroidBattles::survival()
{
    disablebattles();
    ssb = new StartSurvBatt();
    ssb->resize(300, 570);
    ssb->show();
    QObject::connect(ssb, SIGNAL(okclicked()), this,
                     SLOT(startsurvival()));
    QObject::connect(ssb, SIGNAL(cancelclicked()), this,
                     SLOT(stopsurvival()));
}

void DroidBattles::startsurvival()
{
    std::array<QString, 8> names; //Array for the filenames
    int x, numf, ln, xs, ys;
    int numbo = 0; //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x = 0; x < 8; x++) {
        names[x] = ssb->getbotfile(x);
        if (!names[x].isEmpty()) {
            numbo++;
        }
        teams[x] = ssb->getbotteam(x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1) {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength(); //Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();

        BattleConfig battleConfig;
        battleConfig.names = names;
        battleConfig.numFights = numf;
        battleConfig.maxRounds = ln;
        battleConfig.xSize = xs;
        battleConfig.ySize = ys;
        battleConfig.isTeams = ifteamfight;
        battleConfig.teams = teams;
        battleConfig.isTournament = false;
        battleConfig.mode = 1;
        battleConfig.random_seed = BattleConfig::seedingDevice();

        batt = new BattleArea(battleConfig);
        batt->show();
    }
    delete ssb;
    enablebattles();
}

void DroidBattles::stopsurvival()
{
    delete ssb;
    enablebattles();
}

void DroidBattles::death()
{
    disablebattles();
    ssb = new StartDeathBatt();
    ssb->resize(300, 570);
    ssb->show();
    QObject::connect(ssb, SIGNAL(okclicked()), this, SLOT(startdeath()));
    QObject::connect(ssb, SIGNAL(cancelclicked()), this, SLOT(stopdeath()));
}

void DroidBattles::startdeath()
{
    std::array<QString, 8> names; //Array for the filenames
    int x, numf, ln, xs, ys;
    int numbo = 0; //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x = 0; x < 8; x++) {
        names[x] = ssb->getbotfile(x);
        if (!names[x].isEmpty()) {
            numbo++;
        }
        teams[x] = ssb->getbotteam(x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1) {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength(); //Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();

        BattleConfig battleConfig;
        battleConfig.names = names;
        battleConfig.numFights = numf;
        battleConfig.maxRounds = ln;
        battleConfig.xSize = xs;
        battleConfig.ySize = ys;
        battleConfig.isTeams = ifteamfight;
        battleConfig.teams = teams;
        battleConfig.isTournament = false;
        battleConfig.mode = BattleConfig::Deathmatch;
        battleConfig.random_seed = BattleConfig::seedingDevice();

        batt = new BattleArea(battleConfig);
        batt->show();
    }
    delete ssb;
    enablebattles();
}

void DroidBattles::stopdeath()
{
    delete ssb;
    enablebattles();
}

/**
	* Executed if the user presses create bot in the
	* main menu
	*/
void DroidBattles::createb()
{
    cre = new CreateBot();
    cre->resize(520, 500);
    cre->show();

    connect(cre, &CreateBot::helpRequested, this, &DroidBattles::onHelpRequested);
}

/**
	* Executed if the user presses about button
	* in the main menu
	*/
void DroidBattles::about()
{
    QMessageBox::information(this, "About DroidBattles",
                             "DroidBattles " VERSION " 2018 Martin Sandsmark, 2005-10-07 by Andreas Agorander (Bluefire@bluefire.nu)\n"
                             "get the latest version at https://github.com/sandsmark/droidbattles");
}

void DroidBattles::showb()
{
    batt->show();
}

/**
	* Quits the application
	* TODO: check if there is an edit or battle
	* 			running, and don't quit then
	*/
void DroidBattles::quit()
{
    qApp->quit();
}

/**
	*	If user clicks config editor...
	*/
void DroidBattles::editconf()
{
    ccf = new ConfEdit();
    connect(ccf, &ConfEdit::helpRequested, this, &DroidBattles::onConfHelpRequested);
}

/**
	* If user clicks league tournament
	*/
void DroidBattles::tournament()
{
    disabletourneys();
    stment = new StartTournament("League");
    stment->resize(300, 570);
    stment->show();
    QObject::connect(stment, SIGNAL(okclicked()), this,
                     SLOT(starttourney()));
    QObject::connect(stment, SIGNAL(cancelclicked()), this,
                     SLOT(stoptourney()));
}

/**
	* If OK in league tournament dialogue
	*/
void DroidBattles::starttourney()
{
    QString names[64];
    int numofbots = stment->getnumofbots();
    if (numofbots == 0) {
        delete stment;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    int x;
    for (x = 0; x < numofbots; x++) {
        names[x] = stment->getbotfile(x);
        winmatches[x] = 0;
        wingames[x] = 0;
    }
    teams[0] = 0;
    teams[1] = 1;

    BattleConfig battleConfig = stment->getBattleConfig();
    battleConfig.names = { "" };
    battleConfig.names[0] = names[0];
    battleConfig.names[1] = names[1];

    batt = new BattleArea(battleConfig);

    connect(batt, &BattleArea::battledone, this, &DroidBattles::managetourney);
    connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);
    batt->show();
    stment->hide();
    curmainbot = 0;
    cursecbot = 1;
}

/**
	* If cancel in league tournament dialogue
	*/
void DroidBattles::stoptourney()
{
    enabletourneys();
    delete stment;
}

/**
	* During a tournament the battledone from battlearea is connected
	* to this function. It checks which bots should fight next, and
	* contains the code executed when all matches are fought
	*/
void DroidBattles::managetourney(int wins1, int wins2)
{

    QString names[64];
    int numofbots = stment->getnumofbots();
    int x;
    if (numofbots == 0) {
        delete stment;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    for (x = 0; x < numofbots; x++) {
        names[x] = stment->getbotfile(x);
        //		winmatches[x] = 0;
        //		wingames[x] = 0;
    }

    winmatches[curmainbot] += wins1;
    winmatches[cursecbot] += wins2;
    if (wins1 > wins2) {
        wingames[curmainbot]++;
    }
    if (wins1 < wins2) {
        wingames[cursecbot]++;
    }

    cursecbot++;

    if (cursecbot == numofbots) {
        curmainbot++;
        cursecbot = curmainbot + 1;
    }

    if (curmainbot >= numofbots - 1) {
        QFile f("tournament.html");
        if (!f.open(QIODevice::WriteOnly)) {
            //TODO: Add error mesage
            delete stment;
            enabletourneys();
            return;
        }
        bool taken[64];
        int resorder[64];
        for (x = 0; x < 64; x++) {
            taken[x] = false;
            resorder[x] = -1;
        }
        for (x = 0; x < numofbots; x++) //Sort the bots in order after their results
        {
            int y;
            int maxpointg = -1;
            int maxpointm = -1;
            int curmaxbot = -1;
            for (y = 0; y < numofbots; y++) {
                if (!taken[y] && (wingames[y] > maxpointg || (wingames[y] == maxpointg && winmatches[y] > maxpointm))) {
                    maxpointg = wingames[y];
                    maxpointm = winmatches[y];
                    curmaxbot = y;
                }
            }
            resorder[x] = curmaxbot;
            taken[curmaxbot] = true;
        }

        QTextStream s(&f);
        QString temp;

        s << "<HTML>\n";
        s << "<HEAD>\n";
        s << "<TITLE>Tournament results</TITLE>\n";
        s << "</HEAD>\n";
        s << "<BODY>\n";
        s << "<TABLE border=1>\n";
        s << "<TR>\n";
        s << "<TD>Placement</TD>\n";
        s << "<TD>Bot name</TD>\n";
        s << "<TD>Bots defeated</TD>\n";
        s << "<TD>Single fights won</TD>\n";
        s << "</TR>\n";
        for (x = 0; x < numofbots; x++) {
            s << "<TR>\n";
            s << "<TD>" << x + 1 << "</TD>\n";
            s << "<TD>\n";
            temp = names[resorder[x]];
            int pos = temp.lastIndexOf("/");
            temp = temp.right(temp.length() - pos - 1);
            s << temp;
            s << "</TD>\n";
            s << "<TD>" << wingames[resorder[x]] << "</TD>\n";
            s << "<TD>" << winmatches[resorder[x]] << "</TD>\n";
            s << "</TR>\n";
        }
        s << "</TABLE>\n";
        s << "Random seed used: " << stment->getseed();
        s << "</BODY>";
        s << "</HTML>";
        delete stment;
        f.close();
        enabletourneys();
        QString tempdc = QDir::currentPath();
        tempdc += "/tournament.html";
        browser = new DocBrowser(tempdc);
    } else {
        teams[0] = 0;
        teams[1] = 1;

        BattleConfig battleConfig = stment->getBattleConfig();
        battleConfig.names[0] = names[curmainbot];
        battleConfig.names[1] = names[cursecbot];

        batt = new BattleArea(battleConfig);

        connect(batt, &BattleArea::battledone, this, &DroidBattles::managetourney);
        connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);
        batt->show();
    }
}

/**
	*	If user clicks KOTH tournament...
	*/
void DroidBattles::koth()
{
    disabletourneys();
    kotht = new KothTournament();
    kotht->resize(300, 570);
    kotht->show();
    connect(kotht, &KothTournament::okclicked, this, &DroidBattles::startkoth);
    connect(kotht, &KothTournament::cancelclicked, this,
            &DroidBattles::stopkoth);
}

/**
	*	If OK in KOTH tournament dialogue
	*/
void DroidBattles::startkoth()
{
    QString names[64];
    int numofbots = kotht->getnumofbots();
    int numf, ln, xs, ys;
    if (numofbots == 0) {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    int x;
    for (x = 0; x < numofbots; x++) {
        names[x] = kotht->getbotfile(x);
    }
    numf = kotht->getnumfights(); //Get the number of fights
    ln = kotht->getlength(); //Get the max length of fight
    xs = kotht->getxsize();
    ys = kotht->getysize();

    teams[0] = 0;
    teams[1] = 1;

    BattleConfig battleConfig = kotht->getBattleConfig();
    battleConfig.names[0] = names[numofbots - 2];
    battleConfig.names[1] = names[numofbots - 1];

    batt = new BattleArea(battleConfig);
    connect(batt, &BattleArea::battledone, this, &DroidBattles::mankothtourney);
    connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);
    batt->show();
    kotht->hide();
    curmainbot = numofbots - 2;
    cursecbot = numofbots - 1;
}

/**
	*	If cancel in KOTH dialogue
	*/
void DroidBattles::stopkoth()
{
    delete kotht;
    enabletourneys();
}

/**
	*	During a KOTH tournament the battledone signal from battlearea is connected here.
	* This function takes care of keeping the score table, start the next battle and
	* write the results
	*/
void DroidBattles::mankothtourney(int wins1, int wins2)
{
    QString names[64];
    int numofbots = kotht->getnumofbots();
    int x;
    if (numofbots == 0) {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    for (x = 0; x < numofbots; x++) {
        names[x] = kotht->getbotfile(x);
        //		winmatches[x] = 0;
        //		wingames[x] = 0;
    }

    results[curmainbot].secbot = cursecbot;
    results[curmainbot].mainbotwins = wins1;
    results[curmainbot].secbotwins = wins2;

    //If mainbot lost
    if (wins2 > wins1) {
        //mainbot in result array
        newlist[curmainbot + 1] = names[curmainbot];
        //Change mainbot for new battle
        curmainbot--;
        if (curmainbot == -1) {
            newlist[curmainbot + 1] = names[cursecbot];
        }

    } else {
        //secbot in result array
        newlist[curmainbot + 1] = names[cursecbot];

        //Change mainbot for new battle
        cursecbot = curmainbot;
        curmainbot--;
        if (curmainbot == -1) {
            newlist[curmainbot + 1] = names[curmainbot + 1];
        }
    }

    if (curmainbot == -1) {
        QFile f("currentKOTH.table");
        if (!f.open(QIODevice::WriteOnly)) {
            //TODO: Add error mesage
            delete kotht;
            enabletourneys();
            return;
        }

        QTextStream s(&f);
        QString temp;

        s << "Numberofbot:"
          << " " << numofbots << "\n";
        for (x = 0; x < numofbots; x++) {
            s << x + 1 << ". " << newlist[x] << "\n";
        }
        s << "Numberoffights:"
          << " " << kotht->getnumfights() << "\n";
        s << "Length:"
          << " " << kotht->getlength() << "\n";
        s << "Xsize:"
          << " " << kotht->getxsize() << "\n";
        s << "Ysize:"
          << " " << kotht->getysize() << "\n";
        s << "Iffast:"
          << " " << kotht->getiffast() << "\n";
        f.close();

        QFile f2("Kothresults.html");
        if (!f2.open(QIODevice::WriteOnly)) {
            //TODO: Add error mesage
            delete kotht;
            enabletourneys();
            return;
        }

        QTextStream s2(&f2);

        s2 << "<HTML>\n";
        s2 << "<HEAD>\n";
        s2 << "<TITLE>KOTH results</TITLE>\n";
        s2 << "</HEAD>\n";
        s2 << "<BODY>\n";
        s2 << "<TABLE border=1>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Pos</TD>\n";
        s2 << "<TD>Bot name</TD>\n";
        s2 << "</TR>\n";
        for (x = 0; x < numofbots; x++) {
            s2 << "<TR>\n";
            s2 << "<TD>" << x + 1 << "</TD>\n";
            s2 << "<TD>\n";
            temp = newlist[x];
            int pos = temp.lastIndexOf("/");
            temp = temp.right(temp.length() - pos - 1);
            s2 << temp;
            s2 << "</TD>\n";
            s2 << "</TR>\n";
        }
        s2 << "</TABLE>\n";
        s2 << "<P>"
           << "Single match results: "
           << "</P>\n";
        s2 << "<TABLE border=1>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Match nr</TD>\n";
        s2 << "<TD>Defender</TD>\n";
        s2 << "<TD>Attacker</TD>\n";
        s2 << "<TD>Results</TD>\n";
        s2 << "</TR>\n";
        for (x = numofbots - 2; x >= 0; x--) {
            s2 << "<TR>\n";
            s2 << "<TD>" << numofbots - x - 1 << "</TD>\n";
            s2 << "<TD>\n";

            temp = names[x];
            int pos = temp.lastIndexOf("/");
            temp = temp.right(temp.length() - pos - 1);
            s2 << temp;
            s2 << "</TD>\n";

            s2 << "<TD>\n";
            temp = names[results[x].secbot];
            pos = temp.lastIndexOf("/");
            temp = temp.right(temp.length() - pos - 1);
            s2 << temp;
            s2 << "</TD>\n";

            s2 << "<TD> " << results[x].mainbotwins << " - " << results[x].secbotwins << "</TD>\n";

            s2 << "</TR>\n";
        }
        s2 << "</TABLE>";
        s2 << "Random seed used: " << kotht->getseed();
        s2 << "</BODY>";
        s2 << "</HTML>";

        f2.close();
        delete kotht;
        enabletourneys();
        QString tempdc = QDir::currentPath();
        tempdc += "/Kothresults.html";
        browser = new DocBrowser(tempdc);
    } else {
        teams[0] = 0;
        teams[1] = 1;

        BattleConfig battleConfig = kotht->getBattleConfig();
        battleConfig.names[0] = names[curmainbot];
        battleConfig.names[1] = names[cursecbot];

        batt = new BattleArea(battleConfig);

        connect(batt, &BattleArea::battledone, this, &DroidBattles::mankothtourney);
        connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);

        batt->show();
    }
}

void DroidBattles::cup()
{
    disabletourneys();
    cuptournament = new StartCup();
    cuptournament->resize(300, 570);
    cuptournament->show();
    QObject::connect(cuptournament, SIGNAL(okclicked()), this,
                     SLOT(startcupt()));
    QObject::connect(cuptournament, SIGNAL(cancelclicked()), this,
                     SLOT(stopcup()));
}

void DroidBattles::startcupt()
{
    resultcounter = 0;
    nextroundcount = 0;
    botsleft = cuptournament->getnumofbots();
    QString names[64];
    int numofbots = cuptournament->getnumofbots();
    if (numofbots == 0) {
        delete cuptournament;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    int x;
    for (x = 0; x < numofbots; x++) {
        names[x] = cuptournament->getbotfile(x);
        nextround[x] = x;
    }

    teams[0] = 0;
    teams[1] = 1;

    curmainbot = 0;
    cursecbot = 1;

    BattleConfig battleConfig = cuptournament->getBattleConfig();
    battleConfig.names[0] = names[0];
    battleConfig.names[1] = names[1];
    batt = new BattleArea(battleConfig);
    connect(batt, &BattleArea::battledone, this, &DroidBattles::mancuptourney);
    connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);
    batt->show();
    cuptournament->hide();
}

void DroidBattles::stopcup()
{
    delete cuptournament;
    enabletourneys();
}

void DroidBattles::mancuptourney(int wins1, int wins2)
{
    QString names[64];
    int numofbots = cuptournament->getnumofbots();
    int x;
    if (numofbots == 0) {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64) {
        numofbots = 64;
    }
    for (x = 0; x < numofbots; x++) {
        names[x] = cuptournament->getbotfile(x);
        //		winmatches[x] = 0;
        //		wingames[x] = 0;
    }

    results[resultcounter].mainbot = nextround[curmainbot];
    results[resultcounter].secbot = nextround[cursecbot];
    results[resultcounter].mainbotwins = wins1;
    results[resultcounter].secbotwins = wins2;
    resultcounter++;

    if (wins1 >= wins2) {
        nextround[nextroundcount] = nextround[curmainbot];
    } else {
        nextround[nextroundcount] = nextround[cursecbot];
    }

    botsleft--;
    curmainbot += 2;
    cursecbot += 2;
    nextroundcount++;

    if (botsleft == 2 || botsleft == 4 || botsleft == 8 || botsleft == 16 || botsleft == 32) {
        curmainbot = 0;
        cursecbot = 1;
        nextroundcount = 0;
    }
    if (botsleft == 1) {
        //write results
        QFile f2("Cupresults.html");
        if (!f2.open(QIODevice::WriteOnly)) {
            //TODO: Add error mesage
            delete cuptournament;
            enabletourneys();
            return;
        }

        QTextStream s2(&f2);
        s2 << "<HTML>\n";
        s2 << "<HEAD>\n";
        s2 << "<TITLE>Cup results</TITLE>\n";
        s2 << "</HEAD>\n";
        s2 << "<BODY>\n";
        s2 << "<TABLE border=1>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Bot1</TD><TD>Bot2</TD><TD>Result</TD></TR>\n";

        int xxx = cuptournament->getnumofbots();
        resultcounter = 0;
        int x;
        while (xxx > 1) {
            for (x = 0; x < xxx; x += 2) {
                s2 << "<TR><TD>" << names[results[resultcounter].mainbot]
                   << "</TD><TD>" << names[results[resultcounter].secbot]
                   << "</TD><TD>" << results[resultcounter].mainbotwins
                   << " - " << results[resultcounter].secbotwins << "</TD></TR>\n";
                resultcounter++;
            }
            s2 << "<HR>\n";
            xxx /= 2;
        }
        s2 << "</TABLE>\n"
           << "Winner: " << names[nextround[0]] << "\n<BR>";
        s2 << "Random seed used: " << cuptournament->getseed();
        s2 << "\n</BODY>\n</HTML>";
        f2.close();
        QString tempdc = QDir::currentPath();
        tempdc += "/Cupresults.html";
        browser = new DocBrowser(tempdc);
        delete cuptournament;
        enabletourneys();
        return;
    }

    teams[0] = 0;
    teams[1] = 1;

    BattleConfig battleConfig = cuptournament->getBattleConfig();
    battleConfig.names[0] = names[nextround[curmainbot]];
    battleConfig.names[1] = names[nextround[cursecbot]];

    batt = new BattleArea(battleConfig);
    connect(batt, &BattleArea::battledone, this, &DroidBattles::mancuptourney);
    connect(batt, &BattleArea::closed, this, &DroidBattles::enabletourneys);
    batt->show();
}

void DroidBattles::enabletourneys()
{
    m_leagueButton->setEnabled(true);
    m_kothButton->setEnabled(true);
    m_cupButton->setEnabled(true);
}

void DroidBattles::disabletourneys()
{
    m_leagueButton->setEnabled(false);
    m_kothButton->setEnabled(false);
    m_cupButton->setEnabled(false);
}

void DroidBattles::enablebattles()
{
    m_skirmishButton->setEnabled(true);
    m_deathmatchButton->setEnabled(true);
    m_survivalButton->setEnabled(true);
}

void DroidBattles::disablebattles()
{
    m_skirmishButton->setEnabled(false);
    m_deathmatchButton->setEnabled(false);
    m_survivalButton->setEnabled(false);
}

void DroidBattles::onConfHelpRequested()
{
    if (!browser) {
        browser = new DocBrowser("qrc:/doc/index-8.html");
    } else {
        browser->setSource(QUrl("qrc:/doc/index-8.html"));
    }
}
