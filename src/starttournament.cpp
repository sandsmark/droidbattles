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

starttournament::starttournament()
{

//	int x;

    botfiles = new Q3ListBox (this);
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
    maxx = new QSpinBox (8192,65535,512,this);
    maxx->setGeometry (210,350,80,30);
    maxx->setValue (32768);

    maxyinfo = new QLabel ("The ysize of the battlearea: ",this);
    maxyinfo->setGeometry (10,380,200,20);
    maxy = new QSpinBox (8192,65535,512,this);
    maxy->setGeometry (210,380,80,30);
    maxy->setValue (32768);

    seedinfo = new QLabel ("Random seed used (0 for random): ",this);
    seedinfo->setGeometry (10,420,250,20);
    seed = new QLineEdit (this);
    seed->setGeometry (220,420,60,20);

}

starttournament::~starttournament()
{
}

int starttournament::getnumofbots()
{
    return botfiles->count();
}

const char* starttournament::getbotfile (int x)
{
    return botfiles->text (x);
}

/**
	* Load a .bot file
	*/
void starttournament::choosefile()
{
    QString tempname = Q3FileDialog::getOpenFileName (0,"*.bot",this);
//	int x;

    if (!tempname.isEmpty())
    {
        botfiles->insertItem (tempname);
    }
}

/**
	* Remove a .bot file from list
	*/
void starttournament::dechoosefile()
{
//	int x;
    botfiles->removeItem (botfiles->currentItem());

}

void starttournament::ocl()
{
    emit okclicked();
}

void starttournament::ccl()
{
    emit cancelclicked();
}

void starttournament::closeEvent (QCloseEvent *e)
{
    e->ignore();
}

/**
	* The following functions returns settings
	*/

int starttournament::getnumfights()
{
    QString s = wnumfights->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}

int starttournament::getlength()
{
    QString s = length->text();
    if (s.length() == 0)
        return 3000;

    return s.toInt();
}

int starttournament::getxsize()
{
    return (maxx->cleanText()).toInt();
}

int starttournament::getysize()
{
    return (maxy->cleanText()).toInt();
}

bool starttournament::getiffast()
{
    return iffast->isChecked();
}

int starttournament::getseed()
{
    QString s = seed->text();
    if (s.length() == 0)
        return 0;

    return s.toInt();
}
