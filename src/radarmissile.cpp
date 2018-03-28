/***************************************************************************
                          radarmissile.cpp  -  description
                             -------------------
    begin                : Fri Aug 11 2000
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

#include "radarmissile.h"
//Added by qt3to4:
#include <QDebug>
#include <QPixmap>
#include <QtMath>

/**
	* Init positions, devices and load gfx
	*/
RadarMissile::RadarMissile(int X, int Y, int dir, int bootm, int stm, int mnum,
                           TextmodeBattleArea &area, Ram *mem, int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    ourarea = &area;
    mynum = mnum;
    strength = 175;
    m_direction = dir;
    m_speed = 150;
    Xpos = X;
    Ypos = Y;
    noncollid = 256;
    double dira = direction() * pi / 512;
    setPosition(cos(dira) * 1500, sin(dira) * 1500);
    m_size = 8;
    if (useUI) {
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill(Qt::black);
        graphics = PixmapHolder::getpmp(PixmapHolder::RadarMissile);
    }
    ramdevice = mem;
    ramdevice->addowner();
    devices[1] = new Steering(*this, 4);
    devices[2] = new Scanner(*this, 20000, 0);
    devices[0] = new RobCpu(*ramdevice, *this, 2, bootm % 256, bootm / 256, stm % 256,
                            stm / 256);

    fuelval = 300;
    dbgWindow = nullptr;
}

RadarMissile::~RadarMissile()
{
    //	delete graphics;
    delete dbgWindow;
    if (useUI) {
        delete erasegfx;
    }
    delete devices[0];
    delete devices[1];
    delete devices[2];
    ramdevice->removeowner();
    if (ramdevice->getowners() == 0) {
        delete ramdevice;
    }
}

int RadarMissile::objectHit(int /*type*/, int /*strength*/)
{
    return objhitdestroyed;
}

ScreenObject::ObjectType RadarMissile::type()
{
    return ScreenObject::Collidable;
}

/**
	* Paint object black
	*/
void RadarMissile::eraseObject(QPixmap *buffer)
{
    QPainter painter(buffer);
    painter.drawPixmap((oldX >> 6) - 4, (oldY >> 6) - 4, *erasegfx);
    devices[2]->erase(&painter);
}

/**
	* Paint object gfx
	*/
void RadarMissile::drawObject(QPixmap *buffer, int opt)
{
    if (opt > 0) {
        return;
    }

    QPainter painter(buffer);
    painter.drawPixmap((xPos() >> 6) - 4, (yPos() >> 6) - 4, *graphics);
    oldX = int(Xpos);
    oldY = int(Ypos);
    devices[2]->draw(&painter);
}

/**
	* Execute devices, move and use fuel
	*/
int RadarMissile::execute()
{
    int x;
    for (x = 0; x < 3; x++) { //Execute all devices
        devices[x]->execute();
    }
    if (dbgWindow) {
        dbgWindow->updatedata(devices[0]->debugContents());
    }
    double dir = direction() * pi / 512;
    if (--fuelval <= 0) {
        return -1;
    }
    return setPosition(cos(dir) * m_speed, sin(dir) * m_speed); //Update position
}

int RadarMissile::setPosition(double X, double Y)
{
    oldX = int(Xpos);
    oldY = int(Ypos);
    Xpos += X;
    Ypos += Y;
    if (Xpos < 0) {
        return destroyself;
    }
    if (Xpos > ourarea->getareainfo(0)) {
        return destroyself;
    }
    if (Ypos < 0) {
        return destroyself;
    }
    if (Ypos > ourarea->getareainfo(1)) {
        return destroyself;
    }
    return 0;
}

int RadarMissile::collisionType()
{
    return 2;
}

int RadarMissile::collisionStrength()
{
    return 175;
}

/**
	* Inbetween function if the device want to call the
	* batlearea
	*/
int RadarMissile::writetoBattleArea(int bot, int dev, int choice, int arg1, int arg2)
{
    return ourarea->devio(bot, dev, choice, arg1, arg2);
}

/**
	* Get value from device port
	*/
int RadarMissile::readDevicePort(unsigned char port)
{
    int tempport = port % 4;
    int tempdevice = int(port / 4);
    int temp = -1;
    if (tempdevice < 3) {
        temp = devices[tempdevice]->readPort(tempport);
    } else {
        qWarning() << "Illegal port?" << port;
    }
    //setdebug1( temp );
    return temp;
}

/**
	* Put value in device port
	*/
void RadarMissile::writeDevicePort(unsigned char port, unsigned short value)
{
    int tempport = port % 4;
    int tempdevice = int(port / 4);
    if (tempdevice < 3) {
        devices[tempdevice]->addInputPort(tempport, value);
    }
}

int RadarMissile::returnRadar()
{
    return 4;
}

void RadarMissile::createDbgWindow(int id, QPlainTextEdit *e, int *l, int *m)
{
    delete dbgWindow;
    dbgWindow = new DebugWindow(e, &l[0], &m[0]);
    dbgWindow->resize(300, 405);
    dbgWindow->show();
    QString title;
    title.sprintf("Missile #%d", id);
    dbgWindow->setWindowTitle(title); // set title
}
