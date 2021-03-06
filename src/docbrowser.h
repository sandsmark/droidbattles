/***************************************************************************
                          docbrowser.h  -  description
                             -------------------
    begin                : Sat Jan 6 2001
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

#ifndef DOCBROWSER_H
#define DOCBROWSER_H

#include <QTextBrowser>
#include <qstring.h>
//Added by qt3to4:
#include <QCloseEvent>

/**
  *@author Andreas Agorander
  */

class DocBrowser : public QTextBrowser
{

public:
    DocBrowser(const QString &src);
    ~DocBrowser() override;
    void closeEvent(QCloseEvent *e) override;

public slots:
    void lookUp(const QString &keyword);
};

#endif
