/***************************************************************************
                          confedit.cpp  -  description
                             -------------------
    begin                : Tue Apr 18 2000
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

#include "confedit.h"
//Added by qt3to4:
#include <Q3TextStream>
#include <QLabel>

/**
	* Constructor: Init GUI
	*/
confedit::confedit()
{
    this->setMinimumSize (500,400);
    this->setMaximumSize (500,400);
    defaultbutton = new QPushButton ("Load default values" , this);
    openbutton = new QPushButton ("Open existing config" , this);
    savebutton = new QPushButton ("Save current config", this);
    closebutton = new QPushButton ("Close config editor",this);
    makecurrentbutton = new QPushButton ("Apply current config", this);
    helpbutton = new QPushButton ("HELP", this);

    defaultbutton->setGeometry (0,0,166,30);
    openbutton->setGeometry (167,0,166,30);
    savebutton->setGeometry (333,0,166,30);
    closebutton->setGeometry (0,30,166,30);
    makecurrentbutton->setGeometry (167,30,166,30);
    helpbutton->setGeometry (333,30,166,30);

    helpbutton->setEnabled (false);

    QObject::connect (defaultbutton, SIGNAL (clicked()), this,
                      SLOT (defaultc()));
    QObject::connect (openbutton, SIGNAL (clicked()), this,
                      SLOT (openc()));
    QObject::connect (savebutton, SIGNAL (clicked()), this,
                      SLOT (savec()));
    QObject::connect (closebutton, SIGNAL (clicked()), this,
                      SLOT (closec()));
    QObject::connect (makecurrentbutton, SIGNAL (clicked()), this,
                      SLOT (makecurrc()));
    QObject::connect (helpbutton, SIGNAL (clicked()), this,
                      SLOT (helpc()));

    valid = new QIntValidator (this);

    scroll = new Q3ScrollView (this);
    scroll->setGeometry (0,60,500,330);
    setarea = new QWidget();
    setarea->setGeometry (0,0,480,1400);
    scroll->addChild (setarea);

    maxdevl = new QLabel ("Maximum number of devices: ", setarea);
    maxdevl->setGeometry (10,10,190,15);
    maxdevv = new QSpinBox (1,32,1,setarea);
    maxdevv->setGeometry (200,7,50,20);

    maxcostl = new QLabel ("Maximum cost of bot: ", setarea);
    maxcostl->setGeometry (10,30,190,15);
    maxcostv = new QSpinBox (100, 65500, 100, setarea);
    maxcostv->setGeometry (190,27,60,20);

    maxraml = new QLabel ("Maximum amount of RAM: ", setarea);
    maxraml->setGeometry (10,60,190,15);
    maxramv = new QComboBox (setarea);
    maxramv->insertItem ("1k");
    maxramv->insertItem ("2k");
    maxramv->insertItem ("4k");
    maxramv->insertItem ("8k");
    maxramv->insertItem ("16k");
    maxramv->insertItem ("24k");
    maxramv->insertItem ("32k");
    maxramv->insertItem ("48k");
    maxramv->insertItem ("64k");

    QComboBox::Policy pol = QComboBox::InsertAtCurrent;

    ramcostl = new QLabel ("Cost of RAM: ",setarea);
    ramcostl->setGeometry (250,60,80,15);
    ramcostv = new QComboBox (true,setarea);
    ramcostv->setValidator (valid);
    ramcostv->setInsertionPolicy (pol);
    ramcostv->insertItem ("100");
    ramcostv->insertItem ("250");
    ramcostv->insertItem ("600");
    ramcostv->insertItem ("1500");
    ramcostv->insertItem ("4000");
    ramcostv->insertItem ("9000");
    ramcostv->insertItem ("18000");
    ramcostv->insertItem ("20000");
    ramcostv->insertItem ("25000");
    ramcostv->setMaxCount (10);
    ramcostv->move (0,0);
    ramcostv->adjustSize();
    ramcostv->move (330,57);

    maxramv->move (0,0);
    maxramv->adjustSize();
    maxramv->move (170,57);

    devicegroup[0] = new Q3GroupBox ("CPU", setarea);
    devicegroup[1] = new Q3GroupBox ("engine", setarea);
    devicegroup[2] = new Q3GroupBox ("steering",setarea);
    devicegroup[3] = new Q3GroupBox ("plasmagun",setarea);
    devicegroup[4] = new Q3GroupBox ("armor",setarea);
    devicegroup[5] = new Q3GroupBox ("scanner",setarea);
    devicegroup[6] = new Q3GroupBox ("fuel",setarea);
    devicegroup[7] = new Q3GroupBox ("chaff",setarea);
    devicegroup[8] = new Q3GroupBox ("turret",setarea);
    devicegroup[9] = new Q3GroupBox ("scanwarner",setarea);
    devicegroup[10] = new Q3GroupBox ("timedev",setarea);
    devicegroup[11] = new Q3GroupBox ("shield",setarea);
    devicegroup[12] = new Q3GroupBox ("repair",setarea);
    devicegroup[13] = new Q3GroupBox ("radio",setarea);
    devicegroup[14] = new Q3GroupBox ("chiller",setarea);
    devicegroup[15] = new Q3GroupBox ("cloaker",setarea);
    devicegroup[16] = new Q3GroupBox ("minelayer",setarea);
    devicegroup[17] = new Q3GroupBox ("missile",setarea);
    devicegroup[18] = new Q3GroupBox ("beam",setarea);
    devicegroup[19] = new Q3GroupBox ("AS-rocket",setarea);

    int x;
    for (x=0; x<numdev; x++)
    {
        devicesenabled[x] = new QCheckBox ("enabled",devicegroup[x]);
        devicesenabled[x]->setGeometry (10,20,100,15);
        costs[x] = new QLabel ("Cost of device: ", devicegroup[x]);
        costs[x]->setGeometry (10,40, 100,15);

        levelcosts[x] = new QComboBox (true,devicegroup[x]);
        levelcosts[x]->setInsertionPolicy (pol);
        levelcosts[x]->insertItem ("100");
        levelcosts[x]->insertItem ("200");
        levelcosts[x]->insertItem ("300");
        levelcosts[x]->insertItem ("400");
        levelcosts[x]->insertItem ("500");
        levelcosts[x]->setValidator (valid);
        levelcosts[x]->setGeometry (110,37,60,25);
        levelcosts[x]->setMaxCount (6);

        values[x] = new QLabel ("Values for dev: ", devicegroup[x]);
        values[x]->setGeometry (10,70,100,15);

        levelvalues[x] = new QComboBox (true,devicegroup[x]);
        levelvalues[x]->setInsertionPolicy (pol);
        levelvalues[x]->insertItem ("0");
        levelvalues[x]->insertItem ("0");
        levelvalues[x]->insertItem ("0");
        levelvalues[x]->insertItem ("0");
        levelvalues[x]->insertItem ("0");
        levelvalues[x]->setValidator (valid);
        levelvalues[x]->setGeometry (110,67,60,25);
        levelvalues[x]->setMaxCount (6);


        if (x < 10) devicegroup[x]->setGeometry (5,95+x*115,200,110);
        else
            devicegroup[x]->setGeometry (210,95+ (x-10) *115,200,110);

    }
    QString tempname = QDir::homeDirPath();
    tempname += "/droidbattles/current.cfg";
    openfile (tempname);
    show();
}

/**
	* Destructor, does nothing
	*/
confedit::~confedit()
{
}

/**
	* Sets the default values
	*/
void confedit::defaultc()
{
    QString tempname = returninstalldir();
    tempname += "/current.cfg";
    openfile (tempname);
}

/**
	* Opens existing config file and loads those values
	*/
void confedit::openc()
{
    QString tempname = Q3FileDialog::getOpenFileName (0,"*.cfg",this);
    openfile (tempname);
}
/**
	* Saves current setings to a config file
	*/
void confedit::savec()
{
    QString tempname = Q3FileDialog::getSaveFileName (0,"*.cfg",this);
    if (tempname.isEmpty())
    {
        return;
    }

    QFile f (tempname);
    if (!f.open (QIODevice::WriteOnly))
    {
        //TODO: Add error mesage
        return;
    }

    int x,y;

    Q3TextStream s (&f);
    s << "MAXDEVICES: " << maxdevv->text() << endl;
    s << "MAXCOSTS: " << maxcostv->text() << endl;
    s << "MAXRAM: " << maxramv->currentItem() << endl;
    s << "RAMCOSTS:";
    for (x=0; x<9; x++)
        s << " " << ramcostv->text (x);
    s << endl;
    for (x=0; x<numdev; x++)
    {
        s << "DEVICE: " << devicesenabled[x]->isChecked();
        for (y=0; y<5; y++)
        {
            s << " " << levelcosts[x]->text (y);
            s << " " << levelvalues[x]->text (y);
        }
        s << endl;
    }
    f.close();
}

/**
	* Closes this window
	*/
void confedit::closec()
{
    delete this;
}

/**
	* Saves curreent settings to homedir/droidbattles/current.cfg
	*/
void confedit::makecurrc()
{
    QString filename = QDir::homeDirPath();
    filename += "/droidbattles/current.cfg";
    QFile f (filename);
    if (!f.open (QIODevice::WriteOnly))
    {
        //TODO: add error message
        return;
    }

    int x,y;

    Q3TextStream s (&f);
    s << "MAXDEVICES: " << maxdevv->text() << endl;
    s << "MAXCOSTS: " << maxcostv->text() << endl;
    s << "MAXRAM: " << maxramv->currentItem() << endl;
    s << "RAMCOSTS:";
    for (x=0; x<9; x++)
        s << " " << ramcostv->text (x);
    s << endl;
    for (x=0; x<numdev; x++)
    {
        s << "DEVICE: " << devicesenabled[x]->isChecked();
        for (y=0; y<5; y++)
        {
            s << " " << levelcosts[x]->text (y);
            s << " " << levelvalues[x]->text (y);
        }
        s << endl;
    }
    f.close();
}

/**
	* TODO: load basic config help
	*/
void confedit::helpc()
{
}

void confedit::openfile (QString &tempname)
{
    if (tempname.isEmpty())
    {
        return;
    }
    QFile f (tempname);
    if (!f.open (QIODevice::ReadOnly))
    {
        //TODO: Add error message
        return;
    }

    int x,y;
    QString dummy;
    int i;
//	bool ch;
    Q3TextStream s (&f);


    s >> dummy;
    s >> i;
    maxdevv->setValue (i);
    s >> dummy;
    s >> i;
    maxcostv->setValue (i);
    s >> dummy;
    s >> i;
    maxramv->setCurrentItem (i);
    s >> dummy;
    for (x=0; x<9; x++)
    {
        s >> dummy;
        ramcostv->changeItem (dummy,x);
    }
    for (x=0; x<numdev; x++)
    {
        s >> dummy;
        s >> i;
        if (i == 1)
            devicesenabled[x]->setChecked (true);
        else
            devicesenabled[x]->setChecked (false);
        for (y=0; y<5; y++)
        {
            s >> dummy;
            levelcosts[x]->changeItem (dummy,y);
            s >> dummy;
            levelvalues[x]->changeItem (dummy,y);
        }
    }
}
