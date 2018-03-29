#include "confstruct.h"
#include "device.h"
#include <QFile>
#include <QSettings>
#include <QString>

#define KEY_MAXDEVICES "MaxDevices"
#define KEY_MAXCOST "MaxCost"
#define KEY_MAXRAM "MaxRam"
#define GROUP_RAMCOSTS "RamCosts"
#define GROUP_DEVICES "Devices"
#define KEY_ENABLED "Enabled"
#define KEY_COST "Cost"
#define KEY_VALUE "Value"

void ConfStruct::load(QString filename)
{
    if (!QFile::exists(filename)) {
        filename = ":/misc/current.cfg";
    }

    QScopedPointer<QSettings> conf(new QSettings(filename, QSettings::IniFormat));

    if (conf->childGroups().isEmpty()) {
        conf.reset(new QSettings(":/misc/current.cfg", QSettings::IniFormat));

    }


    maxdev = conf->value(KEY_MAXDEVICES, 12).toInt();
    maxcost = conf->value(KEY_MAXCOST, 3300).toInt();
    maxram = conf->value(KEY_MAXRAM, 1).toInt();

    conf->beginGroup(GROUP_RAMCOSTS);
    const int defaultRamCost[9] = { 100, 150, 225, 350, 500, 750, 1200, 1800, 3000 };
    for (int i = 0; i < 9; i++) {
        ramcost[i] = conf->value(QString::number(i), defaultRamCost[i]).toInt();
    }
    conf->endGroup();

    conf->beginGroup(GROUP_DEVICES);
    for (int dev = 0; dev < 20; dev++) {
        conf->beginGroup(Device::deviceName(dev));
        enabled[dev] = conf->value(KEY_ENABLED, true).toBool();
        for (int level = 0; level < 5; level++) {
            conf->beginGroup(QString::number(level));
            cost[level][dev] = conf->value(KEY_COST).toInt();
            values[level][dev] = conf->value(KEY_VALUE).toInt();
            conf->endGroup();
        }
        conf->endGroup();
    }

    conf->endGroup();
}

void ConfStruct::save(const QString &filename)
{
    QSettings conf(filename, QSettings::IniFormat);
    conf.setValue(KEY_MAXDEVICES, maxdev);
    conf.setValue(KEY_MAXCOST, maxcost);
    conf.setValue(KEY_MAXRAM, maxram);

    conf.beginGroup(GROUP_RAMCOSTS);
    for (int i = 0; i < 9; i++) {
        conf.setValue(QString::number(i), ramcost[i]);
    }
    conf.endGroup();

    conf.beginGroup(GROUP_DEVICES);
    for (int dev = 0; dev < 20; dev++) {
        conf.beginGroup(Device::deviceName(dev));
        conf.setValue(KEY_ENABLED, enabled[dev]);
        for (int level = 0; level < 5; level++) {
            conf.beginGroup(QString::number(level));
            conf.setValue(KEY_COST, cost[level][dev]);
            conf.setValue(KEY_VALUE, values[level][dev]);
            conf.endGroup();
        }
        conf.endGroup();
    }
    conf.endGroup();
}
