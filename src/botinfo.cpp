/***************************************************************************
                          botinfo.cpp  -  description
                             -------------------
    begin                : Tue Apr 4 2000
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

#include "botinfo.h"
//Added by qt3to4:
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>

/**
	* Constructor, create all GUI elements
	*/
BotInfo::BotInfo (const QString &botname, ScreenObject *rb, int armor, QWidget *parent) : QWidget (parent)
{
    QHBoxLayout *l = new QHBoxLayout;
    setLayout(l);

    bot = rb;
    if (!botname.isEmpty()) {
        int pos = botname.lastIndexOf("/");
        QString temp = botname.right (botname.length()-pos-1);
        botnam = new QLabel (temp,this);
        l->addWidget(botnam);

        armormsg = new QLabel ("A:",this);
        l->addWidget(armormsg);

        armorlevel = new QProgressBar(this);
        armorlevel->setMaximum(armor);
        l->addWidget(armorlevel);
        armorlevel->setValue(armor);


        heatmsg = new QLabel ("H:",this);
        l->addWidget(heatmsg);

        heatlevel = new QProgressBar(this);
        heatlevel->setMaximum(850);
        l->addWidget(heatlevel);
        heatlevel->setValue(0);

        msgmsg = new QLabel ("F: ",this);
        l->addWidget(msgmsg);

        message = new QLabel ("M: ",this);
        l->addWidget(message);

        ifscanner = new QCheckBox ("Show device gfx",this);
        l->addWidget(ifscanner);
        ifscanner->setChecked (true);
        QObject::connect (ifscanner, SIGNAL (toggled (bool)), this,
                          SLOT (statch (bool)));

        showgfx = new QLabel (this);
        l->addWidget(showgfx);

        showgfx->setPixmap(rb->getgfx().copy(0, 0, rb->getgfx().height(), rb->getgfx().height()));
    }
    show();
}

/**
	* Destructor, does nothing
	*/
BotInfo::~BotInfo()
{
}

/**
	* Updates armor progressbar
	* Connected to armorchanged signal that the bot emits
	*/
void BotInfo::armorupdated (int x)
{
    armorlevel->reset();
    armorlevel->setValue(x);
}

/**
	* emits signal that makes the bots show/not show device gfx
	*/
void BotInfo::statch (bool x)
{
    emit (changeinset (x));
}

/**
	* Updates fuel value
	*/
void BotInfo::updatefuel (int x,int y)
{
    QString temp;
    temp.setNum (x);
    QString t2 = "F: ";
    t2 += temp;
    msgmsg->setText (t2);
    heatlevel->reset();
    heatlevel->setValue(y);
}

/**
	* Shows new message
	*/
void BotInfo::newmessage (char *msg)
{
    QString temp;
    temp = "M : ";
    temp += msg;
    message->setText (temp);
}
