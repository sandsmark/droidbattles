/***************************************************************************
                          startdeathbatt.cpp  -  description
                             -------------------
    begin                : Fri Jan 5 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#include "startdeathbatt.h"
//Added by qt3to4:
#include <QTextStream>

startdeathbatt::startdeathbatt()
{
    tnumfights->setText ("Number of frags:");
    loadfilesettings();
}

startdeathbatt::~startdeathbatt()
{
}

void startdeathbatt::loadfilesettings()
{
    QString temp = QDir::homePath();
    temp += "/droidbattles/deathbattle.save";
    QFile f (temp);
    if (f.exists() && f.open (QIODevice::ReadOnly))
    {
        QTextStream s (&f);
        for (int x=0; x<8; x++)
        {
            s >> botfiles[x];
            s >> temp;
            if (botfiles[x] == QString ("fff"))
                botfiles[x] = "";
            team[x]->setCurrentIndex (temp.toInt());
            shownames[x]->setText (botfiles[x]);
        }
        s >> temp;
        ifteams->setChecked (temp.toInt());
        s >> temp;
        wnumfights->setText (temp);
        s >> temp;
        length->setText (temp);
        s >> temp;
        maxx->setValue (temp.toInt());
        s >> temp;
        maxy->setValue (temp.toInt());
        f.close();
    }
}

void startdeathbatt::ocl()
{
    QString temp = QDir::homePath();
    temp += "/droidbattles/deathbattle.save";
    QFile f (temp);
    if (f.open (QIODevice::WriteOnly))
    {
        QTextStream s (&f);
        for (int x=0; x<8; x++)
        {
            if (botfiles[x] == QString (""))
                s << "fff" << " " << team[x]->currentIndex() << "\n";
            else
                s << botfiles[x] << " " << team[x]->currentIndex() << "\n";
        }
        s << ifteams->isChecked() << "\n";
        s << getnumfights() << "\n";
        s << getlength() << "\n";
        s << getxsize() << " " << getysize() << "\n";
        f.close();
    }
    emit okclicked();
}
