/***************************************************************************
                          startsbatt.cpp  -  description
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

#include "startsbatt.h"
//Added by qt3to4:
#include <QResizeEvent>
#include <QTextStream>
#include <QLabel>
#include <QCloseEvent>

/**
	* init GUI, load file from last battle
	*/
StartsBatt::StartsBatt()
{
    setWindowFlags(Qt::Dialog);

    int x;
    for (x=0; x<8; x++)
    {
        botfiles[x] = "";
        shownames[x] = new QLabel (this);
        shownames[x]->setGeometry (10,50+x*25,230,20);
        shownames[x]->show();
        team[x] = new QComboBox (this);
        team[x]->setGeometry (255,50+x*25,40,20);
        team[x]->addItem ("1");
        team[x]->addItem ("2");
        team[x]->addItem ("3");
        team[x]->addItem ("4");
    }
    press[0] = new PixButton ("load", this);
    press[0]->setGeometry (0,0,80,40);
    press[1] = new PixButton ("remove", this);
    press[1]->setGeometry (85,0,80,40);

    ifteams = new QCheckBox ("Teams",this);
    ifteams->setGeometry (170,10,80,20);

    QObject::connect (press[0],SIGNAL (clicked()),this,
                      SLOT (choosefile()));
    QObject::connect (press[1],SIGNAL (clicked()),this,
                      SLOT (dechoosefile()));

    readyb = new PixButton ("OK", this);
    readyb->setGeometry (100,500,80,40);
    cancelb = new PixButton ("cancel", this);
    cancelb->setGeometry (200,500,80,40);

    QObject::connect (readyb,SIGNAL (clicked()),this,SLOT (ocl()));
    QObject::connect (cancelb,SIGNAL (clicked()),this,SLOT (ccl()));

    tnumfights = new QLabel ("Number of fights:",this);
    tnumfights->setGeometry (10,300,100,20);
    wnumfights = new QLineEdit (this);
    wnumfights->setGeometry (120,300,40,20);
    numfix = new QIntValidator (this);
    wnumfights->setValidator (numfix);

    lengthfight = new QLabel ("Max length of fight ( 50 ~ 1sec ):",this);
    lengthfight->setGeometry (10,320,200,20);
    length = new QLineEdit (this);
    length->setGeometry (200,320,60,20);

    maxxinfo = new QLabel ("The xsize of the battlearea: ",this);
    maxxinfo->setGeometry (10,350,200,20);
    maxx = new QSpinBox (this);
    maxx->setMinimum(8192);
    maxx->setMaximum(65535);
    maxx->setSingleStep(512);
    maxx->setGeometry (210,350,80,30);
    maxx->setValue (32768);

    maxyinfo = new QLabel ("The ysize of the battlearea: ",this);
    maxyinfo->setGeometry (10,380,200,20);
    maxy = new QSpinBox (this);
    maxy->setMinimum(8192);
    maxy->setMaximum(65535);
    maxy->setSingleStep(512);
    maxy->setGeometry (210,380,80,30);
    maxy->setValue (32768);

    setPixmap(PixmapHolder::getpm(PixmapHolder::MetalBackground));
//	setBackgroundPixmap( Pixmapholder::getpm( 3 ) );
    setMinimumSize (300,570);
    loadfilesettings();

}

void StartsBatt::resizeEvent (QResizeEvent*)
{
    for (int x=0; x<8; x++)
    {
        shownames[x]->resize (width()-70,20);
        team[x]->setGeometry (width()-45,50+x*25,40,20);
    }
}

void StartsBatt::loadfilesettings()
{
    QString temp = QDir::homePath();
    temp += "/droidbattles/singlebattle.save";
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

StartsBatt::~StartsBatt()
{
}

int StartsBatt::getnumofbots()
{
    return 0;
}

QString StartsBatt::getbotfile (int x)
{
    return botfiles[x];
}

/**
	* Load a botfile
	*/
void StartsBatt::choosefile()
{
    QString tempname = QFileDialog::getOpenFileName (this, tr("Select bot file"), QDir::homePath(), "*.bot");
    int x;

    for (x=0; x<8; x++)
    {
        if (botfiles[x].isEmpty())
            break;
    }
    if (!tempname.isEmpty() && x < 8)
    {
        shownames[x]->setText (tempname);
        botfiles[x] = tempname;
    }
}

void StartsBatt::dechoosefile()
{
    int x;

    for (x=0; x<8; x++)
    {
        shownames[x]->clear();
        botfiles[x] = "";
    }
}

/**
	* When OK is clicked, save current settings to file and emit signal
	*/
void StartsBatt::ocl()
{
// Save the current settings to file
    QString temp = QDir::homePath();
    temp += "/droidbattles/singlebattle.save";
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

void StartsBatt::ccl()
{
    emit cancelclicked();
}

void StartsBatt::closeEvent (QCloseEvent *e)
{
    e->ignore();
}

/**
	* The following functions returns the settings
	*/

int StartsBatt::getnumfights()
{
    QString s = wnumfights->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}

int StartsBatt::getlength()
{
    QString s = length->text();
    if (s.length() == 0)
        return 3000;

    return s.toInt();
}

int StartsBatt::getxsize()
{
    return (maxx->cleanText()).toInt();
}

int StartsBatt::getysize()
{
    return (maxy->cleanText()).toInt();
}

bool StartsBatt::getifteams()
{
    return ifteams->isChecked();
}

int StartsBatt::getbotteam (int bot)
{
    return team[bot]->currentIndex();
}
