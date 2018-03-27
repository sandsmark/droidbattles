/***************************************************************************
                          createbot.h  -  description
                             -------------------
    begin                : Sun Apr 2 2000
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

#ifndef CREATEBOT_H
#define CREATEBOT_H

#include <qwidget.h>
#include <qmessagebox.h>
#include <QMenu>
#include <qmenubar.h>
#include <QScrollArea>
#include <qstring.h>
#include <QFileDialog>
#include <qfile.h>
#include <qpushbutton.h>
#include <qpixmap.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QScopedPointer>
#include "confstruct.h"
#include "pixmapholder.h"
/**The base widget for the bot editor, contains an editor, an assembler
  *@author Andreas Agorander
  */

class DevChoice;
class MyQMultiLineEdit;
class QPlainTextEdit;
class QComboBox;
class Instruction;
class BattleArea;
class StartsBatt;

class CreateBot : public QWidget
{
    Q_OBJECT

public:

    CreateBot();
    ~CreateBot();
    void closeEvent (QCloseEvent *e);
    void error (const QString &msg, int line);
    void addint (QString & str,int integ);
    int devnum (int sort,int num);

private slots:
    void newb();
    void open();
    void save();
    void saveas();
    void closec();
    void cut();
    void copy();
    void paste();
    void choosepic();
    bool startquick();
    void runquick();
    void confquick();
    void stopconf();
    void checkconf();
    void devchanged();
    void scrollview (int);
    void setEdittxtScrollValue (int i);
    void setShowlatencyScrollValue (int i);
    void onHelpAction();
    void onAssembleAction();

signals:
    void helpRequested(const QString &word);

private:
    bool loadFile(const QString &filename);
    bool assemble();

    unsigned int RAMAMOUNT;
    QMessageBox *ermsg;
    MyQMultiLineEdit *edittxt;
    QScrollArea *scroller;
    QPlainTextEdit *showlatency;
    DevChoice* devices[32];
    QMenu *File;
    QMenu *Edit;
    QMenu *Assemble;
    QMenu *Config;
    QMenu *tests;
    QMenuBar *menb;
    QComboBox *amountRAM;
    QScrollArea *scrvw;
    QWidget *boxarea;
    QString botname;
    char *dirname;
    QPushButton *gfxbutton;
    QPixmap gfx;
//		QPixmap *backpm;
    BattleArea *batt;
    StartsBatt *qc;
    ConfStruct curconfig;
    bool changed;
    int instrlatency[256];
    int debuglines[4096];
    int debugmem[4096];
    int debugentry;
    QString m_fileName;
};
#include "devchoice.h"

#endif
