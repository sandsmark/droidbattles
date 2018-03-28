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
#include "pixbutton.h"
#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>
#include <QTextStream>

/**
	* Init GUI elements
	*/
KothTournament::KothTournament() :
    StartTournament("KOTH")
{
    loadlist = new PixButton("Load list", this);

    QObject::connect(loadlist, SIGNAL(clicked()), this,
                     SLOT(chooselist()));

    QGridLayout *l = qobject_cast<QGridLayout *>(layout());
    Q_ASSERT(l);
    l->addWidget(loadlist, 0, 0);
}

/**
	* Opens an existing file defining settings and
	* bots competeing
	*/
void KothTournament::chooselist()
{
    QSettings settings;

    QString filename = QFileDialog::getOpenFileName(this, tr("Select tournament table file"), settings.value("LastTablePath").toString(), "*.table");
    if (filename.isEmpty()) {
        return;
    }
    settings.setValue("LastTablePath", filename);

    int x;

    //Empty list of bots
    botfiles->clear();
    //Load new bots
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    QTextStream s(&f);

    QString temp;
    s >> temp;
    s >> temp;
    int numbots = temp.toInt();
    for (x = 0; x < numbots; x++) {
        s >> temp;
        s >> temp;
        botfiles->addItem(temp);
    }
    //numfights
    s >> temp;
    s >> temp;
    wnumfights->setValue(temp.toInt());
    //lengthfights
    s >> temp;
    s >> temp;
    length->setValue(temp.toInt());
    //Xsize
    s >> temp;
    s >> temp;
    maxx->setValue(temp.toInt());
    //Ysize
    s >> temp;
    s >> temp;
    maxy->setValue(temp.toInt());
    //Iffast
    s >> temp;
    s >> temp;
    iffast->setChecked(temp.toInt());
}
