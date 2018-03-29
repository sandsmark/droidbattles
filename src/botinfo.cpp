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
#include <QFileInfo>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include "robots.h"
#include <QDebug>

/**
    * Constructor, create all GUI elements
    */
BotInfo::BotInfo(const QString &botname, ScreenObject *rb)
{
    bot = qobject_cast<Robots*>(rb);

    if (!bot || botname.isEmpty()) {
        botnam.setVisible(false);
        armormsg.setVisible(false);
        armorlevel.setVisible(false);
        heatmsg.setVisible(false);
        heatlevel.setVisible(false);
        m_fuelLevel.setVisible(false);
        message.setVisible(false);
        ifscanner.setVisible(false);
        showgfx.setVisible(false);
        return;
    }

    botnam.setText(QFileInfo(botname).baseName());

    armormsg.setText("A:");

    armorlevel.setMaximum(bot->armorval);
    armorlevel.setValue(bot->armorval);

    m_fuelLevel.setMaximum(bot->fuelval);
    m_fuelLevel.setMaximum(bot->fuelval);

    heatmsg.setText("H:");

    heatlevel.setMaximum(850);
    heatlevel.setValue(0);

    m_fuelLabel.setText("F: ");

    message.setText("M: ");

    ifscanner.setText("Show device gfx");
    ifscanner.setChecked(true);
    connect(&ifscanner, &QAbstractButton::toggled, this, &BotInfo::statch);

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
    BotInfo *botInfo = new BotInfo(name, screenObject);
    botInfo->setParent(layout);

    layout->addWidget(&botInfo->botnam, index, 0);
    layout->addWidget(&botInfo->armormsg, index, 1);
    layout->addWidget(&botInfo->armorlevel, index, 2);
    layout->addWidget(&botInfo->heatmsg, index, 3);
    layout->addWidget(&botInfo->heatlevel, index, 4);
    layout->addWidget(&botInfo->m_fuelLabel, index, 5);
    layout->addWidget(&botInfo->m_fuelLevel, index, 6);
    layout->addWidget(&botInfo->message, index, 7);
    layout->addWidget(&botInfo->ifscanner, index, 8);
    layout->addWidget(&botInfo->showgfx, index, 9);

    return botInfo;
}

int BotInfo::score()
{
    if (!bot) {
        return 0;
    }
    int ret = 0;

    // Score calculation
    ret -= bot->cost();

    if (armorlevel.maximum()) {
        ret += 1000 * armorlevel.value() / armorlevel.maximum();
    }

    if (m_fuelLevel.maximum()) {
        ret += 1000 * m_fuelLevel.value() / m_fuelLevel.maximum();
    }

    return ret;
}

/**
    * Updates armor progressbar
    * Connected to armorchanged signal that the bot emits
    */
void BotInfo::armorupdated(int x)
{
    armorlevel.setValue(x);

    if (x <= 0) {
        botnam.setEnabled(false);
        armormsg.setEnabled(false);
        armorlevel.setEnabled(false);
        heatmsg.setEnabled(false);
        heatlevel.setEnabled(false);
        m_fuelLabel.setEnabled(false);
        m_fuelLevel.setEnabled(false);
        message.setEnabled(false);
    }
}

/**
    * emits signal that makes the bots show/not show device gfx
    */
void BotInfo::statch(bool x)
{
    emit(changeinset(x));
}

/**
    * Updates fuel value
    */
void BotInfo::updatefuel(int fuel, int heat)
{
    m_fuelLevel.setValue(fuel);
    heatlevel.setValue(heat);
}

/**
    * Shows new message
    */
void BotInfo::newmessage(char *msg)
{
    message.setText(QString::asprintf("M: %s", msg));
}
