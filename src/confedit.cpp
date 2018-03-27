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
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStandardPaths>
#include <QMessageBox>
#include <QSettings>

#include "confstruct.h"
#include "commonsymbols.h"

/**
	* Constructor: Init GUI
	*/
ConfEdit::ConfEdit()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose);

    defaultbutton = new QPushButton ("Load default values" , this);
    openbutton = new QPushButton ("Open existing config" , this);
    savebutton = new QPushButton ("Save current config", this);
    closebutton = new QPushButton ("Close config editor",this);
    makecurrentbutton = new QPushButton ("Apply current config", this);
    helpbutton = new QPushButton ("HELP", this);

    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->addWidget(defaultbutton, 0, 0);
    buttonsLayout->addWidget(openbutton, 0, 1);
    buttonsLayout->addWidget(savebutton, 0, 2);
    buttonsLayout->addWidget(closebutton, 1, 0);
    buttonsLayout->addWidget(makecurrentbutton, 1, 1);
    buttonsLayout->addWidget(helpbutton, 1, 2);
    mainLayout->addLayout(buttonsLayout);

    connect (defaultbutton, &QAbstractButton::clicked, this, &ConfEdit::defaultc);
    connect (openbutton, &QAbstractButton::clicked, this, &ConfEdit::openc);
    connect (savebutton, &QAbstractButton::clicked, this, &ConfEdit::savec);
    connect(closebutton, &QPushButton::clicked, this, &ConfEdit::close);
    connect (makecurrentbutton, &QAbstractButton::clicked, this, &ConfEdit::makecurrc);
    connect (helpbutton, &QAbstractButton::clicked, this,
                      &ConfEdit::helpRequested);

    valid = new QIntValidator (this);

    scroll = new QScrollArea (this);
    mainLayout->addWidget(scroll);

    setarea = new QWidget();
    QVBoxLayout *setareaLayout = new QVBoxLayout(setarea);
    scroll->setWidgetResizable(true);
    scroll->setWidget(setarea);

    maxdevl = new QLabel ("Maximum number of devices: ", setarea);
    maxdevv = new QSpinBox (setarea);
    maxdevv->setMinimum(1);
    maxdevv->setMaximum(32);
    maxdevv->setSingleStep(1);

    maxcostl = new QLabel ("Maximum cost of bot: ", setarea);
    maxcostv = new QSpinBox (setarea);
    maxcostv->setMinimum(100);
    maxcostv->setMaximum(65500);
    maxcostv->setSingleStep(100);

    maxraml = new QLabel ("Maximum amount of RAM: ", setarea);
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

    QGridLayout *optionsLayout = new QGridLayout;
    optionsLayout->addWidget(maxdevl, 0, 0);
    optionsLayout->addWidget(maxdevv, 0, 1);
    optionsLayout->addWidget(maxcostl, 1, 0);
    optionsLayout->addWidget(maxcostv, 1, 1);
    optionsLayout->addWidget(maxraml, 2, 0);
    optionsLayout->addWidget(maxramv, 2, 1);
    optionsLayout->addWidget(ramcostl, 3, 0);
    optionsLayout->addWidget(ramcostv, 3, 1);

    setareaLayout->addLayout(optionsLayout);

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


    QGridLayout *devicesLayout = new QGridLayout;
    setareaLayout->addLayout(devicesLayout);

    for (int x=0; x<numdev; x++)
    {
        QGridLayout *deviceLayout = new QGridLayout(devicegroup[x]);
        devicesenabled[x] = new QCheckBox ("enabled",devicegroup[x]);
        deviceLayout->addWidget(devicesenabled[x], 0, 0);
        costs[x] = new QLabel ("Cost of device: ", devicegroup[x]);
        deviceLayout->addWidget(costs[x], 1, 0);

        levelcosts[x] = new QComboBox (devicegroup[x]);
        levelcosts[x]->setEditable(true);
        levelcosts[x]->setInsertPolicy (pol);
        levelcosts[x]->addItem ("100");
        levelcosts[x]->addItem ("200");
        levelcosts[x]->addItem ("300");
        levelcosts[x]->addItem ("400");
        levelcosts[x]->addItem ("500");
        levelcosts[x]->setValidator (valid);
        deviceLayout->addWidget(levelcosts[x], 1, 1);
        levelcosts[x]->setMaxCount (6);

        values[x] = new QLabel ("Values for dev: ", devicegroup[x]);
        deviceLayout->addWidget(values[x], 2, 0);

        levelvalues[x] = new QComboBox (devicegroup[x]);
        levelvalues[x]->setEditable(true);
        levelvalues[x]->setInsertPolicy (pol);
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->addItem ("0");
        levelvalues[x]->setValidator (valid);
        deviceLayout->addWidget(levelvalues[x], 2, 1);
        levelvalues[x]->setMaxCount (6);


        if (x < 10) {
            devicesLayout->addWidget(devicegroup[x], x, 0);
        } else {
            devicesLayout->addWidget(devicegroup[x], x-10, 1);

        }
    }

    openfile (QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg"));
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
    openfile (":/misc/current.cfg");
}

/**
	* Opens existing config file and loads those values
	*/
void ConfEdit::openc()
{
    QSettings settings;

    QString filename = QFileDialog::getOpenFileName (this, tr("Select config file"), settings.value("LastConfFile").toString(), "*.cfg");
    if (filename.isEmpty()) {
        return;
    }

    settings.setValue("LastConfFile", filename);
    openfile (filename);
}
/**
	* Saves current setings to a config file
	*/
void ConfEdit::savec()
{
    QSettings settings;
    QString filename = QFileDialog::getSaveFileName (this, tr("Select config file"), settings.value("LastConfFile").toString(), "*.cfg");
    if (filename.isEmpty())
    {
        return;
    }
    settings.setValue("LastConfFile", filename);
    save(filename);
}

/**
	* Saves curreent settings to homedir/droidbattles/current.cfg
	*/
void ConfEdit::makecurrc()
{
    QDir baseDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if (!baseDir.exists()) {
        baseDir.mkpath(baseDir.absolutePath());
    }

    QString filename = baseDir.absoluteFilePath("current.cfg");
    save(filename);
}

void ConfEdit::openfile (const QString &filename)
{
    if (filename.isEmpty()) {
        return;
    }
    ConfStruct conf;
    conf.load(filename);
    maxdevv->setValue(conf.maxdev);
    maxcostv->setValue(conf.maxcost);
    maxramv->setCurrentIndex(conf.maxram);

    int x, y;
    for (x=0; x<9; x++) {
        ramcostv->setItemText(x, QString::number(conf.ramcost[x]));
    }

    for (x=0; x<numdev; x++) {
        devicesenabled[x]->setChecked(conf.enabled[x]);
        for (y=0; y<5; y++) {
            levelcosts[x]->setItemText (y, QString::number(conf.cost[y][x]));
            levelvalues[x]->setItemText (y, QString::number(conf.values[y][x]));
        }
    }
}

void ConfEdit::save(const QString &filename)
{
    ConfStruct conf;
    conf.maxdev = maxdevv->cleanText().toInt();
    conf.maxcost = maxcostv->cleanText().toInt();
    conf.maxram = maxramv->currentIndex();
    int x, y;
    for (x=0; x<9; x++) {
        conf.ramcost[x] = ramcostv->itemText(x).toInt();
    }

    for (x=0; x<numdev; x++) {
        conf.enabled[x] = devicesenabled[x]->isChecked();
        for (y=0; y<5; y++) {
            conf.cost[y][x] = levelcosts[x]->itemText(y).toInt();
            conf.values[y][x] = levelvalues[x]->itemText(y).toInt();;
        }
    }
    conf.save(filename);
}
