/***************************************************************************
                          screenobject.h  -  description
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

#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include <qpixmap.h>
#include <qstring.h>
#include "commonsymbols.h"
#include <qobject.h>
#include "debugcontents.h"
/**The base-class for all independent objects on the battlefield that are "active"
  *@author Andreas Agorander
  */

class ScreenObject : public QObject
{

    Q_OBJECT

public:

    ScreenObject();
    virtual ~ScreenObject();
    virtual int setPosition (double X,double Y);
    void changeDirection (int Z);
    void changeSpeed (int Z);
    int xPos();
    int yPos();
    int direction();
    int speed();
    int number();

    virtual void addScreenObject (int X,int Y,int dir,int type,int arg1=0,
                               int arg2=0, void *arg3=0);
    virtual int readDevicePort (unsigned char port);
    virtual void writeDevicePort (unsigned char port,unsigned short value);
    virtual int execute();
    virtual void eraseObject (QPixmap *buffer);
    virtual void drawObject (QPixmap *buffer, int opt = 0);
    virtual int objectHit (int type,int strength);
    virtual void objectScanned (int intensity,int dir);
    virtual int collisionType();
    virtual int collisionStrength();
    virtual int type();
    virtual int writetoBattleArea (int bot,int dev,int choice,int arg1,int arg2);
    virtual int writeToDevice (int dev, int action, int value);
    virtual int size();
    virtual QString getDebugMessage1();
    virtual QString getDebugMessage2();
    virtual void setDebugVariable1 (int);
    virtual void setDebugVariable2 (int);
    virtual void setFuel (int);
    virtual void setSpeed (int);
    virtual int fuel();
    virtual int armor();
    virtual int memorySize();
    virtual void writeRadio (int);
    virtual bool areaExplosionAffects();
    int armorval;
    int team();
    virtual void addInterrupt (int);
    virtual struct DebugContents debugContents();
    virtual int returnRadar();
    virtual int collisionId();
    void changeHeat (int x);
    virtual void setRadar (int x);
    int heat();
    void setHeat (int x);
    int owner();
    void sendMessage (char *msg);
    virtual void dumpRam();
    QString myfile;
    QPixmap & getgfx();

protected:

    int upcount;
    int fuelval;
    int heatval;
    double Xpos;
    double Ypos;
    int oldX;
    int oldY;
    int m_direction;
    int m_speed;
    QPixmap *graphics;
    QPixmap *erasegfx;
    bool canbehit;
    int mynum;
    int m_size;
    QString debug1;
    QString debug2;
    bool showextragfx;
    int maxx;
    int maxy;
    int m_team;
    int noncollid;
    int myowner;

    bool useUI;

private	slots:

    void setextragfx (bool x);

signals:

    void armorchanged (int x);
    void fuelchanged (int x,int y);
    void messagechanged (char *msg);

};

#endif
