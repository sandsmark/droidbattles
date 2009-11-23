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

class screenobject : public QObject
{

    Q_OBJECT

public:

    screenobject();
    virtual ~screenobject();
    virtual int changepos (double X,double Y);
    void changedir (int Z);
    void changespeed (int Z);
    const int getXpos();
    const int getYpos();
    const int getdir();
    const int getspeed();
    const int getnum();
    virtual void addscrobject (int X,int Y,int dir,int type,int arg1=0,
                               int arg2=0, void *arg3=0);
    virtual int getdevport (unsigned char port);
    virtual void putdevport (unsigned char port,unsigned short value);
    virtual int execute();
    virtual void eraseobject (QWidget *buffer);
    virtual void showobject (QWidget *buffer,int opt = 0);
    virtual int objhit (int type,int strength);
    virtual void objscanned (int intensity,int dir);
    virtual int getcollisiontype();
    virtual int getcollisionstrength();
    virtual int returntype();
    virtual int iodevtobatt (int bot,int dev,int choice,int arg1,int arg2);
    virtual int iodevtodev (int dev, int action, int value);
    virtual int getsize();
    virtual const char* getdebug1();
    virtual const char* getdebug2();
    virtual void setdebug1 (int);
    virtual void setdebug2 (int);
    virtual void setfuel (int);
    virtual void setspeed (int);
    virtual int getfuel();
    virtual int getarmor();
    virtual int getmem();
    virtual void receiveradio (int);
    virtual bool areaexplosionaffects();
    int armorval;
    int getteam();
    virtual void addinterrupt (int);
    virtual struct debugcontents returndbgcont();
    virtual int returnradar();
    virtual int getcollid();
    void changeheat (int x);
    virtual void setradar (int x);
    int getheat();
    void setheat (int x);
    int getowner();
    void sendmsg (char *msg);
    virtual void dumpRAM();
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
    int direction;
    int speed;
    QPixmap *graphics;
    QPixmap *erasegfx;
    bool canbehit;
    int mynum;
    int size;
    QString debug1;
    QString debug2;
    bool showextragfx;
    int maxx;
    int maxy;
    int team;
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
