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
#include "pixbutton.h"
#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>

#define SETTINGS_BOTFILES "BotFiles"
#define SETTINGS_NUMFIGHTS "NumFights"
#define SETTINGS_LENGTHFIGHTS "LengthFights"
#define SETTINGS_MAX_X "MaxX"
#define SETTINGS_MAX_Y "MaxY"
#define SETTINGS_FAST "Fast"
#define SETTINGS_SEED "Seed"

/**
	* Init GUI elements
	*/
StartTournament::StartTournament(const QString &type) :
    m_type(type)
{
    botfiles = new QListWidget(this);

    press[0] = new PixButton("Add bot", this);

    press[1] = new PixButton("Remove selected", this);

    iffast = new QCheckBox("Fast (nodelay) battle", this);

    connect(press[0], &QAbstractButton::clicked, this,
            &StartTournament::choosefile);
    connect(press[1], &QAbstractButton::clicked, this,
            &StartTournament::dechoosefile);

    readyb = new PixButton("OK", this);
    cancelb = new PixButton("cancel", this);

    connect(readyb, &QAbstractButton::clicked, this, &StartTournament::ocl);
    connect(cancelb, &QAbstractButton::clicked, this, &StartTournament::ccl);

    tnumfights = new QLabel("Number of fights:", this);
    wnumfights = new QSpinBox(this);
    wnumfights->setMinimum(1);

    lengthfight = new QLabel("Max length of fight (approximately 50 ticks per 1 sec):", this);

    length = new QSpinBox(this);
    length->setMinimum(50);
    length->setMaximum(180000);

    maxxinfo = new QLabel("The xsize of the battlearea: ", this);
    maxx = new QSpinBox(this);
    maxx->setMinimum(8192);
    maxx->setMaximum(65535);
    maxx->setSingleStep(512);
    maxx->setValue(32768);

    maxyinfo = new QLabel("The ysize of the battlearea: ", this);
    maxy = new QSpinBox(this);
    maxy->setMinimum(8192);
    maxy->setMaximum(65535);
    maxy->setSingleStep(512);
    maxy->setValue(32768);

    seedinfo = new QLabel("Random seed used (0 for random): ", this);
    seed = new QLineEdit(this);

    QGridLayout *l = new QGridLayout;
    l->addWidget(press[0], 0, 1);
    l->addWidget(press[1], 0, 2);

    l->addWidget(botfiles, 1, 0, 1, 3);

    l->addWidget(iffast, 2, 0);

    l->addWidget(tnumfights, 3, 0);
    l->addWidget(wnumfights, 3, 2);

    l->addWidget(lengthfight, 4, 0);
    l->addWidget(length, 4, 2);

    l->addWidget(maxxinfo, 5, 0);
    l->addWidget(maxx, 5, 2);

    l->addWidget(maxyinfo, 6, 0);
    l->addWidget(maxy, 6, 2);

    l->addWidget(seedinfo, 7, 0);
    l->addWidget(seed, 7, 2);

    l->addWidget(readyb, 8, 1);
    l->addWidget(cancelb, 8, 2);

    setLayout(l);

    m_randomDevice = std::make_shared<std::mt19937>(BattleConfig::seedingDevice());

    load();

    readyb->setDefault(true);
}

StartTournament::~StartTournament()
{
}

int StartTournament::getnumofbots()
{
    return botfiles->count();
}

/**
	* Return the dir for bot x
	*/
QString StartTournament::getbotfile(int x)
{
    return botfiles->item(x)->text();
}

/**
	* Chooses one file on the HD
	*/
void StartTournament::choosefile()
{
    QSettings settings;
    QString filename = QFileDialog::getOpenFileName(this, tr("Select bot file"), settings.value("LastBotPath").toString(), "*.bot");
    if (filename.isEmpty()) {
        return;
    }
    settings.setValue("LastBotPath", filename);

    botfiles->addItem(filename);
}

/**
	* Removes one bot in the list
	*/
void StartTournament::dechoosefile()
{
    delete botfiles->takeItem(botfiles->currentRow());
}

void StartTournament::ocl()
{
    save();
    emit okclicked();
}

void StartTournament::ccl()
{
    emit cancelclicked();
}

void StartTournament::save()
{
    QSettings settings;
    settings.beginGroup(m_type);

    QStringList files;
    for (int i = 0; i < botfiles->count(); i++) {
        files.append(botfiles->item(i)->text());
    }

    settings.setValue(SETTINGS_BOTFILES, files);
    settings.setValue(SETTINGS_NUMFIGHTS, wnumfights->value());
    settings.setValue(SETTINGS_LENGTHFIGHTS, length->value());
    settings.setValue(SETTINGS_MAX_X, maxx->value());
    settings.setValue(SETTINGS_MAX_Y, maxy->value());
    settings.setValue(SETTINGS_FAST, iffast->isChecked());
    settings.setValue(SETTINGS_SEED, seed->text());
}

void StartTournament::load()
{
    QSettings settings;
    settings.beginGroup(m_type);

    botfiles->clear();
    botfiles->addItems(settings.value(SETTINGS_BOTFILES).toStringList());

    wnumfights->setValue(settings.value(SETTINGS_NUMFIGHTS).toInt());
    length->setValue(settings.value(SETTINGS_LENGTHFIGHTS, 3000).toInt());
    maxx->setValue(settings.value(SETTINGS_MAX_X, 32768).toInt());
    maxy->setValue(settings.value(SETTINGS_MAX_Y, 32768).toInt());
    iffast->setChecked(settings.value(SETTINGS_FAST).toBool());

    uint loadedSeed = settings.value(SETTINGS_SEED, BattleConfig::seedingDevice()).toUInt();
    seed->setText(QString::number(loadedSeed));

    m_randomDevice->seed(loadedSeed);
}

/**
	* Don't close if the "X" is clicked
	*/
void StartTournament::closeEvent(QCloseEvent *e)
{
    e->ignore();
}

/**
	* The following functions returns the settings
	*/
int StartTournament::getnumfights()
{
    QString s = wnumfights->text();
    if (s.length() == 0) {
        return 0;
    }

    return s.toInt();
}

int StartTournament::getlength()
{
    return length->value();
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

/**
	* Returns the random seed
	*/
uint StartTournament::getseed()
{
    return seed->text().toUInt();
}

void StartTournament::setseed(uint s)
{
    seed->setText(QString::number(s));

    save();
}

BattleConfig StartTournament::getBattleConfig()
{
    BattleConfig battleConfig;
    battleConfig.xSize = maxx->value();
    battleConfig.ySize = maxy->value();
    battleConfig.numFights = wnumfights->value();
    battleConfig.maxRounds = length->value();
    battleConfig.fastMode = iffast->isChecked();
    battleConfig.isTournament = true;
    battleConfig.random_seed = getseed();
    return battleConfig;
}
