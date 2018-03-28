/***************************************************************************
                          pixbutton.cpp  -  description
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

#include "pixbutton.h"
#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionButton>

PixButton::PixButton (QString text,QWidget *parent)
        : QPushButton (text, parent)
{
    tex = text;
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

PixButton::~PixButton()
{
}

void PixButton::paintEvent (QPaintEvent *)
{
    // Draw our own background and text
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    if (!hasFocus()) {
        paint.setPen(QColor(255, 255, 255, 192));
    }

    const QRect r(rect().marginsRemoved(QMargins(2, 2, 2, 2)));
    paint.setBrush(QBrush(PixmapHolder::getpm(PixmapHolder::BackButton)));
    paint.drawRoundedRect(r, 3, 3);

    if (isDown()) {
        paint.fillRect(r, QColor(0, 0, 0, 32));
    } else if (hasFocus()) {
        paint.setPen(QPen(QColor(128, 128, 192, 192), 2));
        paint.setBrush(QColor(255, 255, 255, 64));
        paint.drawRoundedRect(r, 3, 3);
    }

    paint.setPen(Qt::black);
    paint.drawText (0, 0, width(), height(), Qt::AlignCenter, tex);
}
