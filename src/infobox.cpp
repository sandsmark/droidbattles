/***************************************************************************
                          infobox.cpp  -  description
                             -------------------
    begin                : Wed Feb 28 2001
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

#include "infobox.h"
//Added by qt3to4:
#include <QCloseEvent>
#include <QLabel>

InfoBox::InfoBox(const QString &msg, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::Dialog);
    text = new QLabel(msg, this);
    text->setGeometry(0, 0, 0, 0);
    text->resize(text->sizeHint());
    resize(text->sizeHint());
    show();
}

InfoBox::~InfoBox()
{
}

void InfoBox::closeEvent(QCloseEvent * /*unused*/)
{
    delete this;
}
