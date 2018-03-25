/***************************************************************************
                          main.cpp  -  description
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

#ifndef MAIN_CPP
#define MAIN_CPP

#include <qapplication.h>
#include <qfont.h>

//If you want another look, change this include
#include "droidbattles.h"
#include "textmodefilemanip.h"
#include "textmodebattlearea.h"
#include <string.h>
#include <QDebug>
#include <QStyleFactory>

void startbattle (int argc, char *argv[])
{
    QString bots[8];
    int numbots = 0;
    int battletype = 0;
    bool teamfight = false;
    int teams[8];
    for (int i =0; i<8; i++)
    {
        teams[i] = 1;
        bots[i] = "";
    }
    int numfights = 1;
//	int randomseed = random( );
    int xsize = 32768;
    int ysize = 32768;
    int maxrounds = 6000;

    int curarg = 3;
    int tteam = 1;
    while (curarg < argc)
    {
        if (strcmp (argv[curarg] , "-bot") == 0)
        {
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -bot without following bot specification";
                return;
            }
            if (numbots >= 8)
            {
                qWarning() << " ERROR: To many -bot specifications";
                return;
            }
            bots[numbots] = argv[curarg+1];
            QFile f (bots[numbots]);
            if (!f.exists())
            {
                qWarning() << " ERROR: Botfile " << bots[numbots] << " not found";
                return;
            }
            curarg += 2;
            teams[numbots] = tteam;
            numbots++;
        }
        else if (strcmp (argv[curarg] , "-normal") == 0)
        {
            battletype = 0;
            curarg++;
        }
        else if (strcmp (argv[curarg] , "-survival") == 0)
        {
            battletype = 1;
            curarg++;
        }
        else if (strcmp (argv[curarg] , "-deathmatch") == 0)
        {
            battletype = 2;
            curarg++;
        }
        else if (strcmp (argv[curarg] , "-team") == 0)
        {
            teamfight = true;
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -team without following team specification";
                return;
            }
            int temp = atoi (argv[curarg+1]);
            if (temp < 1 || temp > 4)
            {
                qWarning() << " ERROR: -team followed by invalid specification";
                return;
            }
            tteam = temp;
            curarg += 2;
        }
        else if (strcmp (argv[curarg] , "-xsize") == 0)
        {
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -xsize without following size specification";
                return;
            }
            int temp = atoi (argv[curarg+1]);
            if (temp < 8192 || temp > 65535)
            {
                qWarning() << " ERROR: -xsize followed by invalid specification";
                return;
            }
            xsize = temp;
            curarg += 2;
        }
        else if (strcmp (argv[curarg] , "-ysize") == 0)
        {
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -ysize without following team specification";
                return;
            }
            int temp = atoi (argv[curarg+1]);
            if (temp < 8192 || temp > 65535)
            {
                qWarning() << " ERROR: -ysize followed by invalid specification";
                return;
            }
            ysize = temp;
            curarg += 2;
        }
        else if (strcmp (argv[curarg] , "-numfights") == 0)
        {
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -numfights without following specification";
                return;
            }
            int temp = atoi (argv[curarg+1]);
            if (temp < 1)
            {
                qWarning() << " ERROR: -numfights followed by invalid specification";
                return;
            }
            numfights = temp;
            curarg += 2;
        }
        else if (strcmp (argv[curarg] , "-maxrounds") == 0)
        {
            if (argc < curarg+2)
            {
                qWarning() << " ERROR: -maxrounds without following specification";
                return;
            }
            int temp = atoi (argv[curarg+1]);
            if (temp < 100)
            {
                qWarning() << " ERROR: -maxrounds followed by invalid specification";
                return;
            }
            maxrounds = temp;
            curarg += 2;
        }
    }
    if (numbots > 1)
    {
        TextmodeBattleArea *area = new TextmodeBattleArea (bots[0] ,bots[1],
                bots[2], bots[3], bots[4], bots[5], bots[6], bots[7], numfights, maxrounds,
                xsize,ysize,teamfight,teams,false,battletype);
        while (true)
        {
            if (area->execround() == 3)
                break;
        }
    }
    else
        qWarning() << " ERROR: Not enough bots specified";
}

int main (int argc, char *argv[])
{
    bool useGUI = true;
    if (argc > 1) {
        if (strcmp (argv[1] , "-textmode") == 0)
            useGUI = false;
    }
//    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling, false);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
//    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
//    qputenv("QT_SCALE_FACTOR", "2");

    if (useGUI)
    {
        QApplication a (argc, argv);
        a.setApplicationName("droidbattles");
        a.setOrganizationName("martin");

        QApplication::setStyle(QStyleFactory::create("Fusion"));

//        a.setStyle( new QWindowsStyle );
//        a.setFont (QFont ("helvetica", 8));
        QFont font(a.font());
        font.setPixelSize(12);
        a.setFont(font);
        DroidBattles *droidbattles=new DroidBattles();

        droidbattles->show();
        return a.exec();  //Enter event-loop
    } else {
        QCoreApplication a (argc, argv);
        a.setApplicationName("droidbattles");
        a.setOrganizationName("martin");

        if (strcmp (argv[2] , "-assemble") == 0)
        {
            if (argc >= 4)
                TextModeFileManip::assemble (argv[3]);
        }
        else if (strcmp (argv[2] , "-check") == 0)
        {
            if (argc >= 4)
                TextModeFileManip::checkConfig (argv[3]);
        }
        else if (strcmp (argv[2] , "-loadconfig") == 0)
        {
            if (argc >= 4)
                TextModeFileManip::loadConfig (argv[3]);
        }
        else if (strcmp (argv[2] , "-battle") == 0)
        {
            startbattle (argc,argv);
        }
    }
    return 0;
}




#endif
