/***************************************************************************
                          starttournament.cpp  -  description
                             -------------------
    begin                : Sat Aug 5 2000
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

#include "starttournament.h"
//Added by qt3to4:
#include <QLabel>
#include <QCloseEvent>

StartTournament::StartTournament()
{

//	int x;

    botfiles = new QListWidget (this);
    botfiles->setGeometry (10,75,270,170);

    press[0] = new QPushButton ("load",this);
    press[0]->setGeometry (0,0,80,40);
    press[1] = new QPushButton ("remove",this);
    press[1]->setGeometry (85,0,80,40);

    iffast = new QCheckBox ("Fast (nodelay) battle",this);
    iffast->setGeometry (20,50,170,20);

    QObject::connect (press[0],SIGNAL (clicked()),this,
                      SLOT (choosefile()));
    QObject::connect (press[1],SIGNAL (clicked()),this,
                      SLOT (dechoosefile()));

    readyb = new QPushButton (this);
    readyb->setText ("OK");
    readyb->setGeometry (100,500,80,40);
    cancelb = new QPushButton (this);
    cancelb->setText ("cancel");
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

    seedinfo = new QLabel ("Random seed used (0 for random): ",this);
    seedinfo->setGeometry (10,420,250,20);
    seed = new QLineEdit (this);
    seed->setGeometry (220,420,60,20);

}

StartTournament::~StartTournament()
{
}

int StartTournament::getnumofbots()
{
    return botfiles->count();
}

QString StartTournament::getbotfile (int x)
{
    return botfiles->item(x)->text();
}

/**
	* Load a .bot file
	*/
void StartTournament::choosefile()
{
    QString tempname = QFileDialog::getOpenFileName (this, tr("Select bot file"), QDir::homePath(), "*.bot");
//	int x;

    if (!tempname.isEmpty())
    {
        botfiles->addItem (tempname);
    }
}

/**
	* Remove a .bot file from list
	*/
void StartTournament::dechoosefile()
{
//	int x;
    delete botfiles->takeItem(botfiles->currentRow());
}

void StartTournament::ocl()
{
    emit okclicked();
}

void StartTournament::ccl()
{
    emit cancelclicked();
}

void StartTournament::closeEvent (QCloseEvent *e)
{
    e->ignore();
}

/**
	* The following functions returns settings
	*/

int StartTournament::getnumfights()
{
    QString s = wnumfights->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}

int StartTournament::getlength()
{
    QString s = length->text();
    if (s.length() == 0)
        return 3000;

    return s.toInt();
}

int StartTournament::getxsize()
{
    return (maxx->cleanText()).toInt();
}

int StartTournament::getysize()
{
    return (maxy->cleanText()).toInt();
}

bool StartTournament::getiffast()
{
    return iffast->isChecked();
}

int StartTournament::getseed()
{
    QString s = seed->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}
