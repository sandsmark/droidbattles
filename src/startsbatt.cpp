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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

/**
	* init GUI, load file from last battle
	*/
StartsBatt::StartsBatt(const QString &configFileName) :
    m_configFileName(configFileName)
{
    QVBoxLayout *l = new QVBoxLayout;
    setLayout(l);

    setWindowFlags(Qt::Dialog);

    QHBoxLayout *topButtonsLayout = new QHBoxLayout;
    press[0] = new PixButton ("Add", this);
    topButtonsLayout->addWidget(press[0]);
    press[1] = new PixButton ("Clear", this);
    topButtonsLayout->addWidget(press[1]);
    l->addLayout(topButtonsLayout);

    int x;
    for (x=0; x<8; x++)
    {
        QHBoxLayout *pl = new QHBoxLayout;

        botfiles[x] = "";
        shownames[x] = new QLabel (this);
        shownames[x]->show();
        pl->addWidget(shownames[x]);
        team[x] = new QComboBox (this);
        pl->addWidget(team[x]);
        team[x]->addItem ("1");
        team[x]->addItem ("2");
        team[x]->addItem ("3");
        team[x]->addItem ("4");

        l->addLayout(pl);
    }

    ifteams = new QCheckBox ("Teams",this);
    l->addWidget(ifteams);

    QObject::connect (press[0],SIGNAL (clicked()),this,
                      SLOT (choosefile()));
    QObject::connect (press[1],SIGNAL (clicked()),this,
                      SLOT (dechoosefile()));

    QGridLayout *optionsLayout = new QGridLayout;
    l->addLayout(optionsLayout);

    tnumfights = new QLabel ("Number of fights:",this);
    optionsLayout->addWidget(tnumfights, 0, 0);
    wnumfights = new QLineEdit (this);
    optionsLayout->addWidget(wnumfights, 0, 1);
    numfix = new QIntValidator (this);
    wnumfights->setValidator (numfix);

    lengthfight = new QLabel ("Max length of fight ( 50 ~ 1sec ):",this);
    optionsLayout->addWidget(lengthfight, 1, 0);
    length = new QLineEdit (this);
    optionsLayout->addWidget(length, 1, 1);

    maxxinfo = new QLabel ("The xsize of the battlearea: ",this);
    optionsLayout->addWidget(maxxinfo, 2, 0);
    maxx = new QSpinBox (this);
    maxx->setMinimum(8192);
    maxx->setMaximum(65535);
    maxx->setSingleStep(512);
    maxx->setValue (32768);
    optionsLayout->addWidget(maxx, 2, 1);

    maxyinfo = new QLabel ("The ysize of the battlearea: ",this);
    optionsLayout->addWidget(maxyinfo, 3, 0);
    maxy = new QSpinBox (this);
    maxy->setMinimum(8192);
    maxy->setMaximum(65535);
    maxy->setSingleStep(512);
    optionsLayout->addWidget(maxy, 3, 1);
    maxy->setValue (32768);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    l->addLayout(bottomLayout);
    readyb = new PixButton ("OK", this);
    bottomLayout->addWidget(readyb);
    cancelb = new PixButton ("cancel", this);
    bottomLayout->addWidget(cancelb);

    QObject::connect (readyb,SIGNAL (clicked()),this,SLOT (ocl()));
    QObject::connect (cancelb,SIGNAL (clicked()),this,SLOT (ccl()));

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(PixmapHolder::getpm (PixmapHolder::MetalBackground)));
    palette.setColor(foregroundRole(), Qt::white);
    setPalette(palette);

    setMinimumSize (300,570);
    loadfilesettings();

}

void StartsBatt::loadfilesettings()
{
    QString temp = QDir::homePath();
    temp += "/droidbattles/" + m_configFileName;
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
            shownames[x]->setText (QFileInfo(botfiles[x]).baseName());
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
    temp += "/droidbattles/" + m_configFileName;
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
