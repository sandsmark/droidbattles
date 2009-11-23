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
#include "createbot.h"
#include "startsbatt.h"
#include "startsurvbatt.h"
#include "startdeathbatt.h"
#include "battlearea.h"
#include "commonsymbols.h"
#include "confedit.h"
#include "starttournament.h"
#include <sys/time.h>
#include <sys/resource.h>
#include "installdir.h"
#include "kothtournament.h"
#include "startcup.h"
#include "docbrowser.h"
#include "pixbutton.h"
#include "pixmapholder.h"
#include <time.h>
//Added by qt3to4:
#include <Q3TextStream>

#define VERSION "1.0.7"
/**
	* Constructor, creates the main menu, it's buttons
	* and connects them
	*/
DroidBattles::DroidBattles()
{
    setCaption ("DroidBattles " VERSION);
    setpriority (PRIO_PROCESS, 0, 5);  //Lower process execution priority
    srandom (time (0));     //Initialize random seed

    /**
    	* If the dir homedir/droidbattles doesn't exist, create it
    	* Same with the file homedir/droidbattles/current.cfg
    	*/
    QDir d = QDir::home();
    if (!d.cd ("droidbattles"))
    {
        d.mkdir ("droidbattles");
        d.cd ("droidbattles");
    }
    QString temp = QDir::homeDirPath();
    temp += "/droidbattles/current.cfg";
    QFile f (temp);
    if (!f.exists())
    {
        temp = returninstalldir();
        temp += "/current.cfg";
        QFile f2 (temp);
        f2.open (QIODevice::ReadOnly);
        f.open (QIODevice::WriteOnly);
        char *buf = new char[2000];
        int num = f2.readBlock (buf,2000);
        f.writeBlock (buf,num);
        f.close();
        f2.close();
        delete buf;
    }

    resize (500,350);	//Set size of window
    setFixedSize (500,350);

    //Load all pixmaps used by the application
    QString fname = returninstalldir();
    fname += "/pixmaps/mainmenu.png";
    Pixmapholder::addpm (fname,0);

    fname = returninstalldir();
    fname += "/pixmaps/backbutton.xpm";
    Pixmapholder::addpm (fname,1);

    fname = returninstalldir();
    fname += "/pixmaps/metal.png";
    Pixmapholder::addpm (fname,2);

    fname = returninstalldir();
    fname += "/pixmaps/metalback2.png";
    Pixmapholder::addpm (fname,3);

    fname = returninstalldir();
    fname += "/pixmaps/radarmissile.bmp";
    Pixmapholder::addpm (fname,4);

    fname = returninstalldir();
    fname += "/pixmaps/chaff.bmp";
    Pixmapholder::addpm (fname,5);

    fname = returninstalldir();
    fname += "/pixmaps/mine.xpm";
    Pixmapholder::addpm (fname,6);

    fname = returninstalldir();
    fname += "/pixmaps/missile.xpm";
    Pixmapholder::addpm (fname,7);

    setBackgroundPixmap (Pixmapholder::getpm (0));

    menubuttons[0] = new PixButton ("Bot-creator",1, this);
    menubuttons[1] = new PixButton ("Config editor",1, this);
    menubuttons[2] = new PixButton ("Normal battle",1, this);
    menubuttons[3] = new PixButton ("Deathmatch battle",1, this);
    menubuttons[4] = new PixButton ("Survival battle",1, this);
    menubuttons[5] = new PixButton ("League tournament",1, this);
    menubuttons[6] = new PixButton ("KOTH tournament",1, this);
    menubuttons[7] = new PixButton ("Cup tournament",1, this);
    menubuttons[8] = new PixButton ("About DroidBattles",1, this);
    menubuttons[9] = new PixButton ("Documentation",1, this);
    menubuttons[10] = new PixButton ("Quit",1, this);

    menubuttons[0]->setGeometry (90,20,320,30);
    menubuttons[1]->setGeometry (70,60,360,30);
    menubuttons[2]->setGeometry (60,100,180,30);
    menubuttons[3]->setGeometry (55,140,185,30);
    menubuttons[4]->setGeometry (60,180,180,30);
    menubuttons[5]->setGeometry (260,100,180,30);
    menubuttons[6]->setGeometry (260,140,185,30);
    menubuttons[7]->setGeometry (260,180,180,30);
    menubuttons[8]->setGeometry (70,220,360,30);
    menubuttons[9]->setGeometry (90,260,320,30);
    menubuttons[10]->setGeometry (120,300,260,30);

    //Connect the buttons
    QObject::connect (menubuttons[0], SIGNAL (clicked()), this,
                      SLOT (createb()));
    QObject::connect (menubuttons[2], SIGNAL (clicked()), this,
                      SLOT (skirmish()));
    QObject::connect (menubuttons[3], SIGNAL (clicked()), this,
                      SLOT (death()));
    QObject::connect (menubuttons[4], SIGNAL (clicked()), this,
                      SLOT (survival()));
    QObject::connect (menubuttons[10], SIGNAL (clicked()), this,
                      SLOT (quit()));
    QObject::connect (menubuttons[8], SIGNAL (clicked()), this,
                      SLOT (about()));
    QObject::connect (menubuttons[9], SIGNAL (clicked()), this,
                      SLOT (showdoc()));
    QObject::connect (menubuttons[1], SIGNAL (clicked()), this,
                      SLOT (editconf()));
    QObject::connect (menubuttons[5], SIGNAL (clicked()), this,
                      SLOT (tournament()));
    QObject::connect (menubuttons[6], SIGNAL (clicked()), this,
                      SLOT (koth()));
    QObject::connect (menubuttons[7], SIGNAL (clicked()), this,
                      SLOT (cup()));

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
    QString temp = returninstalldir();
    temp += "/doc/index.html";
    browser = new Docbrowser (temp);
}
/**
	* Executed when the user presses start single battle
	* in the main menu
	*/
void DroidBattles::skirmish()
{
    disablebattles();
    //Start the dialog where you can choose which bots should fight
    ssb = new startsbatt();
    ssb->resize (300,570);
    ssb->show();
    QObject::connect (ssb,SIGNAL (okclicked()),this,
                      SLOT (startskirmish()));
    QObject::connect (ssb,SIGNAL (cancelclicked()),this,
                      SLOT (stopskirmish()));
}

/**
	* Executed when the user presses OK in the dialog created
	* above, checks file names for the bots and launches battlearea
	* TODO: check that all the files really exist
	*/
void DroidBattles::startskirmish()
{
    QString names[8];	//Array for the filenames
    int x,numf,ln,xs,ys;
    int numbo=0;      //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x=0; x<8; x++)
    {
        names[x] = ssb->getbotfile (x);
        if (!names[x].isEmpty())
            numbo++;
        teams[x] = ssb->getbotteam (x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1)
    {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength();			//Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();
        batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),
                                (char *) names[2].data(), (char *) names[3].data(),
                                (char *) names[4].data(), (char *) names[5].data(),
                                (char *) names[6].data(), (char *) names[7].data(),
                                numf,ln,xs,ys,ifteamfight,teams,false,false);
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
    ssb = new startsurvbatt();
    ssb->resize (300,570);
    ssb->show();
    QObject::connect (ssb,SIGNAL (okclicked()),this,
                      SLOT (startsurvival()));
    QObject::connect (ssb,SIGNAL (cancelclicked()),this,
                      SLOT (stopsurvival()));
}

void DroidBattles::startsurvival()
{
    QString names[8];	//Array for the filenames
    int x,numf,ln,xs,ys;
    int numbo=0;      //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x=0; x<8; x++)
    {
        names[x] = ssb->getbotfile (x);
        if (!names[x].isEmpty())
            numbo++;
        teams[x] = ssb->getbotteam (x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1)
    {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength();			//Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();
        batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),
                                (char *) names[2].data(), (char *) names[3].data(),
                                (char *) names[4].data(), (char *) names[5].data(),
                                (char *) names[6].data(), (char *) names[7].data(),
                                1,ln,xs,ys,false,teams,false,ifteamfight,1,numf);
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
    ssb = new startdeathbatt();
    ssb->resize (300,570);
    ssb->show();
    QObject::connect (ssb,SIGNAL (okclicked()),this,SLOT (startdeath()));
    QObject::connect (ssb,SIGNAL (cancelclicked()),this,SLOT (stopdeath()));
}

void DroidBattles::startdeath()
{
    QString names[8];	//Array for the filenames
    int x,numf,ln,xs,ys;
    int numbo=0;      //Counter for the number of them who are filled in
    bool ifteamfight;
    for (x=0; x<8; x++)
    {
        names[x] = ssb->getbotfile (x);
        if (!names[x].isEmpty())
            numbo++;
        teams[x] = ssb->getbotteam (x);
    }
    ifteamfight = ssb->getifteams();
    if (numbo > 1)
    {
        //Create the widget that takes care of the actual battle
        numf = ssb->getnumfights(); //Get the number of fights
        ln = ssb->getlength();			//Get the max length of fight
        xs = ssb->getxsize();
        ys = ssb->getysize();
        batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),
                                (char *) names[2].data(), (char *) names[3].data(),
                                (char *) names[4].data(), (char *) names[5].data(),
                                (char *) names[6].data(), (char *) names[7].data(),
                                1,ln,xs,ys,false,teams,false,ifteamfight,2,numf);
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
    cre = new createbot();
    cre->resize (520,500);
    cre->show();
}

/**
	* Executed if the user presses about button
	* in the main menu
	*/
void DroidBattles::about()
{
    QMessageBox::information (this, "About DroidBattles",
                              "DroidBattles " VERSION " 2005-10-07 by Andreas Agorander (Bluefire@bluefire.nu)\n"
                              "get the latest version at http://www.bluefire.nu/droidbattles");
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
    delete this;
}

/**
	*	If user clicks config editor...
	*/
void DroidBattles::editconf()
{
    ccf = new confedit();
}

/**
	* If user clicks league tournament
	*/
void DroidBattles::tournament()
{
    disabletourneys();
    stment = new starttournament();
    stment->resize (300,570);
    stment->show();
    QObject::connect (stment,SIGNAL (okclicked()),this,
                      SLOT (starttourney()));
    QObject::connect (stment,SIGNAL (cancelclicked()),this,
                      SLOT (stoptourney()));
}

/**
	* If OK in league tournament dialogue
	*/
void DroidBattles::starttourney()
{
    QString names[64];
    int numofbots = stment->getnumofbots();
    int numf,ln,xs,ys;
    if (numofbots == 0)
    {
        delete stment;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    int x;
    for (x=0; x<numofbots; x++)
    {
        names[x] = stment->getbotfile (x);
        winmatches[x] = 0;
        wingames[x] = 0;
    }
    numf = stment->getnumfights(); //Get the number of fights
    ln = stment->getlength();			//Get the max length of fight
    xs = stment->getxsize();
    ys = stment->getysize();
    seed = stment->getseed();
    if (!seed) seed = random();
    srandom (seed);
    teams[0] = 0;
    teams[1] = 1;

    batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),
                            "","","","","","",numf,ln,xs,ys,false,teams,true,stment->getiffast());
    QObject::connect (batt, SIGNAL (battledone (int,int)),
                      this, SLOT (managetourney (int,int)));
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
void DroidBattles::managetourney (int wins1, int wins2)
{

    QString names[64];
    int numofbots = stment->getnumofbots();
    int numf,ln,xs,ys,x;
    if (numofbots == 0)
    {
        delete stment;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    for (x=0; x<numofbots; x++)
    {
        names[x] = stment->getbotfile (x);
//		winmatches[x] = 0;
//		wingames[x] = 0;
    }

    winmatches[curmainbot] += wins1;
    winmatches[cursecbot] += wins2;
    if (wins1 > wins2) wingames[curmainbot]++;
    if (wins1 < wins2) wingames[cursecbot]++;

    cursecbot++;

    if (cursecbot == numofbots)
    {
        curmainbot++;
        cursecbot = curmainbot + 1;
    }

    if (curmainbot >= numofbots - 1)
    {
        QFile f ("tournament.html");
        if (!f.open (QIODevice::WriteOnly))
        {
            //TODO: Add error mesage
            delete stment;
            enabletourneys();
            return;
        }
        bool taken[64];
        int resorder[64];
        for (x=0; x<64; x++)
        {
            taken[x] = false;
            resorder[x] = -1;
        }
        for (x=0; x<numofbots; x++)   //Sort the bots in order after their results
        {
            int y;
            int maxpointg=-1;
            int maxpointm=-1;
            int curmaxbot=-1;
            for (y=0; y<numofbots; y++)
            {
                if (taken[y] == false && (wingames[y] > maxpointg ||
                                          (wingames[y] == maxpointg && winmatches[y] > maxpointm)))
                {
                    maxpointg = wingames[y];
                    maxpointm = winmatches[y];
                    curmaxbot = y;
                }
            }
            resorder[x] = curmaxbot;
            taken[curmaxbot] = true;
        }

        Q3TextStream s (&f);
        QString temp;

        s << "<HTML>\n";
        s << "<HEAD>\n";
        s << "<TITLE>Tournament results</TITLE>\n";
        s << "</HEAD>\n";
        s << "<BODY>\n";
        s << "<TABLE>\n";
        s << "<TR>\n";
        s << "<TD>Pos</TD>\n";
        s << "<TD>Bot name</TD>\n";
        s << "<TD>Bots defeated</TD>\n";
        s << "<TD>Single fights won</TD>\n";
        s << "</TR>\n";
        for (x=0; x<numofbots; x++)
        {
            s << "<TR>\n";
            s << "<TD>" << x+1 << "</TD>\n";
            s << "<TD>\n";
            temp = names[resorder[x]];
            int pos = temp.findRev ("/",temp.length());
            temp = temp.right (temp.length()-pos-1);
            s << temp.data();
            s << "</TD>\n";
            s << "<TD>" << wingames[resorder[x]] << "</TD>\n";
            s << "<TD>" << winmatches[resorder[x]] << "</TD>\n";
            s << "</TR>\n";
        }
        s << "</TABLE>\n";
        s << "Random seed used: " << seed;
        s << "</BODY>";
        s << "</HTML>";
        delete stment;
        f.close();
        enabletourneys();
        QString tempdc = QDir::currentDirPath();
        tempdc += "/tournament.html";
        browser = new Docbrowser (tempdc);
    }
    else
    {
        numf = stment->getnumfights(); //Get the number of fights
        ln = stment->getlength();			//Get the max length of fight
        xs = stment->getxsize();
        ys = stment->getysize();

        teams[0] = 0;
        teams[1] = 1;

        batt = new battlearea ( (char *) names[curmainbot].data(),
                                (char *) names[cursecbot].data(),"","","","","","",numf,
                                ln,xs,ys,false,teams,true,stment->getiffast());
        QObject::connect (batt, SIGNAL (battledone (int,int)),
                          this, SLOT (managetourney (int,int)));
        batt->show();
    }
}

/**
	*	If user clicks KOTH tournament...
	*/
void DroidBattles::koth()
{
    disabletourneys();
    kotht = new kothtournament();
    kotht->resize (300,570);
    kotht->show();
    QObject::connect (kotht,SIGNAL (okclicked()),this,SLOT (startkoth()));
    QObject::connect (kotht,SIGNAL (cancelclicked()),this,
                      SLOT (stopkoth()));
}

/**
	*	If OK in KOTH tournament dialogue
	*/
void DroidBattles::startkoth()
{
    QString names[64];
    int numofbots = kotht->getnumofbots();
    int numf,ln,xs,ys;
    if (numofbots == 0)
    {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    int x;
    for (x=0; x<numofbots; x++)
    {
        names[x] = kotht->getbotfile (x);
    }
    numf = kotht->getnumfights(); //Get the number of fights
    ln = kotht->getlength();			//Get the max length of fight
    xs = kotht->getxsize();
    ys = kotht->getysize();
    seed = kotht->getseed();
    if (!seed) seed = random();
    srandom (seed);

    teams[0] = 0;
    teams[1] = 1;

    batt = new battlearea ( (char *) names[numofbots-2].data(),
                            (char *) names[numofbots-1].data(),"","","","","","",numf,
                            ln,xs,ys,false,teams,true,kotht->getiffast());
    QObject::connect (batt, SIGNAL (battledone (int,int)), this,
                      SLOT (mankothtourney (int,int)));
    batt->show();
    kotht->hide();
    curmainbot = numofbots-2;
    cursecbot = numofbots-1;
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
void DroidBattles::mankothtourney (int wins1,int wins2)
{
    QString names[64];
    int numofbots = kotht->getnumofbots();
    int numf,ln,xs,ys,x;
    if (numofbots == 0)
    {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    for (x=0; x<numofbots; x++)
    {
        names[x] = kotht->getbotfile (x);
//		winmatches[x] = 0;
//		wingames[x] = 0;
    }

    results[curmainbot].secbot = cursecbot;
    results[curmainbot].mainbotwins = wins1;
    results[curmainbot].secbotwins = wins2;

    //If mainbot lost
    if (wins2 > wins1)
    {
        //mainbot in result array
        newlist[curmainbot+1] = names[curmainbot];
        //Change mainbot for new battle
        curmainbot--;
        if (curmainbot == -1)
            newlist[curmainbot+1] = names[cursecbot];

    }
    else
    {
        //secbot in result array
        newlist[curmainbot+1] = names[cursecbot];

        //Change mainbot for new battle
        cursecbot = curmainbot;
        curmainbot--;
        if (curmainbot == -1)
            newlist[curmainbot+1] = names[curmainbot+1];

    }


    if (curmainbot == -1)
    {
        QFile f ("currentKOTH.table");
        if (!f.open (QIODevice::WriteOnly))
        {
            //TODO: Add error mesage
            delete kotht;
            enabletourneys();
            return;
        }

        Q3TextStream s (&f);
        QString temp;

        s << "Numberofbot:" << " " << numofbots << "\n";
        for (x=0; x<numofbots; x++)
        {
            s << x+1 << ". " << newlist[x] << "\n";
        }
        s << "Numberoffights:" << " " << kotht->getnumfights() << "\n";
        s << "Length:" << " " << kotht->getlength() << "\n";
        s << "Xsize:" << " " << kotht->getxsize() << "\n";
        s << "Ysize:" << " " << kotht->getysize() << "\n";
        s << "Iffast:" << " " << kotht->getiffast() << "\n";
        f.close();

        QFile f2 ("Kothresults.html");
        if (!f2.open (QIODevice::WriteOnly))
        {
            //TODO: Add error mesage
            delete kotht;
            enabletourneys();
            return;
        }

        Q3TextStream s2 (&f2);

        s2 << "<HTML>\n";
        s2 << "<HEAD>\n";
        s2 << "<TITLE>KOTH results</TITLE>\n";
        s2 << "</HEAD>\n";
        s2 << "<BODY>\n";
        s2 << "<TABLE>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Pos</TD>\n";
        s2 << "<TD>Bot name</TD>\n";
        s2 << "</TR>\n";
        for (x=0; x<numofbots; x++)
        {
            s2 << "<TR>\n";
            s2 << "<TD>" << x+1 << "</TD>\n";
            s2 << "<TD>\n";
            temp = newlist[x];
            int pos = temp.findRev ("/",temp.length());
            temp = temp.right (temp.length()-pos-1);
            s2 << temp.data();
            s2 << "</TD>\n";
            s2 << "</TR>\n";
        }
        s2 << "</TABLE>\n";
        s2 << "<P>" << "Single match results: " << "</P>\n";
        s2 << "<TABLE>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Match nr</TD>\n";
        s2 << "<TD>Defender</TD>\n";
        s2 << "<TD>Attacker</TD>\n";
        s2 << "<TD>Results</TD>\n";
        s2 << "</TR>\n";
        for (x=numofbots-2; x>=0; x--)
        {
            s2 << "<TR>\n";
            s2 << "<TD>" << numofbots-x-1 << "</TD>\n";
            s2 << "<TD>\n";

            temp = names[x];
            int pos = temp.findRev ("/",temp.length());
            temp = temp.right (temp.length()-pos-1);
            s2 << temp.data();
            s2 << "</TD>\n";

            s2 << "<TD>\n";
            temp = names[results[x].secbot];
            pos = temp.findRev ("/",temp.length());
            temp = temp.right (temp.length()-pos-1);
            s2 << temp.data();
            s2 << "</TD>\n";

            s2 << "<TD> " << results[x].mainbotwins << " - " <<
            results[x].secbotwins << "</TD>\n";

            s2 << "</TR>\n";
        }
        s2 << "</TABLE>";
        s2 << "Random seed used: " << seed;
        s2 << "</BODY>";
        s2 << "</HTML>";

        f2.close();
        delete kotht;
        enabletourneys();
        QString tempdc = QDir::currentDirPath();
        tempdc += "/Kothresults.html";
        browser = new Docbrowser (tempdc);
    }
    else
    {
        numf = kotht->getnumfights(); //Get the number of fights
        ln = kotht->getlength();			//Get the max length of fight
        xs = kotht->getxsize();
        ys = kotht->getysize();

        teams[0] = 0;
        teams[1] = 1;

        batt = new battlearea ( (char *) names[curmainbot].data(),
                                (char *) names[cursecbot].data(),"","","","","","",numf,
                                ln,xs,ys,false,teams,true,kotht->getiffast());
        QObject::connect (batt, SIGNAL (battledone (int,int)), this,
                          SLOT (mankothtourney (int,int)));
        batt->show();
    }

}

void DroidBattles::cup()
{
    disabletourneys();
    cuptournament = new startcup();
    cuptournament->resize (300,570);
    cuptournament->show();
    QObject::connect (cuptournament,SIGNAL (okclicked()),this,
                      SLOT (startcupt()));
    QObject::connect (cuptournament,SIGNAL (cancelclicked()),this,
                      SLOT (stopcup()));
}

void DroidBattles::startcupt()
{
    resultcounter = 0;
    nextroundcount = 0;
    botsleft = cuptournament->getnumofbots();
    QString names[64];
    int numofbots = cuptournament->getnumofbots();
    int numf,ln,xs,ys;
    if (numofbots == 0)
    {
        delete cuptournament;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    int x;
    for (x=0; x<numofbots; x++)
    {
        names[x] = cuptournament->getbotfile (x);
        nextround[x] = x;
    }
    numf = cuptournament->getnumfights(); //Get the number of fights
    ln = cuptournament->getlength();			//Get the max length of fight
    xs = cuptournament->getxsize();
    ys = cuptournament->getysize();
    seed = cuptournament->getseed();
    if (!seed) seed = random();
    srandom (seed);

    teams[0] = 0;
    teams[1] = 1;

    curmainbot = 0;
    cursecbot = 1;

    batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),"",
                            "","","","","",numf,ln,xs,ys,false,teams,true,
                            cuptournament->getiffast());
    QObject::connect (batt, SIGNAL (battledone (int,int)), this,
                      SLOT (mancuptourney (int,int)));
    batt->show();
    cuptournament->hide();
}

void DroidBattles::stopcup()
{
    delete cuptournament;
    enabletourneys();
}

void DroidBattles::mancuptourney (int wins1,int wins2)
{
    QString names[64];
    int numofbots = cuptournament->getnumofbots();
    int numf,ln,xs,ys,x;
    if (numofbots == 0)
    {
        delete kotht;
        enabletourneys();
        return;
    }
    if (numofbots > 64)
        numofbots = 64;
    for (x=0; x<numofbots; x++)
    {
        names[x] = cuptournament->getbotfile (x);
//		winmatches[x] = 0;
//		wingames[x] = 0;
    }

    results[resultcounter].mainbot = nextround[curmainbot];
    results[resultcounter].secbot = nextround[cursecbot];
    results[resultcounter].mainbotwins = wins1;
    results[resultcounter].secbotwins = wins2;
    resultcounter++;

    if (wins1 >= wins2)
        nextround[nextroundcount] = nextround[curmainbot];
    else
        nextround[nextroundcount] = nextround[cursecbot];

    botsleft--;
    curmainbot += 2;
    cursecbot += 2;
    nextroundcount++;

    if (botsleft==2 || botsleft==4 || botsleft==8 || botsleft==16 ||
            botsleft==32)
    {
        curmainbot = 0;
        cursecbot = 1;
        nextroundcount = 0;
    }
    if (botsleft == 1)
    {
        //write results
        QFile f2 ("Cupresults.html");
        if (!f2.open (QIODevice::WriteOnly))
        {
            //TODO: Add error mesage
            delete cuptournament;
            enabletourneys();
            return;
        }

        Q3TextStream s2 (&f2);
        s2 << "<HTML>\n";
        s2 << "<HEAD>\n";
        s2 << "<TITLE>Cup results</TITLE>\n";
        s2 << "</HEAD>\n";
        s2 << "<BODY>\n";
        s2 << "<TABLE>\n";
        s2 << "<TR>\n";
        s2 << "<TD>Bot1</TD><TD>Bot2</TD><TD>Result</TD></TR>\n";

        int xxx = cuptournament->getnumofbots();
        resultcounter=0;
        int x;
        while (xxx > 1)
        {
            for (x = 0; x < xxx; x+=2)
            {
                s2 << "<TR><TD>" << names[results[resultcounter].mainbot]
                << "</TD><TD>" << names[results[resultcounter].secbot]
                << "</TD><TD>" << results[resultcounter].mainbotwins
                << " - " <<  results[resultcounter].secbotwins << "</TD></TR>\n";
                resultcounter++;
            }
            s2 << "<HR>\n";
            xxx /= 2;
        }
        s2 << "</TABLE>\n" << "Winner: " << names[nextround[0]] << "\n<BR>";
        s2 << "Random seed used: " << seed;
        s2 << "\n</BODY>\n</HTML>";
        f2.close();
        QString tempdc = QDir::currentDirPath();
        tempdc += "/Cupresults.html";
        browser = new Docbrowser (tempdc);
        delete cuptournament;
        enabletourneys();
        return;
    }
    numf = cuptournament->getnumfights(); //Get the number of fights
    ln = cuptournament->getlength();			//Get the max length of fight
    xs = cuptournament->getxsize();
    ys = cuptournament->getysize();

    teams[0] = 0;
    teams[1] = 1;

    batt = new battlearea ( (char *) names[nextround[curmainbot]].data(),
                            (char *) names[nextround[cursecbot]].data(),"","","","","","",numf,
                            ln,xs,ys,false,teams,true,cuptournament->getiffast());
    QObject::connect (batt, SIGNAL (battledone (int,int)), this,
                      SLOT (mancuptourney (int,int)));
    batt->show();

}

void DroidBattles::enabletourneys()
{
    menubuttons[5]->setEnabled (true);
    menubuttons[6]->setEnabled (true);
    menubuttons[7]->setEnabled (true);
}

void DroidBattles::disabletourneys()
{
    menubuttons[5]->setEnabled (false);
    menubuttons[6]->setEnabled (false);
    menubuttons[7]->setEnabled (false);
}

void DroidBattles::enablebattles()
{
    menubuttons[2]->setEnabled (true);
    menubuttons[3]->setEnabled (true);
    menubuttons[4]->setEnabled (true);
}

void DroidBattles::disablebattles()
{
    menubuttons[2]->setEnabled (false);
    menubuttons[3]->setEnabled (false);
    menubuttons[4]->setEnabled (false);
}
