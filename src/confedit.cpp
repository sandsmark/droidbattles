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
#include <QTextStream>
#include <QLabel>
#include <QDebug>

/**
	* Constructor: Init GUI
	*/
ConfEdit::ConfEdit()
{
    setAttribute(Qt::WA_DeleteOnClose);

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
    connect(closebutton, &QPushButton::clicked, this, &ConfEdit::close);
    QObject::connect (makecurrentbutton, SIGNAL (clicked()), this,
                      SLOT (makecurrc()));
    QObject::connect (helpbutton, SIGNAL (clicked()), this,
                      SLOT (helpc()));

    valid = new QIntValidator (this);

    scroll = new QScrollArea (this);
    scroll->setGeometry (0,60,500,330);
    setarea = new QWidget();
    setarea->setGeometry (0,0,480,1400);
    scroll->setWidget(setarea);

    maxdevl = new QLabel ("Maximum number of devices: ", setarea);
    maxdevl->setGeometry (10,10,190,15);
    maxdevv = new QSpinBox (setarea);
    maxdevv->setMinimum(1);
    maxdevv->setMaximum(32);
    maxdevv->setSingleStep(1);
    maxdevv->setGeometry (200,7,50,20);

    maxcostl = new QLabel ("Maximum cost of bot: ", setarea);
    maxcostl->setGeometry (10,30,190,15);
    maxcostv = new QSpinBox (setarea);
    maxcostv->setMinimum(100);
    maxcostv->setMaximum(65500);
    maxcostv->setSingleStep(100);
    maxcostv->setGeometry (190,27,60,20);

    maxraml = new QLabel ("Maximum amount of RAM: ", setarea);
    maxraml->setGeometry (10,60,190,15);
    maxramv = new QComboBox (setarea);
    maxramv->addItem ("1k");
    maxramv->addItem ("2k");
    maxramv->addItem ("4k");
    maxramv->addItem ("8k");
    maxramv->addItem ("16k");
    maxramv->addItem ("24k");
    maxramv->addItem ("32k");
    maxramv->addItem ("48k");
    maxramv->addItem ("64k");

    QComboBox::InsertPolicy pol = QComboBox::InsertAtCurrent;

    ramcostl = new QLabel ("Cost of RAM: ",setarea);
    ramcostl->setGeometry (250,60,80,15);
    ramcostv = new QComboBox (setarea);
    ramcostv->setEditable(true);
    ramcostv->setValidator (valid);
    ramcostv->setInsertPolicy (pol);
    ramcostv->addItem ("100");
    ramcostv->addItem ("250");
    ramcostv->addItem ("600");
    ramcostv->addItem ("1500");
    ramcostv->addItem ("4000");
    ramcostv->addItem ("9000");
    ramcostv->addItem ("18000");
    ramcostv->addItem ("20000");
    ramcostv->addItem ("25000");
    ramcostv->setMaxCount (10);
    ramcostv->move (0,0);
    ramcostv->adjustSize();
    ramcostv->move (330,57);

    maxramv->move (0,0);
    maxramv->adjustSize();
    maxramv->move (170,57);

    devicegroup[0] = new QGroupBox ("CPU", setarea);
    devicegroup[1] = new QGroupBox ("engine", setarea);
    devicegroup[2] = new QGroupBox ("steering",setarea);
    devicegroup[3] = new QGroupBox ("plasmagun",setarea);
    devicegroup[4] = new QGroupBox ("armor",setarea);
    devicegroup[5] = new QGroupBox ("scanner",setarea);
    devicegroup[6] = new QGroupBox ("fuel",setarea);
    devicegroup[7] = new QGroupBox ("chaff",setarea);
    devicegroup[8] = new QGroupBox ("turret",setarea);
    devicegroup[9] = new QGroupBox ("scanwarner",setarea);
    devicegroup[10] = new QGroupBox ("timedev",setarea);
    devicegroup[11] = new QGroupBox ("shield",setarea);
    devicegroup[12] = new QGroupBox ("repair",setarea);
    devicegroup[13] = new QGroupBox ("radio",setarea);
    devicegroup[14] = new QGroupBox ("chiller",setarea);
    devicegroup[15] = new QGroupBox ("cloaker",setarea);
    devicegroup[16] = new QGroupBox ("minelayer",setarea);
    devicegroup[17] = new QGroupBox ("missile",setarea);
    devicegroup[18] = new QGroupBox ("beam",setarea);
    devicegroup[19] = new QGroupBox ("AS-rocket",setarea);

    int x;
    for (x=0; x<numdev; x++)
    {
        devicesenabled[x] = new QCheckBox ("enabled",devicegroup[x]);
        devicesenabled[x]->setGeometry (10,20,100,15);
        costs[x] = new QLabel ("Cost of device: ", devicegroup[x]);
        costs[x]->setGeometry (10,40, 100,15);

        levelcosts[x] = new QComboBox (devicegroup[x]);
        levelcosts[x]->setEditable(true);
        levelcosts[x]->setInsertPolicy (pol);
        levelcosts[x]->addItem ("100");
        levelcosts[x]->addItem ("200");
        levelcosts[x]->addItem ("300");
        levelcosts[x]->addItem ("400");
        levelcosts[x]->addItem ("500");
        levelcosts[x]->setValidator (valid);
        levelcosts[x]->setGeometry (110,37,60,25);
        levelcosts[x]->setMaxCount (6);

        values[x] = new QLabel ("Values for dev: ", devicegroup[x]);
        values[x]->setGeometry (10,70,100,15);

        levelvalues[x] = new QComboBox (devicegroup[x]);
        levelvalues[x]->setEditable(true);
        levelvalues[x]->setInsertPolicy (pol);
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->setValidator (valid);
        levelvalues[x]->setGeometry (110,67,60,25);
        levelvalues[x]->setMaxCount (6);


        if (x < 10) devicegroup[x]->setGeometry (5,95+x*115,200,110);
        else
            devicegroup[x]->setGeometry (210,95+ (x-10) *115,200,110);

    }
    QString tempname = QDir::homePath();
    tempname += "/droidbattles/current.cfg";
    openfile (tempname);
    show();
}

/**
	* Destructor, does nothing
	*/
ConfEdit::~ConfEdit()
{
}

/**
	* Sets the default values
	*/
void ConfEdit::defaultc()
{
    QString tempname = returninstalldir();
    tempname += "misc/current.cfg";
    qDebug() << tempname;
    openfile (tempname);
}

/**
	* Opens existing config file and loads those values
	*/
void ConfEdit::openc()
{
    QString tempname = QFileDialog::getOpenFileName (this, tr("Select config file"), QDir::homePath(), "*.cfg");
    openfile (tempname);
}
/**
	* Saves current setings to a config file
	*/
void ConfEdit::savec()
{
    QString tempname = QFileDialog::getSaveFileName (this, tr("Save config file"), QDir::homePath(), "*.cfg");
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

    QTextStream s (&f);
    s << "MAXDEVICES: " << maxdevv->cleanText() << endl;
    s << "MAXCOSTS: " << maxcostv->cleanText() << endl;
    s << "MAXRAM: " << maxramv->currentIndex() << endl;
    s << "RAMCOSTS:";
    for (x=0; x<9; x++)
        s << " " << ramcostv->itemText(x);
    s << endl;
    for (x=0; x<numdev; x++)
    {
        s << "DEVICE: " << devicesenabled[x]->isChecked();
        for (y=0; y<5; y++)
        {
            s << " " << levelcosts[x]->itemText(y);
            s << " " << levelvalues[x]->itemText(y);
        }
        s << endl;
    }
    f.close();
}

/**
	* Saves curreent settings to homedir/droidbattles/current.cfg
	*/
void ConfEdit::makecurrc()
{
    QString filename = QDir::homePath();
    filename += "/droidbattles/current.cfg";
    QFile f (filename);
    if (!f.open (QIODevice::WriteOnly))
    {
        //TODO: add error message
        return;
    }

    int x,y;

    QTextStream s (&f);
    s << "MAXDEVICES: " << maxdevv->cleanText() << endl;
    s << "MAXCOSTS: " << maxcostv->cleanText() << endl;
    s << "MAXRAM: " << maxramv->currentText() << endl;
    s << "RAMCOSTS:";
    for (x=0; x<9; x++)
        s << " " << ramcostv->itemText(x);
    s << endl;
    for (x=0; x<numdev; x++)
    {
        s << "DEVICE: " << devicesenabled[x]->isChecked();
        for (y=0; y<5; y++)
        {
            s << " " << levelcosts[x]->itemText(y);
            s << " " << levelvalues[x]->itemText(y);
        }
        s << endl;
    }
    f.close();
}

/**
	* TODO: load basic config help
	*/
void ConfEdit::helpc()
{
}

void ConfEdit::openfile (QString &tempname)
{
    if (tempname.isEmpty())
    {
        return;
    }
    QFile f (tempname);
    if (!f.open (QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open" << tempname;
        //TODO: Add error message
        return;
    }

    int x,y;
    QString dummy;
    int i;
//	bool ch;
    QTextStream s (&f);


    s >> dummy;
    s >> i;
    maxdevv->setValue (i);
    s >> dummy;
    s >> i;
    maxcostv->setValue (i);
    s >> dummy;
    s >> i;
    maxramv->setCurrentIndex(i);
    s >> dummy;
    for (x=0; x<9; x++)
    {
        s >> dummy;
        ramcostv->setItemText(x, dummy);
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
            levelcosts[x]->setItemText (y, dummy);
            s >> dummy;
            levelvalues[x]->setItemText (y, dummy);
        }
    }
}
