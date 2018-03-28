/***************************************************************************
                          debugwindow.h  -  description
                             -------------------
    begin                : Fri Nov 3 2000
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

#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>
#include "debugcontents.h"
#include <QLabel>
#include <QString>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QPointer>
/**
	* Shows some debug info (register contents, some mem contents) for the
	* first CPU in the bot
  *@author Andreas Agorander
  */

class DebugWindow : public QDialog
{

    Q_OBJECT

public:
    DebugWindow(QPlainTextEdit *Medit, int *dbl, int *dbm);
    ~DebugWindow();
    void updatedata(struct DebugContents);
    void addint(QString &, uint16_t);

private slots:
    void distsignal();

private:
    QLabel *registercontents[9]; //AX,BX,CX,DX,SP,BP,SI,DI,IP
    QLabel *flagcontents[4]; //equal,above,below,intenabled
    QLabel *memcontents[4];
    QPlainTextEdit *execlines;
    QPushButton *dumpmemb;

    int *debuglines;
    int *debugmem;
    QPointer<QPlainTextEdit> maineditor;

signals:
    void dumpmem();
};

#endif
