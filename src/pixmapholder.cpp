/***************************************************************************
                          pixmapholder.cpp  -  description
                             -------------------
    begin                : Thu Mar 1 2001
    copyright            : (C) 2001 by Andreas Agorander
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

#include "pixmapholder.h"
//Added by qt3to4:
#include <QDebug>
#include <QPixmap>

static QPixmap *pm[20];
bool PixmapHolder::initialized = false;

PixmapHolder::PixmapHolder()
{
}

PixmapHolder::~PixmapHolder()
{
}

void PixmapHolder::addpm(const QString &name, PixmapId num)
{
    pm[num] = new QPixmap(name);
    if (pm[num]->isNull()) {
        qWarning() << "Failed to load" << name;
    }
}

QPixmap &PixmapHolder::getpm(PixmapId num)
{
    if (!initialized) {
        load();
    }

    if (pm[num]->isNull()) {
        qWarning() << "Queried for invalid pixmap" << num;
    }
    return *pm[num];
}

QPixmap *PixmapHolder::getpmp(PixmapId num)
{
    if (!initialized) {
        load();
    }

    if (pm[num]->isNull()) {
        qWarning() << "Queried for invalid pixmap point" << num;
    }
    return pm[num];
}

void PixmapHolder::load()
{
    //Load all pixmaps used by the application
    addpm(":/images/mainmenu.png", PixmapHolder::MainMenu);
    addpm(":/images/backbutton.png", PixmapHolder::BackButton);
    addpm(":/images/metal.png", PixmapHolder::Metal);
    addpm(":/images/metalback2.png", PixmapHolder::MetalBackground);
    addpm(":/images/radarmissile.bmp", PixmapHolder::RadarMissile);
    addpm(":/images/chaff.bmp", PixmapHolder::Chaff);
    addpm(":/images/mine.xpm", PixmapHolder::Mine);
    addpm(":/images/missile.xpm", PixmapHolder::Missile);
    addpm(":/images/rocket.xpm", PixmapHolder::Rocket);

    initialized = true;
}
