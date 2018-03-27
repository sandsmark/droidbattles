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
#include <QFileInfo>
#include <QGridLayout>

/**
    * Constructor, create all GUI elements
    */
BotInfo::BotInfo (const QString &botname, ScreenObject *rb, int armor)
{
    bot = rb;
    if (botname.isEmpty()) {
        botnam.setVisible(false);
        armormsg.setVisible(false);
        armorlevel.setVisible(false);
        heatmsg.setVisible(false);
        heatlevel.setVisible(false);
        msgmsg.setVisible(false);
        message.setVisible(false);
        ifscanner.setVisible(false);
        showgfx.setVisible(false);
        return;
    }

    botnam.setText(QFileInfo(botname).baseName());

    armormsg.setText("A:");

    armorlevel.setMaximum(armor);
    armorlevel.setValue(armor);


    heatmsg.setText("H:");

    heatlevel.setMaximum(850);
    heatlevel.setValue(0);

    msgmsg.setText("F: ");

    message.setText("M: ");

    ifscanner.setText("Show device gfx");
    ifscanner.setChecked (true);
    connect (&ifscanner, &QAbstractButton::toggled, this, &BotInfo::statch);

    showgfx.setPixmap(rb->getgfx().copy(0, 0, rb->getgfx().height(), rb->getgfx().height()));
}

/**
    * Destructor, does nothing
    */
BotInfo::~BotInfo()
{
}

BotInfo *BotInfo::addBotInfo(QGridLayout *layout, int index, const QString &name, ScreenObject *screenObject)
{
    BotInfo *botInfo = new BotInfo(name, screenObject, screenObject->armorval);
    botInfo->setParent(layout);

    layout->addWidget(&botInfo->botnam, index, 0);
    layout->addWidget(&botInfo->armormsg, index, 1);
    layout->addWidget(&botInfo->armorlevel, index, 2);
    layout->addWidget(&botInfo->heatmsg, index, 3);
    layout->addWidget(&botInfo->heatlevel, index, 4);
    layout->addWidget(&botInfo->msgmsg, index, 5);
    layout->addWidget(&botInfo->message, index, 6);
    layout->addWidget(&botInfo->ifscanner, index, 7);
    layout->addWidget(&botInfo->showgfx, index, 8);

    return botInfo;
}

/**
    * Updates armor progressbar
    * Connected to armorchanged signal that the bot emits
    */
void BotInfo::armorupdated (int x)
{
    armorlevel.setValue(x);

    if (x <= 0) {
        botnam.setEnabled(false);
        armormsg.setEnabled(false);
        armorlevel.setEnabled(false);
        heatmsg.setEnabled(false);
        heatlevel.setEnabled(false);
        msgmsg.setEnabled(false);
        message.setEnabled(false);
    }
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
void BotInfo::updatefuel (int fuel,int heat)
{
    msgmsg.setText (QString::asprintf("F: %d", fuel));
    heatlevel.setValue(heat);
}

/**
    * Shows new message
    */
void BotInfo::newmessage (char *msg)
{
    message.setText(QString::asprintf("M: %s", msg));
}
