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
#include <QPixmap>
#include <QDebug>

static QPixmap *pm[20];

PixmapHolder::PixmapHolder()
{
}

PixmapHolder::~PixmapHolder()
{
}

void PixmapHolder::addpm (QString name,int num)
{
    pm[num] = new QPixmap (name);
    if (pm[num]->isNull()) {
        qWarning() << "Failed to load" << name;
    }
}

QPixmap & PixmapHolder::getpm (int num)
{
    if (pm[num]->isNull()) {
        qWarning() << "Queried for invalid pixmap" << num;
    }
    return *pm[num];
}

QPixmap * PixmapHolder::getpmp (int num)
{
    if (pm[num]->isNull()) {
        qWarning() << "Queried for invalid pixmap point" << num;
    }
    return pm[num];
}
