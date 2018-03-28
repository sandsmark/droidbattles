/***************************************************************************
                          infobox.h  -  description
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

#ifndef INFOBOX_H
#define INFOBOX_H

#include <QDialog>
#include <qlabel.h>
//Added by qt3to4:
#include <QCloseEvent>

/**
  *@author Andreas Agorander
  */

class InfoBox : public QDialog
{
public:
    InfoBox(QString msg, QWidget *parent = 0);
    ~InfoBox();
    void closeEvent(QCloseEvent *e);

private:
    QLabel *text;
};

#endif
