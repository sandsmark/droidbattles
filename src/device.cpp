/***************************************************************************
                          device.cpp  -  description
                             -------------------
    begin                : Mon Apr 3 2000
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

#include "device.h"
#include <QMap>
const QStringList Device::s_deviceNames = {
    "CPU",
    "engine",
    "steering",
    "plasmagun",
    "armor",
    "scanner",
    "fuel",
    "chaff",
    "turret",
    "scanwarner",
    "timedev",
    "shield",
    "repair",
    "radio",
    "chiller",
    "cloaker",
    "minelayer",
    "missile",
    "beam",
    "AS-rocket"
};

Device::Device(ScreenObject &object)
{
    ourbot = &object;
}

const QString Device::deviceName(int index)
{
    if (index >= 0 && index < s_deviceNames.size()) {
        return s_deviceNames[index];
    }
    return QString::asprintf("Unknown device %d", index);
}

int Device::deviceId(const QString &name)
{
    int ret = s_deviceNames.indexOf(name);
    if (ret == -1) {
        return 0;
    }
    return ret;
}

Device::Device()
{
}

Device::~Device()
{
}

/**
	* Take in a value in the port (after an out instruktion from the CPU
	* And place it in the stack
	*/
void Device::addInputPort(uint8_t port, uint16_t value)
{
    for (int count = 0; count < 4; count++) {
        if (!stacktaken[port][count]) {
            stacktaken[port][0] = true;
            portstack[port][0] = value;
            break;
        }
    }
}

void Device::execute()
{
}

int Device::readPort(uint8_t /*port*/)
{
    return 0;
}

int Device::absorbHit(int str, int /*ifint*/)
{
    return str;
}

void Device::erase(QPainter * /*buffer*/)
{
}

void Device::draw(QPainter * /*buffer*/)
{
}

/**
	* Sets relative angle of device (relative to bot)
	* ie. turret calls this function in the device he "turrets"
	*/
void Device::setRelativeAngle(int x)
{
    relang = x;
}

int Device::type()
{
    return 0;
}

int Device::specialValue()
{
    return 0;
}

struct DebugContents Device::debugContents()
{
    return DebugContents();
}

void Device::doSpecial(int /*x*/, int /*y*/)
{
}

/**
	* Move the sack one step down for port "port"
	*/
void Device::moveportstack(int port)
{
    int count;
    for (count = 0; count < 3; count++) {
        portstack[port][count] = portstack[port][count + 1];
        stacktaken[port][count] = stacktaken[port][count + 1];
    }
    portstack[port][3] = 0;
    stacktaken[port][3] = false;
}
