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

PixButton::PixButton (QString text,int pix,QWidget *parent)
        : QPushButton (text, parent)
{
    whichpix = pix;
    tex = text;
}

PixButton::~PixButton()
{
}

void PixButton::paintEvent (QPaintEvent *event)
{
//    {
//        QPushButton::paintEvent(event);
//        QStylePainter p(this);
//        QStyleOptionButton option;
//        initStyleOption(&option);
//        p.drawControl(QStyle::CE_PushButton, option);
//    }
//    QPushButton::paintEvent(event);
    QPainter paint(this);
    paint.fillRect(rect().marginsRemoved(QMargins(2, 2, 2, 2)), QBrush(PixmapHolder::getpm(whichpix)));
    paint.drawText (isDown() ? 1 : 0, isDown() ? 1 : 0, width(), height(), Qt::AlignCenter, tex);
}
