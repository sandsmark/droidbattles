/***************************************************************************
                          devchoice.cpp  -  description
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

#include "devchoice.h"
//Added by qt3to4:
#include <QDebug>
#include <QFrame>
#include <QGroupBox>
#include <QLabel>
#include <QStandardPaths>
#include <QVBoxLayout>

/** Holds one group of the device choosing group of combobox etc. in
	* the createbot dialog
	*/

DevChoice::DevChoice(CreateBot *cre, QWidget *parent, int num) :
    QGroupBox(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    setLayout(mainLayout);

    chosenlevel = 0;
    dev = 0;
    int x;
    mynum = num;
    comb = new QComboBox(this);
    comb->setEditable(false);
    comb->addItem("none");
    comb->addItem("CPU");
    comb->addItem("engine");
    comb->addItem("steering");
    comb->addItem("plasmagun");
    comb->addItem("armor");
    comb->addItem("scanner");
    comb->addItem("fuel");
    comb->addItem("chaff");
    comb->addItem("turret");
    comb->addItem("scanwarn");
    comb->addItem("timedev");
    comb->addItem("shield");
    comb->addItem("repair");
    comb->addItem("radio");
    comb->addItem("chiller");
    comb->addItem("cloaker");
    comb->addItem("minelayer");
    comb->addItem("missile");
    comb->addItem("beam");
    comb->addItem("AS-rocket");
    mainLayout->addWidget(comb, 0, 0);

    level = new QButtonGroup(this);
    QGroupBox *radioButtons = new QGroupBox;
    QHBoxLayout *levelsLayout = new QHBoxLayout(radioButtons);
    levelsLayout->setMargin(0);
    radioButtons->setFlat(true);
    for (x = 0; x < 5; x++) {
        levels[x] = new QRadioButton(radioButtons);
        levelsLayout->addWidget(levels[x]);
        level->addButton(levels[x], x);
    }
    mainLayout->addWidget(radioButtons, 1, 0);

    arg1 = new QLineEdit(this);
    mainLayout->addWidget(arg1, 0, 1);
    connect(level, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &DevChoice::levelchosen);
    arg1->setMaximumWidth(100);
    valid = new QIntValidator(0, 31, this);
    arg1->setValidator(valid);
    showcost = new QLabel("Cost", this);
    mainLayout->addWidget(showcost, 1, 1, 1, 2);

    info = new QPushButton("info", this);
    mainLayout->addWidget(info, 0, 2);

    QObject::connect(this, SIGNAL(change()), this, SLOT(costchanged()));
    QObject::connect(info, SIGNAL(clicked()), this, SLOT(showinfo()));
    QObject::connect(comb, SIGNAL(activated(int)), this,
                     SLOT(costchanged()));

    callb = cre;
}

DevChoice::~DevChoice()
{
}

/**
	* Returns the number of the device chosen
	*/
unsigned short DevChoice::getitem()
{
    return comb->currentIndex();
}

/**
	* Sets the device chosen
	*/
void DevChoice::setitem(int x)
{
    comb->setCurrentIndex(x);
    emit change();
}

/**
	* Sets the level of the device (0-4)
	*/
void DevChoice::levelchosen(int x)
{
    chosenlevel = x;
    levels[x]->setChecked(true);
    emit change();
}

/**
	* Returns the level (0-4)
	*/
int DevChoice::getlevel()
{
    return chosenlevel;
}

/**
	* Returns the extra argument for the device (white box)
	*/
int DevChoice::getarg1()
{
    QString temp = arg1->text();
    return (temp.trimmed()).toInt();
}

/**
	* Sets the value in the white box
	*/
void DevChoice::setarg1(const QString &value)
{
    arg1->setText(value.trimmed());
}

void DevChoice::costchanged()
{
    struct ConfStruct curconfig;
    curconfig.load(QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg"));

    int dev = getitem();
    if (dev == 0) {
        return;
    }
    int devlev = getlevel();

    QString resulttext;
    resulttext = "Cost:";
    resulttext += QString::number(curconfig.cost[devlev][dev - 1]);
    showcost->setText(resulttext);
}

void DevChoice::showinfo()
{
    QString msg;
    msg = "Info about device number";
    msg += QString::number(mynum);
    msg += " :\n";

    int dvn = callb->devnum(getitem(), mynum);

    switch (getitem()) {
    case 0:
        msg += "No device chosen";
        break;
    case 1:
        msg += "CPU device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " CPU";
        msg += QString::number(dvn);
        msg += "_GetXSize: Get X-size of battlefield\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " CPU";
        msg += QString::number(dvn);
        msg += "_GetYSize: Get Y-size of battlefield\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " CPU";
        msg += QString::number(dvn);
        msg += "_GetBattleType: Get type of battle (0-normal,1-survival,"
               "2-deathmatch)\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += " CPU";
        msg += QString::number(dvn);
        msg += "_GetMyTeam: Get my team/frequency\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += ": Add interrupt (intended for internal use)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 2:
        msg += "Engine device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Engine";
        msg += QString::number(dvn);
        msg += "_GetThrust: Get current thrust level\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Engine";
        msg += QString::number(dvn);
        msg += "_GetSpeed: Get current speed\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Engine";
        msg += QString::number(dvn);
        msg += "_SetThrust: Set thrust level/wanted speed\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Engine";
        msg += QString::number(dvn);
        msg += "_SetReverseThrust: Set wanted reverse speed\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 3:
        msg += "steering device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_GetDir: Get current direction\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_GetWantedDir: Get wanted direction\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_GetXPos: Get X position of bot\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_GetYPos: Get Y position of bot\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_AdjustWantedDir: Adjust wanted direction (relative to wanted d"
               "ir)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_SetDir: Adjust wanted direction (at absolute heading)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Steering";
        msg += QString::number(dvn);
        msg += "_AdjustCurrentDir: Adjust wanted direction (relative to current"
               " dir)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 4:
        msg += "Plasmagun device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Plasmagun";
        msg += QString::number(dvn);
        msg += "_Shoot: Shoot one shot\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 5:
        msg += "Armor device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_GetArmor: Get amount of armor\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_GetHeat: Get amount of heat in bot\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_SetCollIntEnabled: Enable/disable hit/collision interrupt\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_SetArmorIntEnabled: Enable/disable armor below level interrupt\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_SetArmorIntLevel: Set level for interrupt\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += " Armor";
        msg += QString::number(dvn);
        msg += "_SetHeatIntLevel: empty\n";

        break;
    case 6:
        msg += "Scanner device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_GetScanDistance: Get distance to object last scanned\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_GetScanAccuracy: Get accuracy of last scan\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_GetScanWidth: Get width of scanner beam\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_GetScanInfo: Get one of four things set by third outport\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_Scan: Emit scan pulse\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_SetScanWidth: Set width of scanner\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_SelectReturn: Select what fourth inport should return:\n";
        msg += "0:Frequency,1:number,2:direction,3:speed of object last scanned\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += " Scanner";
        msg += QString::number(dvn);
        msg += "_SetSensitivity: Set sensitivity for scanner\n";

        break;
    case 7:
        msg += "fuel device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Fuel";
        msg += QString::number(dvn);
        msg += "_GetFuel: Get amount of fuel\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Fuel";
        msg += QString::number(dvn);
        msg += "_SetFuelIntEnabled: Enable/disable low fuel interrupt\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Fuel";
        msg += QString::number(dvn);
        msg += "_SetFuelIntLevel: Set level for interrupt\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 8:
        msg += "Chaff device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Chaff";
        msg += QString::number(dvn);
        msg += "_GetDebris: Get number of debris left\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Chaff";
        msg += QString::number(dvn);
        msg += "_ReleaseDebris: Release debris\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 9:
        msg += "Turret device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Turret";
        msg += QString::number(dvn);
        msg += "_GetOffset: Return offset\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Turret";
        msg += QString::number(dvn);
        msg += "_GetWantedOffset: Return wanted offset\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Turret";
        msg += QString::number(dvn);
        msg += "_SetOffset: Put at absolute offset\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Turret";
        msg += QString::number(dvn);
        msg += "_AdjustOffset: Change offset relative to wanted offset\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Turret";
        msg += QString::number(dvn);
        msg += "_AdjustCurrentOffset: Change offset relative to current offset\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 10:
        msg += "Scanwarner device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " ScanWarn";
        msg += QString::number(dvn);
        msg += "_GetNumScans: Get number of scans\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " ScanWarn";
        msg += QString::number(dvn);
        msg += "_GetScanDir: Get approximate dir of last scan\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " ScanWarn";
        msg += QString::number(dvn);
        msg += "_GetScanIntensity: Get intensity of last scan\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " ScanWarn";
        msg += QString::number(dvn);
        msg += "_ZeroCounter: Zero scan counter\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 11:
        msg += "Time device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_GetTime: Get current time\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_GetIntTime: Get interrupt time\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_GetIntEnabled: Get time interrupt enabled/disabled\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_SetTime: Set current time\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_SetIntTime: Set interrupt time\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Timer";
        msg += QString::number(dvn);
        msg += "_SetIntEnabled: Set interrupt enabled/disabled\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 12:
        msg += "Shield device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Shield";
        msg += QString::number(dvn);
        msg += "_GetShieldEnabled: Get state of shield\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Shield";
        msg += QString::number(dvn);
        msg += "_SetShieldEnabled: Up/Down with shield (1/0)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 13:
        msg += "Repair device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 14:
        msg += "Radio device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_GetNumMsgs: Get number of values in msg queue\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_GetMsg: Get first value in msg queue\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_GetMyNum: Get my number\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_SetReceiver: Set receiver (255 means broadcast)\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_SendMsg: Send number\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Radio";
        msg += QString::number(dvn);
        msg += "_SetMsgIntEnabled: Enable/disable msg received int\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 15:
        msg += "Chiller device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Chiller";
        msg += QString::number(dvn);
        msg += "_SetExtraCooling: Set extra cooling on/off\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 16:
        msg += "Cloak device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Cloak";
        msg += QString::number(dvn);
        msg += "_EnableCloak: Set cloak up/down\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 17:
        msg += "Minelayer device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Minelayer";
        msg += QString::number(dvn);
        msg += "_GetMines: Get mines left\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Minelayer";
        msg += QString::number(dvn);
        msg += "_LayMine: Lay mine\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 18:
        msg += "Missile device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Missile";
        msg += QString::number(dvn);
        msg += "_GetLoadTime: Get reloadtime\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Missile";
        msg += QString::number(dvn);
        msg += "_SetBootPos: Set bootposition\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Missile";
        msg += QString::number(dvn);
        msg += "_SetStackPos: Set stackposition\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Missile";
        msg += QString::number(dvn);
        msg += "_FireMissile: Fire missile\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 19:
        msg += "Beam device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Beam";
        msg += QString::number(dvn);
        msg += "_GetDir: Get dir\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Beam";
        msg += QString::number(dvn);
        msg += "_GetLength: Get length\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Beam";
        msg += QString::number(dvn);
        msg += "_FireBeam: Fire beam\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Beam";
        msg += QString::number(dvn);
        msg += "_SetBeamDir: Set dir of beam\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += " Beam";
        msg += QString::number(dvn);
        msg += "_SetBeamLength: Set length of beam\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    case 20:
        msg += "Rocket device\n\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4);
        msg += " Rocket";
        msg += QString::number(dvn);
        msg += "_GetReadiness: Get readiness\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Rocket";
        msg += QString::number(dvn);
        msg += "_GetDistance: Get distance\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Inport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4);
        msg += " Rocket";
        msg += QString::number(dvn);
        msg += "_SetDistance: Set distance\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 1);
        msg += " Rocket";
        msg += QString::number(dvn);
        msg += "_FireRocket: Fire rocket\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 2);
        msg += ": empty\n";

        msg += "Outport ";
        msg += QString::number(mynum * 4 + 3);
        msg += ": empty\n";

        break;
    }
    //	QMessageBox::information( this,"Devinfo",msg );
    showbox = new InfoBox(msg, nullptr);
}
