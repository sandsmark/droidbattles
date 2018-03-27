/***************************************************************************
                          kothtournament.cpp  -  description
                             -------------------
    begin                : Thu Nov 2 2000
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

#include "kothtournament.h"
//Added by qt3to4:
#include <QTextStream>
#include <QLabel>
#include <QCloseEvent>
#include <QSettings>
#include <QGridLayout>

/**
	* Init GUI elements
	*/
KothTournament::KothTournament()
{
    botfiles = new QListWidget (this);
//    botfiles->setGeometry (10,75,270,170);

    press[0] = new PixButton ("load", this);

    press[1] = new PixButton ("remove", this);

    loadlist = new PixButton ("load list", this);

    iffast = new QCheckBox ("Fast (nodelay) battle",this);

    QObject::connect (press[0],SIGNAL (clicked()),this,
                      SLOT (choosefile()));
    QObject::connect (press[1],SIGNAL (clicked()),this,
                      SLOT (dechoosefile()));
    QObject::connect (loadlist,SIGNAL (clicked()),this,
                      SLOT (chooselist()));

    readyb = new PixButton ("OK", this);
    cancelb = new PixButton ("cancel", this);

    QObject::connect (readyb,SIGNAL (clicked()),this,SLOT (ocl()));
    QObject::connect (cancelb,SIGNAL (clicked()),this,SLOT (ccl()));

    tnumfights = new QLabel ("Number of fights:",this);
    wnumfights = new QSpinBox (this);
    wnumfights->setMinimum(1);

    lengthfight = new QLabel ("Max length of fight (approximately 50 ticks per 1 sec):",this);

    length = new QSpinBox (this);
    length->setMinimum(50);

    maxxinfo = new QLabel ("The xsize of the battlearea: ",this);
    maxx = new QSpinBox (this);
    maxx->setMinimum(8192);
    maxx->setMaximum(65535);
    maxx->setSingleStep(512);
    maxx->setValue (32768);

    maxyinfo = new QLabel ("The ysize of the battlearea: ",this);
    maxy = new QSpinBox (this);
    maxy->setMinimum(8192);
    maxy->setMaximum(65535);
    maxy->setSingleStep(512);
    maxy->setValue (32768);

    seedinfo = new QLabel ("Random seed used (0 for random): ",this);
    seed = new QLineEdit (this);

    QGridLayout *l = new QGridLayout;
    l->addWidget(press[0], 0, 0);
    l->addWidget(press[1], 0, 1);
    l->addWidget(loadlist, 0, 2);

    l->addWidget(botfiles, 1, 0, 1, 3);


    l->addWidget(iffast, 2, 0);

    l->addWidget(tnumfights, 3, 0);
    l->addWidget(wnumfights, 3, 2);

    l->addWidget(lengthfight, 4, 0);
    l->addWidget(length, 4, 2);

    l->addWidget(maxxinfo, 5, 0);
    l->addWidget(maxx, 5, 2);

    l->addWidget(maxyinfo, 6, 0);
    l->addWidget(maxy, 6, 2);

    l->addWidget(seedinfo, 7, 0);
    l->addWidget(seed, 7, 2);

    l->addWidget(readyb, 8, 1);
    l->addWidget(cancelb, 8, 2);

    setLayout(l);
}

KothTournament::~KothTournament()
{
}

int KothTournament::getnumofbots()
{
    return botfiles->count();
}

/**
	* Return the dir for bot x
	*/
QString KothTournament::getbotfile (int x)
{
    return botfiles->item(x)->text();
}

/**
	* Chooses one file on the HD
	*/
void KothTournament::choosefile()
{
    QSettings settings;
    QString filename = QFileDialog::getOpenFileName (this, tr("Select bot file"), settings.value("LastBotPath").toString(), "*.bot");
    if (filename.isEmpty()) {
        return;
    }
    settings.setValue("LastBotPath", filename);

    botfiles->addItem(filename);
}

/**
	* Removes one bot in the list
	*/
void KothTournament::dechoosefile()
{
    delete botfiles->takeItem(botfiles->currentRow());
}

void KothTournament::ocl()
{
    emit okclicked();
}

void KothTournament::ccl()
{
    emit cancelclicked();
}

/**
	* Don't close if the "X" is clicked
	*/
void KothTournament::closeEvent (QCloseEvent *e)
{
    e->ignore();
}

/**
	* The following functions returns the settings
	*/
int KothTournament::getnumfights()
{
    QString s = wnumfights->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}

int KothTournament::getlength()
{
    return length->value();
}

int KothTournament::getxsize()
{
    return (maxx->cleanText()).toInt();
}

int KothTournament::getysize()
{
    return (maxy->cleanText()).toInt();
}

bool KothTournament::getiffast()
{
    return iffast->isChecked();
}

/**
	* Opens an existing file defining settings and
	* bots competeing
	*/
void KothTournament::chooselist()
{
    QSettings settings;

    QString filename = QFileDialog::getOpenFileName (this, tr("Select tournament table file"), settings.value("LastTablePath").toString(), "*.table");
    if (filename.isEmpty()) {
        return;
    }
    settings.setValue("LastTablePath", filename);

    int x;

    //Empty list of bots
    botfiles->clear();
    //Load new bots
    QFile f (filename);
    f.open (QIODevice::ReadOnly);
    QTextStream s (&f);

    QString temp;
    s >> temp;
    s >> temp;
    int numbots = temp.toInt();
    for (x=0; x<numbots; x++)
    {
        s >> temp;
        s >> temp;
        botfiles->addItem (temp);
    }
    //numfights
    s >> temp;
    s >> temp;
    wnumfights->setValue( temp.toInt());
    //lengthfights
    s >> temp;
    s >> temp;
    length->setValue (temp.toInt());
    //Xsize
    s >> temp;
    s >> temp;
    maxx->setValue (temp.toInt());
    //Ysize
    s >> temp;
    s >> temp;
    maxy->setValue (temp.toInt());
    //Iffast
    s >> temp;
    s >> temp;
    iffast->setChecked (temp.toInt());
}

/**
	* Returns the random seed
	*/
int KothTournament::getseed()
{
    QString s = seed->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}
