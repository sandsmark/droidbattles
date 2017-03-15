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

/**
	* Init GUI elements
	*/
KothTournament::KothTournament()
{

//	int x;

    botfiles = new QListWidget (this);
    botfiles->setGeometry (10,75,270,170);

    press[0] = new PixButton ("load",1,this);
    press[0]->setGeometry (0,0,80,40);
    press[1] = new PixButton ("remove",1,this);
    press[1]->setGeometry (85,0,80,40);
    loadlist = new PixButton ("load list",1,this);
    loadlist->setGeometry (170,0,80,40);

    iffast = new QCheckBox ("Fast (nodelay) battle",this);
    iffast->setGeometry (20,50,170,20);

    QObject::connect (press[0],SIGNAL (clicked()),this,
                      SLOT (choosefile()));
    QObject::connect (press[1],SIGNAL (clicked()),this,
                      SLOT (dechoosefile()));
    QObject::connect (loadlist,SIGNAL (clicked()),this,
                      SLOT (chooselist()));

    readyb = new PixButton ("OK",1,this);
    readyb->setGeometry (100,500,80,40);
    cancelb = new PixButton ("cancel",1,this);
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

//	setBackgroundPixmap( Pixmapholder::getpm( 3 ) );
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
    QString tempname = QFileDialog::getOpenFileName (this, tr("Select bot file"), QDir::homePath(), "*.bot");
//	int x;

    if (!tempname.isEmpty())
    {
        botfiles->addItem(tempname);
    }
}

/**
	* Removes one bot in the list
	*/
void KothTournament::dechoosefile()
{
//	int x;
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
    QString s = length->text();
    if (s.length() == 0)
        return 3000;

    return s.toInt();
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
    QString tempname = QFileDialog::getOpenFileName (this, tr("Select tournament table file"), QDir::homePath(), "*.table");
    int x;

    if (!tempname.isEmpty())
    {
        //Empty list of bots
        botfiles->clear();
        //Load new bots
        QFile f (tempname);
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
        wnumfights->setText (temp);
        //lengthfights
        s >> temp;
        s >> temp;
        length->setText (temp);
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
