/***************************************************************************
                          robots.cpp  -  description
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

#include "robots.h"
#include <QDebug>
#include <QPixmap>
#include <QtMath>

/**
	* Init bot position, load program file and graphics
	*/
Robots::Robots(const QString &name, TextmodeBattleArea &object, int mnum, ConfStruct config,
               int tm, bool er, bool ui)
{
    gfxin = false;
    useUI = ui;
    int numdev = 0;
    int cost = 0;
    upcount = 0;
    m_team = tm;
    showerror = er;
    myfile = name;
    myfile = myfile.left(myfile.length() - 3);
    myfile += "dat";

    ourarea = &object;

    Xpos = ourarea->getstartx(mnum); //Get start position from battlearea
    Ypos = ourarea->getstarty(mnum);
    m_direction = qrand() % 1024;

    fuelval = 0;
    mynum = mnum;
    myowner = mnum;
    maxx = ourarea->getareainfo(0);
    maxy = ourarea->getareainfo(1);
    armorval = 0;
    m_speed = 0;
    QFile f(name); //Open the .bot file
    if (f.open(QIODevice::ReadOnly)) {
        QDataStream s(&f);
        uint32_t lng;
        char *tc;
        s.readBytes(tc, lng);
        uint8_t *my = (uint8_t *)&tc[0];
        showextragfx = true;
        f.close();
        if (my[1] > config.maxram) //Read in all devices
        {
            showError("Max amount of ram", name);
        }
        if (my[1] <= 9) {
            cost += config.ramcost[my[1]];
            switch (my[1]) {
            case 0:
                ramdevice = new Ram(1024, my);
                break;
            case 1:
                ramdevice = new Ram(2048, my);
                break;
            case 2:
                ramdevice = new Ram(4096, my);
                break;
            case 3:
                ramdevice = new Ram(8192, my);
                break;
            case 4:
                ramdevice = new Ram(16384, my);
                break;
            case 5:
                ramdevice = new Ram(24576, my);
                break;
            case 6:
                ramdevice = new Ram(32768, my);
                break;
            case 7:
                ramdevice = new Ram(49152, my);
                break;
            case 8:
                ramdevice = new Ram(65536, my);
                break;
            }
        } else {
            showError("File format error", name);
            ramdevice = new Ram();
        }
        int x;

        for (x = 0; x < 32; x++) {
            hitabsorborder[x] = 0;
        }
        int backx = 31;
        int forx = 0;
        int levelvalue = 0;
        for (x = 0; x < 32; x++) {
            if (my[x * 6 + 2] <= NUMDEV) {
                if (!config.enabled[my[x * 6 + 2] - 1] && my[x * 6 + 2] != 0) {
                    showError(QString("Using disabled device %1").arg(Device::deviceName(my[x * 6 + 2])), name);
                }
                if (my[x * 6 + 3] <= 4 && my[x * 6 + 2] > 0) {
                    numdev++;
                    cost += config.cost[my[x * 6 + 3]][my[x * 6 + 2] - 1];
                    levelvalue = config.values[my[x * 6 + 3]][my[x * 6 + 2] - 1];
                }
                if (my[x * 6 + 3] > 4) {
                    showError("File format error", name);
                    levelvalue = 0;
                }

                switch (my[x * 6 + 2]) {
                case 0:
                    devicelist[x] = new Device(*this);
                    break;
                case 1:
                    devicelist[x] = new RobCpu(*ramdevice, *this, levelvalue, my[x * 6 + 4],
                                               my[x * 6 + 5], my[x * 6 + 6], my[x * 6 + 7]);
                    break;
                case 2:
                    devicelist[x] = new Engine(*this, levelvalue);
                    break;
                case 3:
                    devicelist[x] = new Steering(*this, levelvalue);
                    break;
                case 4:
                    devicelist[x] = new Plasma(*this, levelvalue, my[x * 6 + 4]);
                    break;
                case 5:
                    devicelist[x] = new Armor(*this, levelvalue);
                    hitabsorborder[backx] = x;
                    backx--;
                    break;
                case 6:
                    devicelist[x] = new Scanner(*this, levelvalue, my[x * 6 + 4]);
                    break;
                case 7:
                    devicelist[x] = new Fuel(*this, levelvalue);
                    break;
                case 8:
                    devicelist[x] = new ChaffLauncher(*this, levelvalue);
                    break;
                case 9:
                    devicelist[x] = new Turret(*this, levelvalue, my[x * 6 + 4]);
                    break;
                case 10:
                    devicelist[x] = new ScanDetect(*this);
                    break;
                case 11:
                    devicelist[x] = new TimeDev(*this);
                    break;
                case 12:
                    devicelist[x] = new Shield(*this, levelvalue);
                    hitabsorborder[forx] = x;
                    forx++;
                    break;
                case 13:
                    devicelist[x] = new Repair(*this, levelvalue);
                    break;
                case 14:
                    devicelist[x] = new Communication(*this);
                    ourradiodev = x;
                    break;
                case 15:
                    devicelist[x] = new Chiller(*this, levelvalue);
                    break;
                case 16:
                    devicelist[x] = new Cloaker(*this, levelvalue);
                    break;
                case 17:
                    devicelist[x] = new MineLayer(*this, levelvalue);
                    break;
                case 18:
                    devicelist[x] = new RadarMissileLauncher(*this, levelvalue,
                                                             ramdevice, my[x * 6 + 4]);
                    break;
                case 19:
                    devicelist[x] = new Beamer(*this, levelvalue);
                    break;
                case 20:
                    devicelist[x] = new RocketLauncher(*this, levelvalue, my[x * 6 + 4]);
                    break;
                default:
                    devicelist[x] = new Device(*this);
                    break;
                }
            } else {
                showError("File format error", name);
                devicelist[x] = new Device(*this);
            }
        }
        if (numdev > config.maxdev) {
            showError(QString("Max number of devices (%1/%2").arg(numdev).arg(config.maxdev), name);
        }
        if (cost > config.maxcost) {
            showError("Max cost of bot", name);
        }

        delete[] my;
    } else {
        showError(QString("Couldn't open bot file %1!").arg(f.fileName()), name);
        ramdevice = new Ram;
        for (int x = 0; x < 32; x++) {
            devicelist[x] = new Device(*this);
        }
    }

    if (useUI) {
        erasegfx = new QPixmap(32, 32);
        erasegfx->fill(Qt::black);
        graphics = new QPixmap(32, 32);
        QString temp;
        temp = name;
        temp = temp.left(temp.length() - 3);
        temp += "png";
        QFile f2(temp);
        if (!f2.exists()) {
            temp = ":/images/ship" + QString::number(mynum) + ".png";
        }
        if (!graphics->load(temp)) {
            *graphics = QPixmap(32, 32);
            graphics->fill(Qt::white);
        } else {
            graphics->setMask(graphics->createHeuristicMask());
        }
        //Set a mask that makes the bot background transparent
        piccols = graphics->width() / 32;
        picrows = graphics->height() / 32;
        currentrow = 0;
        rowchangeval = 0;
        degreesperpic = 1024 / piccols;
    }
    m_size = 16;
    setHeat(0);
}

Robots::~Robots()
{
    int x;
    for (x = 0; x < 32; x++) {
        delete devicelist[x];
    }
    ramdevice->removeowner();
    if (ramdevice->getowners() == 0) {
        delete ramdevice;
    }
    if (useUI) {
        delete graphics;
        delete erasegfx;
    }
}

/**
	* Execute devices, adjust spedd and position
	*/
int Robots::execute()
{
    int x;
    currentradar = 5;
    for (x = 0; x < 32; x++) //Execute all devices
    {
        devicelist[x]->execute();
    }
    double dir = direction() * pi / 512;
    setPosition(cos(dir) * speed(), sin(dir) * speed()); //Update position
    rowchangeval += speed();
    if (rowchangeval > 512) {
        currentrow++;
        rowchangeval -= 512;
    }
    if (rowchangeval < 0) {
        currentrow--;
        rowchangeval += 512;
    }
    if (currentrow < 0) {
        currentrow = picrows - 1;
    }
    if (currentrow == picrows) {
        currentrow = 0;
    }

    upcount++;
    if (upcount > 10) {
        upcount = 0;
        if (useUI) {
            emit fuelchanged(fuelval, heat());
        }
    }
    changeHeat(-7);

    if (heat() > 500 && heat() <= 600) {
        objectHit(9, 1);
    }
    if (heat() > 600 && heat() <= 700) {
        objectHit(9, 2);
    }
    if (heat() > 700 && heat() <= 800) {
        objectHit(9, 5);
    }
    if (heat() > 800) {
        objectHit(9, 999);
    }

    return 0;
}

/**
	* Paint bot black
	*/
void Robots::eraseObject(QPixmap *buffer)
{
    QPainter painter(buffer);
    painter.drawPixmap((oldX >> 6) - 16, (oldY >> 6) - 16, *erasegfx);
    int x;
    if (gfxin) {
        for (x = 0; x < 32; x++) {
            devicelist[x]->erase(&painter);
        }
        gfxin = false;
    }
}

/**
	* Show bot gfx on screen
	*/
void Robots::drawObject(QPixmap *buffer, int opt)
{
    if (opt > 1) {
        return;
    }

    QPainter painter(buffer);

    int degrees = direction() + (degreesperpic / 2);
    if (degrees > 1023) {
        degrees -= 1024;
    }

    int picpos = int(degrees / degreesperpic) * 32;
    int ypicpos = currentrow * 32;

    int x;
    if (opt == 1) {
        painter.drawPixmap((xPos() >> 6) - 16, (yPos() >> 6) - 16, 32, 32, *graphics, picpos, ypicpos, 32, 32);
    } else if (showextragfx) {
        for (x = 0; x < 32; x++) {
            devicelist[x]->draw(&painter);
        }
        gfxin = true;
    }
}

/**
	* Get values from device ports
	*/
int Robots::readDevicePort(uint8_t port)
{
    int tempport = port % portsperdev;
    int tempdevice = int(port / portsperdev);
    int temp = devicelist[tempdevice]->readPort(tempport);
    return temp;
}

/**
	* Put values in device ports
	*/
void Robots::writeDevicePort(uint8_t port, uint16_t value)
{
    int tempport = port % portsperdev;
    int tempdevice = int(port / portsperdev);
    devicelist[tempdevice]->addInputPort(tempport, value);
}

/**
	* Inbetween function for devices that wants to add screenobjects to battlearea
	*/
void Robots::addScreenObject(int X, int Y, int dir, int type, int arg1,
                             int arg2, void *arg3)
{
    ourarea->addscrobject(mynum, X, Y, dir, type, arg1, arg2, arg3);
}

ScreenObject::ObjectType Robots::type()
{
    return ScreenObject::BotObject;
}

/**
	* Inbetween function for devices that want to communicate to battlearea
	*/
int Robots::writetoBattleArea(int bot, int dev, int choice, int arg1, int arg2)
{
    return ourarea->devio(bot, dev, choice, arg1, arg2);
}

/**
	* Inbetween function for when one device wants to do something with
	* another device
	*/
int Robots::writeToDevice(int dev, int action, int value)
{
    switch (action) {
    case 1:
        if (dev < 32 && dev >= 0) {
            devicelist[dev]->setRelativeAngle(value);
        }
        break;
    case 2:
        return devicelist[dev]->type();
        break;
    case 3:
        return devicelist[dev]->specialValue();
        break;
    case 4:
        devicelist[dev]->doSpecial(value);
        emit armorchanged(armorval);
        break;
    }
    return 0;
}

int Robots::collisionType()
{
    return 1;
}

int Robots::collisionStrength()
{
    return int(m_speed / 5);
}

/**
	* If hit, let armor and shield absorb hit.
	* If that doesn't help, die
	*/
int Robots::objectHit(int type, int strength)
{
    int x;
    int xy;
    int strengthleft = strength;

    int ifint;
    if (type == 9) {
        ifint = 1;
    } else {
        ifint = 0;
    }
    for (x = 0; x < 32; x++) {
        xy = hitabsorborder[x];
        strengthleft = devicelist[xy]->absorbHit(strengthleft, ifint);
        if (strengthleft <= 0) {
            break;
        }
    }
    if (useUI) {
        emit armorchanged(armorval);
    }

    if (strengthleft > 0) {
        return objhitdestroyed;
    }
    return 0;
}

int Robots::size()
{
    return m_size;
}

QString Robots::getDebugMessage1()
{
    return debug1;
}

QString Robots::getDebugMessage2()
{
    return debug2;
}

void Robots::setDebugVariable1(int msg)
{
    debug1 = QString::asprintf("Angle is: %d", msg);
}

void Robots::setDebugVariable2(int msg)
{
    debug2 = QString::asprintf("Distance is: %d", msg);
}

/**
	* Show error message (mainly for showing that bot doesn't conform to .cfg file)
	*/
void Robots::showError(const QString &string, const QString &name)
{
    if (showerror && useUI) {
        QString msg = "The bot ";
        msg += name;
        msg += "\nbreaks the following rule in the config file: \n";
        msg += string;
        //        msg += QString::number(team);
        QMessageBox::information(nullptr, "Message from the bot", msg);
        return;
    }
}

void Robots::writeRadio(int sig)
{
    devicelist[ourradiodev]->doSpecial(sig, 0);
}

int Robots::memorySize()
{
    return ramdevice->returnsize();
}

/**
	* Add interrupt to one of bots CPU:s
	*/
void Robots::addInterrupt(int inter)
{
    if (inter > 255) {
        return;
    }
    int x;
    for (x = 0; x < 32; x++) {
        if (devicelist[x]->type() == CPUtype) {
            if (devicelist[x]->specialValue() == CPUwithint) {
                devicelist[x]->addInputPort(0, inter);
                break;
            }
        }
    }
}

/**
	* Returns debugstructure from first CPU
	*/
struct DebugContents Robots::debugContents()
{
    int x;
    for (x = 0; x < 32; x++) {
        if (devicelist[x]->type() == 9) {
            return devicelist[x]->debugContents();
            break;
        }
    }

    return DebugContents(); // return empty debugcontents
}

/**
 * Returns number of CPUs
 */
int Robots::cpuCount()
{
    int num = 0;
    for (int x = 0; x < 32; x++) {
        if (devicelist[x] && (devicelist[x]->type() == 9)) {
            num++;
        }
    }
    return num;
}

/**
 * Returns debugstructure from all CPUs
 */

QVector<struct DebugContents> *Robots::allDebugContents()
{
    QVector<DebugContents> *dc = new QVector<DebugContents>;
    for (int x = 0; x < 32; x++) {
        if (devicelist[x] && (devicelist[x]->type() == 9)) {
            dc->push_back(devicelist[x]->debugContents());
        }
    }
    return dc;
}
/**
    * Object is seen by radar...
    */
int Robots::returnRadar()
{
    return currentradar;
}

/**
    * When object is scanned, check if we have a scandetector...
    */
void Robots::objectScanned(int intensity, int dir)
{
    int x;
    for (x = 0; x < 32; x++) {
        if (devicelist[x]->type() == 11) {
            devicelist[x]->doSpecial(intensity, dir);
            break;
        }
    }
}

void Robots::setRadar(int x)
{
    currentradar = x;
}

/**
    * When dumpRAM button in debugwindow is pressed
    * this function opens a file and dumps RAM
    * contents to it
    */
void Robots::dumpRam()
{
    for (int x = 0; x < 256; x++) {
        QString fname = "BBdump";
        fname += QString::number(x);
        fname += ".bin";
        QFile f(fname);
        if (!f.exists()) {
            if (f.open(QIODevice::WriteOnly)) {
                for (int y = 0; y < ramdevice->returnsize(); y++) {
                    f.putChar(ramdevice->getbyte(y));
                }
                f.close();
            }
            break;
        }
    }
}
