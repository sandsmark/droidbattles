/***************************************************************************
                          debugwindow.cpp  -  description
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

#include "debugwindow.h"

#include <QTextBlock>
#include <qmessagebox.h>
//Added by qt3to4:
#include <QLabel>

#include <QGridLayout>
#include <QVBoxLayout>
/**
	* Constructor, create GUI elements
	*/
DebugWindow::DebugWindow(QPlainTextEdit *Medit, int *dbl, int *dbm)
{
    QFont monoFont("Monospace");
    monoFont.setStyleHint(QFont::Monospace);
    setFont(monoFont);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    //	int x;

    registercontents[0] = new QLabel("ax :", this);
    registercontents[1] = new QLabel("bx :", this);
    registercontents[2] = new QLabel("cx :", this);
    registercontents[3] = new QLabel("dx :", this);
    registercontents[4] = new QLabel("bp :", this);
    registercontents[5] = new QLabel("sp :", this);
    registercontents[6] = new QLabel("si :", this);
    registercontents[7] = new QLabel("di :", this);
    registercontents[8] = new QLabel("ip :", this);

    flagcontents[0] = new QLabel("Equal :", this);
    flagcontents[1] = new QLabel("Above :", this);
    flagcontents[2] = new QLabel("Below :", this);
    flagcontents[3] = new QLabel("Interrupt Enable :", this);

    memcontents[0] = new QLabel("Mem contents @ip :", this);
    memcontents[1] = new QLabel("Mem contents @sp :", this);
    memcontents[2] = new QLabel("Mem contents @si :", this);
    memcontents[3] = new QLabel("Mem contents @di :", this);

    execlines = new QPlainTextEdit(this);

    dumpmemb = new QPushButton("Dump mem-map", this);

    QGridLayout *l = new QGridLayout;
    for (int i = 0; i < 9; i++) {
        l->addWidget(registercontents[i], i / 3, i % 3);
    }
    mainLayout->addLayout(l);

    l = new QGridLayout;
    l->addWidget(flagcontents[0], 0, 0);
    l->addWidget(flagcontents[1], 0, 1);
    l->addWidget(flagcontents[2], 1, 0);
    l->addWidget(flagcontents[3], 1, 1);
    mainLayout->addLayout(l);

    mainLayout->addWidget(memcontents[0]);
    mainLayout->addWidget(memcontents[1]);
    mainLayout->addWidget(memcontents[2]);
    mainLayout->addWidget(memcontents[3]);
    mainLayout->addWidget(execlines);
    mainLayout->addWidget(dumpmemb);

    maineditor = Medit;
    debuglines = dbl;
    debugmem = dbm;

    QObject::connect(dumpmemb, SIGNAL(clicked()), this, SLOT(distsignal()));
}

DebugWindow::~DebugWindow()
{
}

/**
	* Updates the debug info
	*/
void DebugWindow::updatedata(struct DebugContents contents)
{
    QString tmp;
    registercontents[0]->setText("ax :" + QString::number(contents.ax));
    registercontents[1]->setText("bx :" + QString::number(contents.bx));
    registercontents[2]->setText("cx :" + QString::number(contents.cx));
    registercontents[3]->setText("dx :" + QString::number(contents.dx));
    registercontents[4]->setText("bp :" + QString::number(contents.bp));
    registercontents[5]->setText("sp :" + QString::number(contents.sp));
    registercontents[6]->setText("si :" + QString::number(contents.si));
    registercontents[7]->setText("di :" + QString::number(contents.di));
    registercontents[8]->setText("ip :" + QString::number(contents.ip));

    tmp = "Mem contents @ip :";
    int x;
    for (x = 0; x < 4; x++) {
        tmp += " " + QString::number(contents.ipcontents[x]);
    }
    tmp += " ip:";
    for (x = 4; x < 9; x++) {
        tmp += " " + QString::number(contents.ipcontents[x]);
    }
    memcontents[0]->setText(tmp);

    tmp = "Mem contents @sp :";

    for (x = 0; x < 4; x++) {
        tmp += " " + QString::number(contents.spcontents[x]);
    }
    tmp += " sp:";
    for (x = 4; x < 9; x++) {
        tmp += " " + QString::number(contents.spcontents[x]);
    }
    memcontents[1]->setText(tmp);

    tmp = "Mem contents @si :";

    for (x = 0; x < 4; x++) {
        tmp += " " + QString::number(contents.sicontents[x]);
    }
    tmp += " si:";
    for (x = 4; x < 9; x++) {
        tmp += " " + QString::number(contents.sicontents[x]);
    }
    memcontents[2]->setText(tmp);

    tmp = "Mem contents @di :";

    for (x = 0; x < 4; x++) {
        tmp += " " + QString::number(contents.dicontents[x]);
    }
    tmp += " di:";
    for (x = 4; x < 9; x++) {
        tmp += " " + QString::number(contents.dicontents[x]);
    }
    memcontents[3]->setText(tmp);

    tmp = "Equal Flag: ";
    if ((contents.flags & 0x8000) == 0x8000) {
        tmp += "1";
    } else {
        tmp += "0";
    }
    flagcontents[0]->setText(tmp);

    tmp = "Above Flag: ";
    if ((contents.flags & 0x2000) == 0x2000) {
        tmp += "1";
    } else {
        tmp += "0";
    }
    flagcontents[1]->setText(tmp);

    tmp = "Below Flag: ";
    if ((contents.flags & 0x4000) == 0x4000) {
        tmp += "1";
    } else {
        tmp += "0";
    }
    flagcontents[2]->setText(tmp);

    tmp = "Interrupt Enable: ";
    if ((contents.flags & 0x0400) == 0x0400) {
        tmp += "1";
    } else {
        tmp += "0";
    }
    flagcontents[3]->setText(tmp);

    if (maineditor) {
        execlines->clear();
        for (x = 0; x < 30; x++) {
            int z = contents.execmem[x];
            if (z >= 0) {
                int x2;
                for (x2 = 0; x2 < 4095; x2++) {
                    if (debugmem[x2] == z) {
                        execlines->appendPlainText(maineditor->document()->findBlockByLineNumber(debuglines[x2]).text());
                        break;
                    }
                }
            }
        }
    }

    update();
}

void DebugWindow::distsignal()
{
    emit(dumpmem());
}
