/***************************************************************************
                          createbot.cpp  -  description
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

#include "createbot.h"
#include "myqmultilineedit.h"
#include <qcombobox.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QMenu>
#include <QCloseEvent>
#include <QScrollBar>
#include "commonsymbols.h"
#include "instruktion.h"
#include <qregexp.h>
#include <QTextStream>
#include <QTextBlock>
#include <QSettings>
#include "battlearea.h"
#include "startsbatt.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardPaths>

/**
	* Constructor Inits GUI
	*/
CreateBot::CreateBot()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose);
    edittxt = new MyQMultiLineEdit (this);
    edittxt->setFont (QFont ("helvetica",9));
    showlatency = new QPlainTextEdit (this);
    showlatency->setFont (QFont ("helvetica",9));
    connect (edittxt->verticalScrollBar(),SIGNAL (valueChanged (int)),
             this,SLOT (setShowlatencyScrollValue (int)));
    connect (showlatency->verticalScrollBar(),SIGNAL (valueChanged (int)),
             this,SLOT (setEdittxtScrollValue (int)));
    showlatency->setMaximumWidth(100);
    showlatency->setReadOnly (true);

    menb = new QMenuBar (this);
    mainLayout->addWidget(menb);

    File = menb->addMenu("&File");

    QAction *action = File->addAction("&New", this, SLOT (newb()));
    action->setShortcut(QKeySequence::New);
    action = File->addAction("&Open", this, SLOT (open()));
    action->setShortcut(QKeySequence::Open);
    action = File->addAction("&Save", this, SLOT (save()));
    action->setShortcut(QKeySequence::Save);
    action = File->addAction("S&ave As", this, SLOT (saveas()));
    action->setShortcut(QKeySequence::SaveAs);
    action = File->addAction("&Close", this, SLOT (closec()));
    action->setShortcut(QKeySequence::Close);

    Edit = menb->addMenu("&Edit");
    action = Edit->addAction("&Copy", this, SLOT (copy()));
    action->setShortcut(QKeySequence::Copy);
    action = Edit->addAction("C&ut", this, SLOT (cut()));
    action->setShortcut(QKeySequence::Cut);
    action = Edit->addAction("&Paste", this, SLOT (paste()));
    action->setShortcut(QKeySequence::Paste);

    Assemble = menb->addMenu("&Assemble");
    action = Assemble->addAction ("&Assemble", this, SLOT (onAssembleAction()));
    action->setShortcut(QKeySequence::Refresh);

    tests = menb->addMenu("&Tests");
    action = tests->addAction("&Quick battle", this, SLOT (startquick()));
    action->setShortcut(QKeySequence("Ctrl+R"));

    action = tests->addAction("&Autolaunch battle", this, SLOT (runquick()));
    action->setShortcut(QKeySequence("Ctrl+Shift+R"));

    tests->addAction("&Config quick battle", this, SLOT (confquick()));
    tests->addAction("C&heck against config", this, SLOT (checkconf()));

    QMenu *helpMenu = menb->addMenu("&Help");
    action = helpMenu->addAction("&Context help", this, SLOT (onHelpAction()));
    action->setShortcut(QKeySequence::HelpContents);


    scrvw = new QScrollArea (this);
    boxarea = new QWidget();
    boxarea->setLayout(new QVBoxLayout);
    scrvw->setWidgetResizable(true);
    scrvw->setWidget(boxarea);
    scrvw->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    amountRAM = new QComboBox (boxarea);
    amountRAM->setEditable(false);
    amountRAM->addItem ("1k RAM");
    amountRAM->addItem ("2k RAM");
    amountRAM->addItem ("4k RAM");
    amountRAM->addItem ("8k RAM");
    amountRAM->addItem ("16k RAM");
    amountRAM->addItem ("24k RAM");
    amountRAM->addItem ("32k RAM");
    amountRAM->addItem ("48k RAM");
    amountRAM->addItem ("64k RAM");
    boxarea->layout()->addWidget(amountRAM);
    boxarea->layout()->setMargin(0);


    int x;
    for (x=0; x<32; x++)
    {
        devices[x] = new DevChoice (this,boxarea,x);
        boxarea->layout()->addWidget(devices[x]);
        QObject::connect (devices[x],SIGNAL (change()),this,
                          SLOT (devchanged()));
    }

    QHBoxLayout *editorLayout = new QHBoxLayout;
    editorLayout->addWidget(showlatency);
    editorLayout->addWidget(edittxt);
    editorLayout->addWidget(scrvw);
    mainLayout->addLayout(editorLayout);

    dirname = new char[100];
    QDir botsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/droidbattles/";
    if (!botsPath.exists()) {
        botsPath.mkpath(botsPath.absolutePath());
    }
    botname = botsPath.absoluteFilePath("unnamed");

    gfxbutton = new QPushButton (this);
    gfxbutton->setIcon(QIcon(gfx));
    mainLayout->addWidget(gfxbutton);

    QObject::connect (gfxbutton, SIGNAL (clicked()), this,
                      SLOT (choosepic()));
    changed = false;

    instrlatency[0] = 1;
    instrlatency[1] = 1;
    instrlatency[2] = 1;
    instrlatency[3] = 2;
    instrlatency[4] = 2;
    instrlatency[5] = 2;
    instrlatency[6] = 2;
    instrlatency[7] = 2;
    instrlatency[8] = 2;
    instrlatency[9] = 2;
    instrlatency[10] = 2;
    instrlatency[11] = 1;
    instrlatency[12] = 1;
    instrlatency[13] = 2;
    instrlatency[14] = 2;
    instrlatency[15] = 2;
    instrlatency[16] = 2;
    instrlatency[17] = 1;
    instrlatency[18] = 1;
    instrlatency[19] = 1;
    instrlatency[20] = 1;
    instrlatency[21] = 1;
    instrlatency[22] = 1;
    instrlatency[23] = 2;
    instrlatency[24] = 2;
    instrlatency[25] = 2;
    instrlatency[26] = 2;
    instrlatency[27] = 1;
    instrlatency[28] = 1;
    instrlatency[29] = 1;
    instrlatency[30] = 1;
    instrlatency[31] = 2;
    instrlatency[32] = 2;
    instrlatency[33] = 2;
    instrlatency[34] = 2;
    instrlatency[35] = 1;
    instrlatency[36] = 1;
    instrlatency[37] = 2;
    instrlatency[38] = 2;
    instrlatency[39] = 2;
    instrlatency[40] = 2;
    instrlatency[41] = 1;
    instrlatency[42] = 2;
    instrlatency[43] = 2;
    instrlatency[44] = 1;
    instrlatency[45] = 2;
    instrlatency[46] = 2;
    instrlatency[47] = 1;
    instrlatency[48] = 1;
    instrlatency[49] = 2;
    instrlatency[50] = 2;
    instrlatency[51] = 2;
    instrlatency[52] = 2;
    instrlatency[53] = 1;
    instrlatency[54] = 1;
    instrlatency[55] = 2;
    instrlatency[56] = 2;
    instrlatency[57] = 2;
    instrlatency[58] = 2;
    instrlatency[59] = 5;
    instrlatency[60] = 1;
    instrlatency[61] = 1;
    instrlatency[62] = 1;
    instrlatency[63] = 1;
    instrlatency[64] = 1;
    instrlatency[65] = 1;
    instrlatency[66] = 1;
    instrlatency[67] = 1;
    instrlatency[68] = 1;
    instrlatency[69] = 1;
    instrlatency[70] = 1;
    instrlatency[71] = 1;
    instrlatency[72] = 2;
    instrlatency[73] = 2;
    instrlatency[74] = 3;
    instrlatency[75] = 3;
    instrlatency[76] = 1;
    instrlatency[77] = 1;
    instrlatency[78] = 1;
    instrlatency[79] = 1;
    instrlatency[80] = 1;
    instrlatency[81] = 1;
    instrlatency[82] = 1;
    instrlatency[83] = 1;
    instrlatency[84] = 1;
    instrlatency[85] = 1;
    instrlatency[86] = 1;
    instrlatency[87] = 1;
    instrlatency[88] = 1;
    instrlatency[89] = 1;
    instrlatency[90] = 1;
    instrlatency[91] = 1;
    instrlatency[92] = 2;
    instrlatency[93] = 2;
    instrlatency[94] = 2;
    instrlatency[95] = 2;
    instrlatency[96] = 2;
    instrlatency[97] = 2;
    instrlatency[98] = 2;
    instrlatency[99] = 2;
    instrlatency[100] = 2;
    instrlatency[101] = 2;
    instrlatency[102] = 2;
    instrlatency[103] = 2;
    instrlatency[104] = 1;
    instrlatency[105] = 1;
    instrlatency[106] = 1;
    instrlatency[107] = 1;
    instrlatency[108] = 2;
    instrlatency[109] = 2;
    instrlatency[110] = 2;
    instrlatency[111] = 2;
    instrlatency[112] = 2;
    instrlatency[113] = 2;
    instrlatency[114] = 2;
    instrlatency[115] = 2;
    instrlatency[116] = 2;
    instrlatency[117] = 2;
    instrlatency[118] = 2;
    instrlatency[119] = 2;
    instrlatency[120] = 1;
    instrlatency[121] = 1;
    instrlatency[122] = 2;
    instrlatency[123] = 2;
    instrlatency[124] = 2;
    instrlatency[125] = 2;
    instrlatency[126] = 1;
    instrlatency[127] = 1;
    instrlatency[128] = 2;
    instrlatency[129] = 2;
    instrlatency[130] = 2;
    instrlatency[131] = 2;
    instrlatency[132] = 4;
    instrlatency[133] = 5;
    instrlatency[134] = 1;
    instrlatency[135] = 1;
    instrlatency[136] = 8;
    instrlatency[137] = 7;
    instrlatency[138] = 1;
    instrlatency[139] = 1;
    instrlatency[140] = 1;
    instrlatency[141] = 1;
    instrlatency[142] = 2;
    instrlatency[143] = 2;
    instrlatency[144] = 0;
    instrlatency[145] = 0;
    instrlatency[146] = 0;
    instrlatency[147] = 100;
    instrlatency[148] = 100;
    instrlatency[149] = 1;
    instrlatency[150] = 1;
    instrlatency[151] = 1;
    instrlatency[152] = 1;
    instrlatency[153] = 1;
    instrlatency[154] = 1;
    instrlatency[155] = 1;
    instrlatency[156] = 2;
    instrlatency[157] = 2;
    instrlatency[158] = 2;
    instrlatency[159] = 2;
    instrlatency[160] = 2;
    instrlatency[161] = 2;
    instrlatency[162] = 2;
    instrlatency[163] = 2;
    instrlatency[164] = 2;
    instrlatency[165] = 2;
    instrlatency[166] = 2;
    instrlatency[167] = 2;
    instrlatency[168] = 1;
    instrlatency[169] = 1;
    instrlatency[170] = 1;
    instrlatency[171] = 1;
    instrlatency[172] = 2;
    instrlatency[173] = 2;
    instrlatency[174] = 2;
    instrlatency[175] = 2;
    instrlatency[176] = 2;
    instrlatency[177] = 2;
    instrlatency[178] = 2;
    instrlatency[179] = 2;
    instrlatency[180] = 2;
    instrlatency[181] = 2;
    instrlatency[182] = 2;
    instrlatency[183] = 2;
    instrlatency[184] = 1;
    instrlatency[185] = 1;
    instrlatency[186] = 1;
    instrlatency[187] = 1;
    instrlatency[188] = 2;
    instrlatency[189] = 2;
    instrlatency[190] = 2;
    instrlatency[191] = 2;
    instrlatency[192] = 2;
    instrlatency[193] = 2;
    instrlatency[194] = 2;
    instrlatency[195] = 2;
    instrlatency[196] = 2;
    instrlatency[197] = 2;
    instrlatency[198] = 2;
    instrlatency[199] = 2;
    instrlatency[200] = 1;
    instrlatency[201] = 1;
    instrlatency[202] = 1;
    instrlatency[203] = 1;
    instrlatency[204] = 1;
    instrlatency[205] = 1;
    instrlatency[206] = 1;
    instrlatency[207] = 1;
    instrlatency[208] = 1;
    instrlatency[209] = 1;
    instrlatency[210] = 1;
    instrlatency[211] = 1;
    instrlatency[212] = 1;
    instrlatency[213] = 1;
    instrlatency[214] = 1;
    instrlatency[215] = 1;
    instrlatency[216] = 1;
    instrlatency[217] = 1;
    instrlatency[218] = 1;
    instrlatency[219] = 1;
    instrlatency[220] = 1;
    instrlatency[221] = 1;
    instrlatency[222] = 1;
    instrlatency[223] = 1;
    instrlatency[224] = 2;
    instrlatency[225] = 4;
    instrlatency[226] = 5;
    instrlatency[227] = 1;
    instrlatency[228] = 1;
    instrlatency[229] = 1;
    instrlatency[230] = 13;
    instrlatency[231] = 13;
    instrlatency[232] = 8;
    instrlatency[233] = 8;
    instrlatency[234] = 2;
    instrlatency[235] = 2;
    instrlatency[236] = 5;
    instrlatency[237] = 0;
    instrlatency[238] = 1;
    instrlatency[239] = 1;
    instrlatency[240] = 1;
    instrlatency[241] = 1;
    instrlatency[242] = 1;

    QSettings settings;
    settings.beginGroup("editor");
    QString filename = settings.value("lastfile").toString();
    if (!filename.isEmpty()) {
        loadFile(filename);
    }
}

/**
	* Loads the bot graphics
	*/
void CreateBot::choosepic()
{
    QSettings settings;

    QString filename = QFileDialog::getOpenFileName (this, tr("Select picture file"), settings.value("LastPicPath").toString(), "*.png");
    if (!filename.isEmpty()) {
        settings.setValue("LastPicPath", filename);
        gfx.load (filename);
    }

    gfxbutton->setIcon(QIcon(gfx));

    changed = true;
}

/**
	* Destructor, Asks if bot should be saved before closing
	*/
CreateBot::~CreateBot()
{
    delete []dirname;
//	delete backpm;
}

/**
	* Deletes window (if user clicksthe X )
	*/
void CreateBot::closeEvent (QCloseEvent*)
{
    if (changed || edittxt->document()->isModified())
    {
        switch (QMessageBox::information (this, "BattleBots",
                                          "The document contains unsaved work\n"
                                          "Do you want to save it before exiting?",
                                          "&Save and exit", "&Exit",0,1))
        {
        case 0:
            save();
            break;
        case 1: // Don't Save clicked or Alt-D pressed
            break;
        }
    }
}

/**
	* Creates an empty bot
	*/
void CreateBot::newb()
{
    if (changed || edittxt->document()->isModified())
    {
        switch (QMessageBox::information (this, "BattleBots",
                                          "The document contains unsaved work\n"
                                          "Do you want to save it before creating new?",
                                          "&Save and New", "&New",0,1))
        {
        case 0:
            save();
            break;
        case 1: // Don't Save clicked or Alt-D pressed
            break;
        }
    }
    edittxt->clear();
    int x;
    for (x=0; x<32; x++)
    {
        devices[x]->setitem (0);
        devices[x]->levelchosen (0);
        devices[x]->setarg1 (0);
    }
    amountRAM->setCurrentIndex(0);

    botname = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/droidbattles/unnamed";
    gfx = QPixmap(0,0);
    changed = false;
    edittxt->document()->setModified(false);
}

/**
	* Opens a bot source file, and lets the user choose the file.
	* TODO: Check if the contents of the file is correctly
	*       formatted
	* TODO: Add "are you sure" dialog if the current bot loaded
	*       is unsaved
	*/
void CreateBot::open()
{

    if (changed || edittxt->document()->isModified())
    {
        switch (QMessageBox::information (this, "BattleBots",
                                          "The document contains unsaved work\n"
                                          "Do you want to save it before opening?",
                                          "&Save and open", "&Open",0,1))
        {
        case 0:
            save();
            break;
        case 1: // Don't Save clicked or Alt-D pressed
            break;
        }
    }

    QSettings settings;
    settings.beginGroup("editor");
    QString filename = settings.value("lastfile").toString();
    if (filename.isEmpty()) {
        filename = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/droidbattles/";
    }

    filename = QFileDialog::getOpenFileName (this, tr("Select bot source file"), filename, "*.basm");
    if (filename.isEmpty()) {
        return;
    }

    if (loadFile(filename)) {
        settings.setValue("lastfile", filename);
    }
}

bool CreateBot::loadFile(const QString &filename)
{
    if (filename.isEmpty()) {
        return false;
    }

    QFile f (filename);
    if (!f.open (QIODevice::ReadOnly)) {
        error ("Couldn't open file!",0);
        return false;
    }
    m_fileName.clear();

    QString tline;
    QTextStream s (&f);
    unsigned short i;
    //		char v;
    s >> tline;
    s >> i;
    amountRAM->setCurrentIndex (i);
    showlatency->clear();
    int x;
    for (x=0; x<32; x++)
    {
        s >> tline;
        s >> i;
        devices[x]->setitem (i);
        s >> i;
        devices[x]->levelchosen (i);
        s >> tline;
        devices[x]->setarg1 (tline);
    }
    tline = s.readLine();
    tline = s.readLine();
    edittxt->clear();
    while (!s.atEnd()) {
        tline = s.readLine();
        edittxt->appendPlainText (tline);
    }
    f.close();
    botname = filename;

    QString pngName = QFileInfo(m_fileName).absoluteDir().filePath(QFileInfo(botname).baseName() + ".png");
    QFile f2 (pngName);
    if (f2.exists())
        gfx.load (pngName);
    else
        gfx = QPixmap();

    changed = false;
    edittxt->document()->setModified(false);

    m_fileName = filename;

    return true;
}

/**
	* Saves changes to file
	*/
void CreateBot::save()
{
    if (m_fileName.isEmpty()) {
        saveas();
        return;
    }

    QFile f (m_fileName);
    if (!f.open (QIODevice::WriteOnly))
    {
        saveas();
        return;
    }
    QTextStream s (&f);
    s << "RAM: " << amountRAM->currentIndex() << endl <<  endl;
    int x;
    for (x=0; x<32; x++)
        s << "DEVICE: " << devices[x]->getitem() << " " <<
             devices[x]->getlevel() << " " << devices[x]->getarg1() << endl;
    s << endl;
    QString tempdata = edittxt->document()->toPlainText();
    s << tempdata;
    f.close();

    if (gfx.width() > 31 && gfx.height() > 31)
    {
        QString pngPath = QFileInfo(m_fileName).absoluteDir().filePath(botname + ".png");
        gfx.save (pngPath);
    }
    changed = false;
    edittxt->document()->setModified(false);
}

/**
	* Saves the current bot to a bot source file
	* (and lets the user choose file)
	* TODO: If the user specifies a file without
	*       .basm at the end, add that end.
	*/
void CreateBot::saveas()
{
    QString filename = QFileDialog::getSaveFileName (this, tr("Save bot source file"), QFileInfo(m_fileName).absolutePath(), "*.basm");
    if (!filename.isEmpty())
    {
        QFile f (filename);
        if (!f.open (QIODevice::WriteOnly))
        {
            error ("Couldn't open file!",0);
            return;
        }
        QTextStream s (&f);
        s << "RAM: " << amountRAM->currentIndex() << endl <<  endl;
        int x;
        for (x=0; x<32; x++)
            s << "DEVICE: " << devices[x]->getitem() << " " <<
            devices[x]->getlevel() << " " << devices[x]->getarg1() << endl;
        s << endl;
        QString tempdata = edittxt->document()->toPlainText();
        s << tempdata;
        f.close();
    }
    botname = filename;
    if (gfx.width() > 31 && gfx.height() > 31)
    {
        QString pngPath = QFileInfo(filename).absoluteDir().filePath(QFileInfo(botname).baseName() + ".png");
        gfx.save (pngPath);
    }
    changed = false;
    edittxt->document()->setModified(false);
}

/**
	* TODO: add "are you sure" dialog
	*/
void CreateBot::closec()
{
    close();
}


void CreateBot::copy()
{
    edittxt->copy();
}

void CreateBot::cut()
{
    edittxt->cut();
}

void CreateBot::paste()
{
    edittxt->paste();
}

void CreateBot::devchanged()
{
    changed = true;
}

/**
	* Makes a binary file out of the
	* current bot.
	* TODO: Document this beast (or rewrite it from scratch)
	*/
bool CreateBot::assemble()
{
    int i;

    //Memory where the file contents are stored during assemble
    unsigned char mem[65536+256];
    for (i=0; i<65536; i++)
        mem[i] = 0;

    //comb/QString array where forward referencing jumps are remembered
    QString jumpnames[512];
    unsigned short jvalues[512];
    bool existj[512];
    //comb/QString array where label locations, consts and vars are remembered
    QString names[2048];
    unsigned short nvalues[2048];
    bool existn[2048];
    //unresolved symbols go here (in case of later declaration)
    QString unresn[4096];
    unsigned short unrespos[4096];
    bool unresexist[4096];
    short unresbits[4096];
    short unresline[4096];
    int numsortdec[NUMDEV*2+1];


    mem[0] = 'B';

    //Put in the amount of RAM
    mem[1] = amountRAM->currentIndex();
    if (mem[1] == 0)
        RAMAMOUNT = 1024;
    if (mem[1] == 1)
        RAMAMOUNT = 2048;
    if (mem[1] == 2)
        RAMAMOUNT = 4096;
    if (mem[1] == 3)
        RAMAMOUNT = 8192;
    if (mem[1] == 4)
        RAMAMOUNT = 16384;
    if (mem[1] == 5)
        RAMAMOUNT = 24576;
    if (mem[1] == 6)
        RAMAMOUNT = 32768;
    if (mem[1] == 7)
        RAMAMOUNT = 49152;
    if (mem[1] == 8)
        RAMAMOUNT = 65536;
    //Put in the devices chosen
    for (i=0; i< (NUMDEV*2+1); i++)
        numsortdec[i] = 0;

    //Zero alot of vars
    for (i=0; i<511; i++)
    {
        jumpnames[i] = "";
        jvalues[i] = 0;
        existj[i] = false;
    }
    for (i=0; i<2047; i++)
    {
        names[i] = "";
        nvalues[i] = 0;
        existn[i] = false;
    }
    for (i=0; i<4095; i++)
    {
        unresn[i] = "";
        unrespos[i] = 0;
        unresexist[i] = false;
        debugmem[i] = -1;
        debuglines[i] = -1;
    }
    debugentry = 0;

    for (i=0; i<32; i++)
    {
        mem[2+i*6] = devices[i]->getitem();
        mem[3+i*6] = devices[i]->getlevel();
        mem[4+i*6] = devices[i]->getarg1();
        switch (mem[2+i*6])
        {
        case 1 :
            names[i*8] = "CPU";
            names[i*8] += QString::number (numsortdec[1]);
            names[i*8] += "_GetXSize";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "CPU";
            names[i*8+1] += QString::number (numsortdec[1]);
            names[i*8+1] += "_GetYSize";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "CPU";
            names[i*8+2] += QString::number (numsortdec[1]);
            names[i*8+2] += "_GetBattleType";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+3] = "CPU";
            names[i*8+3] += QString::number (numsortdec[1]);
            names[i*8+3] += "_GetMyTeam";
            nvalues[i*8+3] = i*4+3;
            existn[i*8+3] = true;

            numsortdec[1]++;

            break;
        case 2 :

            names[i*8] = "Engine";
            names[i*8] += QString::number (numsortdec[2]);
            names[i*8] += "_GetThrust";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Engine";
            names[i*8+1] += QString::number (numsortdec[2]);
            names[i*8+1] += "_GetSpeed";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+4] = "Engine";
            names[i*8+4] += QString::number (numsortdec[2]);
            names[i*8+4] += "_SetThrust";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Engine";
            names[i*8+5] += QString::number (numsortdec[2]);
            names[i*8+5] += "_SetReverseThrust";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            numsortdec[2]++;

            break;
        case 3 :
            names[i*8] = "Steering";
            names[i*8] += QString::number (numsortdec[3]);
            names[i*8] += "_GetDir";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Steering";
            names[i*8+1] += QString::number (numsortdec[3]);
            names[i*8+1] += "_GetWantedDir";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "Steering";
            names[i*8+2] += QString::number (numsortdec[3]);
            names[i*8+2] += "_GetXPos";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+3] = "Steering";
            names[i*8+3] += QString::number (numsortdec[3]);
            names[i*8+3] += "_GetYPos";
            nvalues[i*8+3] = i*4+3;
            existn[i*8+3] = true;

            names[i*8+4] = "Steering";
            names[i*8+4] += QString::number (numsortdec[3]);
            names[i*8+4] += "_AdjustWantedDir";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Steering";
            names[i*8+5] += QString::number (numsortdec[3]);
            names[i*8+5] += "_SetDir";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Steering";
            names[i*8+6] += QString::number (numsortdec[3]);
            names[i*8+6] += "_AdjustCurrentDir";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[3]++;

            break;
        case 4 :

            names[i*8+4] = "Plasmagun";
            names[i*8+4] += QString::number (numsortdec[4]);
            names[i*8+4] += "_Shoot";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[4]++;

            break;
        case 5 :
            names[i*8] = "Armor";
            names[i*8] += QString::number (numsortdec[5]);
            names[i*8] += "_GetArmor";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Armor";
            names[i*8+1] += QString::number (numsortdec[5]);
            names[i*8+1] += "_GetHeat";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+4] = "Armor";
            names[i*8+4] += QString::number (numsortdec[5]);
            names[i*8+4] += "_SetCollIntEnabled";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Armor";
            names[i*8+5] += QString::number (numsortdec[5]);
            names[i*8+5] += "_SetArmorIntEnabled";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Armor";
            names[i*8+6] += QString::number (numsortdec[5]);
            names[i*8+6] += "_SetArmorIntLevel";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            names[i*8+7] = "Armor";
            names[i*8+7] += QString::number (numsortdec[5]);
            names[i*8+7] += "_SetHeatIntLevel";
            nvalues[i*8+7] = i*4+3;
            existn[i*8+7] = true;

            numsortdec[5]++;


            break;
        case 6 :

            names[i*8] = "Scanner";
            names[i*8] += QString::number (numsortdec[6]);
            names[i*8] += "_GetScanDistance";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Scanner";
            names[i*8+1] += QString::number (numsortdec[6]);
            names[i*8+1] += "_GetScanAccuracy";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "Scanner";
            names[i*8+2] += QString::number (numsortdec[6]);
            names[i*8+2] += "_GetScanWidth";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+3] = "Scanner";
            names[i*8+3] += QString::number (numsortdec[6]);
            names[i*8+3] += "_GetScanInfo";
            nvalues[i*8+3] = i*4+3;
            existn[i*8+3] = true;

            names[i*8+4] = "Scanner";
            names[i*8+4] += QString::number (numsortdec[6]);
            names[i*8+4] += "_Scan";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Scanner";
            names[i*8+5] += QString::number (numsortdec[6]);
            names[i*8+5] += "_SetScanWidth";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Scanner";
            names[i*8+6] += QString::number (numsortdec[6]);
            names[i*8+6] += "_SelectReturn";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            names[i*8+7] = "Scanner";
            names[i*8+7] += QString::number (numsortdec[6]);
            names[i*8+7] += "_SetSensitivity";
            nvalues[i*8+7] = i*4+3;
            existn[i*8+7] = true;

            numsortdec[6]++;

            break;
        case 7 :
            names[i*8] = "Fuel";
            names[i*8] += QString::number (numsortdec[7]);
            names[i*8] += "_GetFuel";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+4] = "Fuel";
            names[i*8+4] += QString::number (numsortdec[7]);
            names[i*8+4] += "_SetFuelIntEnabled";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Fuel";
            names[i*8+5] += QString::number (numsortdec[7]);
            names[i*8+5] += "_SetFuelIntLevel";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            numsortdec[7]++;

            break;
        case 8 :
            names[i*8] = "Chaff";
            names[i*8] += QString::number (numsortdec[8]);
            names[i*8] += "_GetDebris";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+4] = "Chaff";
            names[i*8+4] += QString::number (numsortdec[8]);
            names[i*8+4] += "_ReleaseDebris";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[8]++;

            break;
        case 9 :
            names[i*8] = "Turret";
            names[i*8] += QString::number (numsortdec[9]);
            names[i*8] += "_GetOffset";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Turret";
            names[i*8+1] += QString::number (numsortdec[9]);
            names[i*8+1] += "_GetWantedOffset";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+4] = "Turret";
            names[i*8+4] += QString::number (numsortdec[9]);
            names[i*8+4] += "_SetOffset";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Turret";
            names[i*8+5] += QString::number (numsortdec[9]);
            names[i*8+5] += "_AdjustOffset";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Turret";
            names[i*8+6] += QString::number (numsortdec[9]);
            names[i*8+6] += "_AdjustCurrentOffset";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[9]++;

            break;
        case 10 :
            names[i*8] = "ScanWarn";
            names[i*8] += QString::number (numsortdec[10]);
            names[i*8] += "_GetNumScans";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "ScanWarn";
            names[i*8+1] += QString::number (numsortdec[10]);
            names[i*8+1] += "_GetScanDir";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "ScanWarn";
            names[i*8+2] += QString::number (numsortdec[10]);
            names[i*8+2] += "_GetScanIntensity";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+4] = "ScanWarn";
            names[i*8+4] += QString::number (numsortdec[10]);
            names[i*8+4] += "_ZeroCounter";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[10]++;

            break;
        case 11 :

            names[i*8] = "Timer";
            names[i*8] += QString::number (numsortdec[11]);
            names[i*8] += "_GetTime";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Timer";
            names[i*8+1] += QString::number (numsortdec[11]);
            names[i*8+1] += "_GetIntTime";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "Timer";
            names[i*8+2] += QString::number (numsortdec[11]);
            names[i*8+2] += "_GetIntEnabled";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+4] = "Timer";
            names[i*8+4] += QString::number (numsortdec[11]);
            names[i*8+4] += "_SetTime";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Timer";
            names[i*8+5] += QString::number (numsortdec[11]);
            names[i*8+5] += "_SetIntTime";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Timer";
            names[i*8+6] += QString::number (numsortdec[11]);
            names[i*8+6] += "_SetIntEnabled";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[11]++;

            break;
        case 12 :
            names[i*8] = "Shield";
            names[i*8] += QString::number (numsortdec[12]);
            names[i*8] += "_GetShieldEnabled";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+4] = "Shield";
            names[i*8+4] += QString::number (numsortdec[12]);
            names[i*8+4] += "_SetShieldEnabled";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[12]++;

            break;
        case 13 :

            break;
        case 14 :

            names[i*8] = "Radio";
            names[i*8] += QString::number (numsortdec[14]);
            names[i*8] += "_GetNumMsgs";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Radio";
            names[i*8+1] += QString::number (numsortdec[14]);
            names[i*8+1] += "_GetMsg";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+2] = "Radio";
            names[i*8+2] += QString::number (numsortdec[14]);
            names[i*8+2] += "_GetMyNum";
            nvalues[i*8+2] = i*4+2;
            existn[i*8+2] = true;

            names[i*8+4] = "Radio";
            names[i*8+4] += QString::number (numsortdec[14]);
            names[i*8+4] += "_SetReceiver";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Radio";
            names[i*8+5] += QString::number (numsortdec[14]);
            names[i*8+5] += "_SendMsg";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Radio";
            names[i*8+6] += QString::number (numsortdec[14]);
            names[i*8+6] += "_SetMsgIntEnabled";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[14]++;

            break;
        case 15 :
            names[i*8+4] = "Chiller";
            names[i*8+4] += QString::number (numsortdec[15]);
            names[i*8+4] += "_SetExtraCooling";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[15]++;

            break;
        case 16 :
            names[i*8+4] = "Cloak";
            names[i*8+4] += QString::number (numsortdec[16]);
            names[i*8+4] += "_EnableCloak";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[16]++;

            break;
        case 17 :
            names[i*8] = "Minelayer";
            names[i*8] += QString::number (numsortdec[17]);
            names[i*8] += "_GetMines";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+4] = "Minelayer";
            names[i*8+4] += QString::number (numsortdec[17]);
            names[i*8+4] += "_LayMine";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            numsortdec[17]++;

            break;
        case 18 :
            names[i*8] = "Missile";
            names[i*8] += QString::number (numsortdec[18]);
            names[i*8] += "_GetLoadTime";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+4] = "Missile";
            names[i*8+4] += QString::number (numsortdec[18]);
            names[i*8+4] += "_SetBootPos";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Missile";
            names[i*8+5] += QString::number (numsortdec[18]);
            names[i*8+5] += "_SetStackPos";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Missile";
            names[i*8+6] += QString::number (numsortdec[18]);
            names[i*8+6] += "_FireMissile";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[18]++;

            break;
        case 19 :
            names[i*8] = "Beam";
            names[i*8] += QString::number (numsortdec[19]);
            names[i*8] += "_GetDir";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Beam";
            names[i*8+1] += QString::number (numsortdec[19]);
            names[i*8+1] += "_GetLength";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+4] = "Beam";
            names[i*8+4] += QString::number (numsortdec[19]);
            names[i*8+4] += "_FireBeam";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Beam";
            names[i*8+5] += QString::number (numsortdec[19]);
            names[i*8+5] += "_SetBeamDir";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            names[i*8+6] = "Beam";
            names[i*8+6] += QString::number (numsortdec[19]);
            names[i*8+6] += "_SetBeamLength";
            nvalues[i*8+6] = i*4+2;
            existn[i*8+6] = true;

            numsortdec[19]++;

            break;
        case 20 :
            names[i*8] = "Rocket";
            names[i*8] += QString::number (numsortdec[20]);
            names[i*8] += "_GetReadiness";
            nvalues[i*8] = i*4;
            existn[i*8] = true;

            names[i*8+1] = "Rocket";
            names[i*8+1] += QString::number (numsortdec[20]);
            names[i*8+1] += "_GetDistance";
            nvalues[i*8+1] = i*4+1;
            existn[i*8+1] = true;

            names[i*8+4] = "Rocket";
            names[i*8+4] += QString::number (numsortdec[20]);
            names[i*8+4] += "_SetDistance";
            nvalues[i*8+4] = i*4;
            existn[i*8+4] = true;

            names[i*8+5] = "Rocket";
            names[i*8+5] += QString::number (numsortdec[20]);
            names[i*8+5] += "_FireRocket";
            nvalues[i*8+5] = i*4+1;
            existn[i*8+5] = true;

            numsortdec[20]++;

            break;
        }
    }

    int posinmem=0;
    QString tempstring;
    QString curline;
    QString token[16];
    QString curmnem;
    bool tunres[16];
    short unresnum[16];
    for (i=0; i<15; i++)
        token[i] = "      ";
    bool exist[16];
    bool ok=false;
    Instruction::Types type[16];
    unsigned char value[16][2];
    int tpos;
    int bits;
    showlatency->clear();

    QString outputName = QFileInfo(m_fileName).absoluteDir().filePath(QFileInfo(botname).baseName() + ".bot");
    QFile f (outputName);
    for (int linenum = 0; linenum < edittxt->document()->lineCount(); linenum++) {
        curline = edittxt->document()->findBlockByLineNumber(linenum).text();   //Load one line
        if (curline.isEmpty()) {
            showlatency->appendPlainText(" ");
            continue;
        }

        QString insertstr = "";
        for (i=0; i<15; i++)
        {
            value[i][0]=0;
            value[i][1]=0;
            exist[i]=false;
            tunres[i]=false;
            token[i]="";
            type[i]=Instruction::None;
            unresnum[i]=0;
        }
        bits=0;

        //Chop of line comments and such
        tpos = curline.indexOf(QRegExp ("[;\\n\\r]"),0);
        tempstring = curline.left (tpos);
        curline = tempstring;
        tpos = curline.indexOf (QRegExp ("[a-zA-Z0-9_#:%@$]"),0);
        curline = curline.right (curline.length()-tpos);

        if (curline.length() <= 1)
        {
            showlatency->appendPlainText(" ");
            continue;
        }

        // divide into tokens
        /////////////////////
        // take the tokens
        const QStringList tokens = curline.split(QRegExp ("[\\s,\\x0]"), QString::SkipEmptyParts);
        for (i=0; i<tokens.length(); i++) {
            token[i] = tokens[i];
            exist[i] = true;
        }

        //Assign types and values to all tokens
        //types: 0-none
        //       1-label
        //	   2-mnemonic
        //	   3-value
        //	   4-memadress (@value)
        //	   5-register
        //       6-const declaration
        //	   7-org
        //	   8-vardeclaration
        //	   9-cpuboot
        //	  10-cpustack
        //	  11-db
        //	  12-bit-identifier
        //	  13-@register
        ///////////////////////////////////////
        //Check if the first token is a label
        if (token[0].left (1) == QString (":"))
        {
            if (token[0].length() <= 1)
            {
                error ("Expected: name of label",linenum);
                return false;
            }

            type[0] = Instruction::Label;
            int x;
            for (x=0; x<2047; x++)
            {
                if (existn[x] == false) break;
            }
            names[x] = token[0].right (token[0].length()-1);
            nvalues[x] = posinmem;
            existn[x] = true;
            if (exist[1]==true)
            {
                error ("Expected: only one token",linenum);
                return false;
            }
        }
        //Check for vardeclaration
        if (type[0] == Instruction::None && token[0].left (1) == QString ("#"))
        {
            if (token[0].length() > 1)
            {
                type[0] = Instruction::ConstDecl;
                int x;
                for (x=0; x<2047; x++)
                {
                    if (existn[x] == false) break;
                }
                names[x] = token[0].right (token[0].length()-1);
                nvalues[x] = posinmem;
                existn[x] = true;

                if (exist[1] == true)
                {
                    error ("Expected: only one token",linenum);
                    return false;
                }
            }
            else
            {
                error ("Expected: name of variable", linenum);
                return false;
            }
        }

        //Check for const declarations
        if (type[0] == Instruction::None && token[0].left (1) == QString ("$"))
        {
            if (token[0].length() > 1)
            {
                type[0] = Instruction::VarDecl;
                int x;
                for (x=0; x<2047; x++)
                {
                    if (existn[x] == false) break;
                }
                names[x] = token[0].right (token[0].length()-1);
                existn[x] = true;
                if (exist[1]==true)
                {
                    nvalues[x] = token[1].toInt();
                    //							if( nvalues[x] < 0 )nvalues[x] += 65536;
                }
                else
                {
                    error ("Expected: value of constant",linenum);
                    return false;
                }
                if (exist[2] == true)
                {
                    error ("Expected: only two tokens",linenum);
                    return false;
                }
            }
            else
            {
                error ("Expected: name of constant", linenum);
                return false;
            }
        }
        //Check for db
        if (type[0] == Instruction::None && token[0] == QString ("db"))
        {
            type[0] = Instruction::Db;
            for (i=1; i<15; i++)
            {
                if (exist[i] == true)
                {
                    tpos = token[i].toInt (&ok);
                    if (ok == false)
                    {
                        int x;
                        for (x=0; x<2047; x++)
                        {
                            if (existn[x] == true)
                            {
                                if (token[i] == names[x])
                                {
                                    mem[posinmem+256] = nvalues[x];
                                    posinmem++;
                                }
                            }
                        }
                    }
                    else
                    {
                        //								if( tpos < 0 )tpos += 129;
                        mem[posinmem+256] = tpos;
                        posinmem++;
                    }
                }
            }
        }
        //Check for dw
        if (type[0] == Instruction::None && token[0] == QString ("dw"))
        {
            type[0] = Instruction::Db;
            for (i=1; i<15; i++)
            {
                if (exist[i] == true)
                {
                    tpos = token[i].toInt (&ok);
                    if (ok == false)
                    {
                        int x;
                        for (x=0; x<2047; x++)
                        {
                            if (existn[x] == true)
                            {
                                if (token[i] == names[x])
                                {
                                    mem[posinmem+256] = nvalues[x]%256;
                                    mem[posinmem+257] = int (nvalues[x]/256);
                                    posinmem += 2;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (tpos < 0) tpos += 65536;
                        mem[posinmem+256] = tpos%256;
                        mem[posinmem+257] = int (tpos/256);
                        posinmem += 2;
                    }
                }
            }
        }


        //Check for %org
        if (type[0] == Instruction::None && token[0] == QString ("%org"))
        {
            type[0] = Instruction::Offset;
            if (exist[1] == true)
            {
                bool isplus = token[1].startsWith('+');
                QString comp = token[1];
                if (isplus) {
                    comp.remove(0, 1);
                }
                tpos = token[1].toInt (&ok);
                if (ok == false)
                {
                    //If it's a symbol
                    int x;
                    for (x=0; x<2047; x++)
                    {
                        if (existn[x] == true)
                        {
                            if (token[1] == names[x])
                            {
                                posinmem = nvalues[x];
                            }
                        }
                        else
                        {
                            error ("Unknown symbol",linenum);
                            return false;
                        }
                    }

                }
                else
                {
                    //If it's a direct value
                    if (isplus)   //if( token[1].left( 1 )=="+" )
                        posinmem += tpos;
                    else
                        posinmem = tpos;
                }
            }
            else
            {
                error ("Expected: value for org" ,linenum);
                return false;
            }
        }

        //Check for %CPUboot
        if (type[0] == Instruction::None && token[0] == QString ("%CPUboot"))
        {
            type[0] = Instruction::CpuBoot;
            if (!exist[1]) {
                error ("Expected: number of CPU device",linenum);
                return false;
            }

            tpos = token[1].toInt (&ok);
            if (ok == false)
            {
                int x;
                for (x=0; x<2047; x++)
                {
                    if (!existn[x])
                    {
                        error ("Unknown symbol",linenum);
                        return false;
                    }

                    if (token[1] == names[x])
                    {
                        if (nvalues[x]<32 && mem[nvalues[x]*6+2] == 1)
                        {
                            mem[nvalues[x]*6+4] = posinmem%256;
                            mem[nvalues[x]*6+5] = int (posinmem/256);
                        }
                        else
                        {
                            //Code for error in dev-value
                            error ("Value must be the number of a CPU device",
                                   linenum);
                            return false;
                        }
                    }
                }
            }
            else
            {
                //Code for non-symbol value
                if (tpos >= 32 || mem[tpos*6+2] != 1)
                {
                    error ("Value must be the number of a CPU device",linenum);
                    return false;
                }

                mem[tpos*6+4] = posinmem%256;
                mem[tpos*6+5] = int (posinmem/256);
            }
        }
        //Check for %CPUstack
        if (type[0] == Instruction::None && token[0] == QString ("%CPUstack"))
        {
            type[0] = Instruction::CpuStack;
            if (!exist[1])
            {
                error ("Expected: number of CPU device",linenum);
                return false;
            }

            tpos = token[1].toInt (&ok);
            if (!ok)
            {
                int x;
                for (x=0; x<2047; x++)
                {
                    if (!existn[x])
                    {
                        error ("Unknown symbol",linenum);
                        return false;
                    }
                    if (token[1] != names[x]) {
                        continue;
                    }

                    if (nvalues[x] >= 32 || mem[nvalues[x]*6+2] != 1)
                    {
                        //Code for error in dev-value
                        error ("Value must be the number of a CPU device",
                               linenum);
                        return false;
                    }

                    mem[nvalues[x]*6+6] = posinmem%256;
                    mem[nvalues[x]*6+7] = int (posinmem/256);
                }
            }
            else
            {
                //Code for non-symbol value
                if (tpos >= 32 || mem[tpos*6+2] != 1)
                {
                    error ("Value must be the number of a CPU device",linenum);
                    return false;
                }

                mem[tpos*6+6] = posinmem%256;
                mem[tpos*6+7] = int (posinmem/256);
            }
        }

        //Check for %interrupt
        if (type[0] == Instruction::None && token[0] == QString ("%interrupt"))
        {
            type[0] = Instruction::Interrupt;
            if (!exist[1])
            {
                error ("Expected: number of interrupt",linenum);
                return false;
            }

            tpos = token[1].toInt (&ok);
            if (ok == false)
            {
                int x;
                for (x=0; x<2047; x++)
                {
                    if (!existn[x])
                    {
                        error ("Unknown symbol",linenum);
                        return false;
                    }

                    if (token[1] == names[x])
                    {
                        if (nvalues[x]<256)
                        {
                            mem[ (RAMAMOUNT+256- (nvalues[x]*2+2)) ] = posinmem%256;
                            mem[ (RAMAMOUNT+256- (nvalues[x]*2+1)) ] =
                                    int (posinmem/256);
                        }
                        else
                        {
                            //Code for error in dev-value
                            error ("Value must be lower than 256",linenum);
                            return false;
                        }
                    }
                }
            }
            else
            {
                //Code for non-symbol value
                if (tpos > 255)
                {
                    error ("Value must be lower than 256",linenum);
                    return false;
                }

                mem[ (RAMAMOUNT+256- (tpos*2+2)) ] = posinmem%256;
                mem[ (RAMAMOUNT+256- (tpos*2+1)) ] = int (posinmem/256);
            }
        }

        //Assign as mnemonic
        if (type[0] == Instruction::None)
        {
            type[0] = Instruction::Mnemonic;
            curmnem = token[0];
        }
        //If mnemonic Assign types to all other tokens
        if (type[0] == Instruction::Mnemonic)
        {

            //Check for register
            for (i=1; i<4; i++)
            {
                if (exist[i] == true && type[i] == Instruction::None)
                {
                    if (token[i] == QString ("ax"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = ax;
                        bits = 16;
                    }
                    if (token[i] == "bx")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = bx;
                        bits = 16;
                    }
                    if (token[i] == "cx")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = cx;
                        bits = 16;
                    }
                    if (token[i] == "dx")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = dx;
                        bits = 16;
                    }
                    if (token[i] == "sp")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = sp;
                        bits = 16;
                    }
                    if (token[i] == "bp")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = bp;
                        bits = 16;
                    }
                    if (token[i] == "si")
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = si;
                        bits = 16;
                    }
                    if (token[i] == QString ("di"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = di;
                        bits = 16;
                    }
                    if (token[i] == QString ("eip"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = eip;
                        bits = 16;
                    }
                    if (token[i] == QString ("flags"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = 0;
                        bits = 16;
                    }
                    if (token[i] == QString ("ah"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = ah;
                        bits = 8;
                    }
                    if (token[i] == QString ("al"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = al;
                        bits = 8;
                    }
                    if (token[i] == QString ("bh"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = bh;
                        bits = 8;
                    }
                    if (token[i] == QString ("bl"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = bl;
                        bits = 8;
                    }
                    if (token[i] == QString ("ch"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = ch;
                        bits = 8;
                    }
                    if (token[i] == QString ("cl"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = cl;
                        bits = 8;
                    }
                    if (token[i] == QString ("dh"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = dh;
                        bits = 8;
                    }
                    if (token[i] == QString ("dl"))
                    {
                        type[i] = Instruction::Register;
                        value[i][0] = dl;
                        bits = 8;
                    }
                }
            }

            //Check for @register
            for (i=1; i<3; i++)
            {
                if (exist[i] == true && type[i] == Instruction::None && token[i].left (1) == "@")
                {
                    QString tempstring = token[i].right (token[i].length()-1);
                    if (tempstring == QString ("ax"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = ax;
                    }
                    if (tempstring == QString ("bx"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = bx;
                    }
                    if (tempstring == QString ("cx"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = cx;
                    }
                    if (tempstring == QString ("dx"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = dx;
                    }
                    if (tempstring == QString ("sp"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = sp;
                    }
                    if (tempstring == QString ("bp"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = bp;
                    }
                    if (tempstring == QString ("si"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = si;
                    }
                    if (tempstring == QString ("di"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = di;
                    }
                    if (tempstring == QString ("eip"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = eip;
                    }
                    if (tempstring == QString ("flags"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = 0;
                    }
                    if (tempstring == QString ("ah"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = ah;
                    }
                    if (tempstring == QString ("al"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = al;
                    }
                    if (tempstring == QString ("bh"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = bh;
                    }
                    if (tempstring == QString ("bl"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = bl;
                    }
                    if (tempstring == QString ("ch"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = ch;
                    }
                    if (tempstring == QString ("cl"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = cl;
                    }
                    if (tempstring == QString ("dh"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = dh;
                    }
                    if (tempstring == QString ("dl"))
                    {
                        type[i] = Instruction::RegisterRef;
                        value[i][0] = dl;
                    }
                }
            }

            //Check for bit identifier
            for (i=1; i<3; i++)
            {
                if (exist[i] == true && type[i] == Instruction::None)
                {
                    if (token[i] == QString ("byte"))
                    {
                        type[i] = Instruction::BitId;
                        value[i][0] = 8;
                        bits = 8;
                    }
                    if (token[i] == QString ("word"))
                    {
                        type[i] = Instruction::BitId;
                        value[i][0] = 16;
                        bits = 16;
                    }
                }
            }


            //Check for @value
            for (i=1; i<3; i++)
            {
                if (exist[i] == true && type[i] == Instruction::None && token[i].left (1) == "@")
                {
                    QString tempstring = token[i].right (token[i].length()-1);
                    tpos = tempstring.toInt (&ok);
                    if (ok == false)
                    {
                        int x;
                        for (x=0; x<2047; x++)
                        {
                            if (existn[x] == true)
                            {
                                if (tempstring == names[x])
                                {
                                    value[i][0] = nvalues[x]%256;
                                    value[i][1] = nvalues[x]/256;
                                    type[i] = Instruction::MemAddress;
                                }
                            }
                        }
                        if (type[i] == Instruction::None)
                        {
                            type[i] = Instruction::MemAddress;
                            tunres[i] = true;
                            for (x=0; x<4095; x++)
                            {
                                if (unresexist[x] == false)
                                    break;
                            }
                            unresexist[x] = true;
                            unresn[x] = tempstring.right (tempstring.length());
                            unresline[x] = linenum;
                            unresnum[i] = x;
                        }
                    }
                    else
                    {
                        value[i][0] = tpos%256;
                        value[i][1] = tpos/256;
                        type[i] = Instruction::MemAddress;
                    }
                }
            }


            //Check for value
            for (i=1; i<4; i++)
            {
                if (exist[i] == true && type[i] == Instruction::None)
                {
                    QString comp = token[i];
                    if (comp.startsWith('+')) {
                        comp.remove(0, 1);
                    }
                    tpos = comp.toInt (&ok);
                    if (!ok)
                    {
                        int x;
                        for (x=0; x<2047; x++)
                        {
                            if (existn[x] == true)
                            {
                                if (comp == names[x])
                                {
                                    value[i][0] = nvalues[x]%256;
                                    value[i][1] = nvalues[x]/256;
                                    type[i] = Instruction::Value;
                                }
                            }
                        }
                        if (type[i] == Instruction::None)
                        {
                            type[i] = Instruction::Value;
                            tunres[i] = true;
                            for (x=0; x<4095; x++)
                            {
                                if (unresexist[x] == false)
                                    break;
                            }
                            unresexist[x] = true;
                            unresn[x] = token[i].right (tempstring.length());
                            unresline[x] = linenum;
                            unresnum[i] = x;
                        }
                    }
                    else
                    {
                        if (tpos<0) tpos += 65536;
                        value[i][0] = tpos%256;
                        value[i][1] = tpos/256;
                        type[i] = Instruction::Value;
                    }
                }
            }

            if ( (curmnem == "mov") && (type[1] == Instruction::Register) &&
                 (type[2] == Instruction::RegisterRef) && (type[3] == Instruction::Value))
            {
                value[1][1] = value[2][0];
                value[2][0] = value[3][0];
                i = 245;
                if (tunres[3] == true)
                {
                    error ("Sorry, this instruction can't use symbols not declared yet",
                           linenum);
                    return false;
                }
            } else if ( (curmnem == "mov") && (type[1] == Instruction::RegisterRef) &&
                        (type[2] == Instruction::Value) && (type[3] == Instruction::Register))
            {
                value[1][1] = value[2][0];
                value[2][0] =	value[3][0];
                i = 246;
                if (tunres[2] == true)
                {
                    error ("Sorry, this instruction can't use symbols not declared yet",
                           linenum);
                    return false;
                }
            } else {
                //Run through all available mnemonic-operand combinations available
                bool foundOp = false;
                for (i=0; i<245; i++) {
                    if (Instruction::instructions[i].checkmatch (curmnem,type[1],type[2],bits)) {
                        foundOp = true;
                        break;
                    }
                }
                if (!foundOp) {
                    //If not success return error
                    error ("Error: unknown mnemonic/operand combination",linenum);
                    return false;
                }
            }

            //If success write result
            mem[posinmem+256] = Instruction::instructions[i].getopcode();
            debugmem[debugentry] = posinmem;
            debuglines[debugentry++] = linenum;
            ///////////////
            int q;
            q = instrlatency[Instruction::instructions[i].getopcode() ];
            insertstr = QString::number (posinmem);
            insertstr += " : ";
            if (q < 200)
            {
                insertstr += QString::number (q);
            }
            if (i == 237)
                insertstr += "+X";
            ///////////////
            posinmem++;

            if (tunres[1] == true)
            {
                unrespos[ unresnum[1] ] = posinmem;
                if (Instruction::instructions[i].getarg1bits() > 0)
                {
                    unresbits[ unresnum[1] ] = 8;
                    posinmem++;
                }
                if (Instruction::instructions[i].getarg1bits() > 8)
                {
                    unresbits[ unresnum[1] ] = 16;
                    posinmem++;
                }
            }
            else
            {
                if (Instruction::instructions[i].getarg1bits() > 0)
                {
                    mem[posinmem+256] = value[1][0];
                    posinmem++;
                }
                if (Instruction::instructions[i].getarg1bits() > 8)
                {
                    mem[posinmem+256] = value[1][1];
                    posinmem++;
                }
            }

            if (tunres[2] == true)
            {
                unrespos[ unresnum[2] ] = posinmem;
                if (Instruction::instructions[i].getarg2bits() > 0)
                {
                    unresbits[ unresnum[2] ] = 8;
                    posinmem++;
                }
                if (Instruction::instructions[i].getarg2bits() > 8)
                {
                    unresbits[ unresnum[2] ] = 16;
                    posinmem++;
                }
            }
            else
            {
                if (Instruction::instructions[i].getarg2bits() > 0)
                {
                    mem[posinmem+256] = value[2][0];
                    posinmem++;
                }
                if (Instruction::instructions[i].getarg2bits() > 8)
                {
                    mem[posinmem+256] = value[2][1];
                    posinmem++;
                }
            }
        }

        if (insertstr.isEmpty()) {
            showlatency->appendPlainText(" ");
        } else {
            showlatency->appendPlainText(insertstr);
        }
    }
    mem[RAMAMOUNT+256] = 255;

    int i2;
    bool resolved[4096];

    for (i=0; i<4095; i++)
    {
        if (unresexist[i] == true)
        {
            resolved[i] = false;
            for (i2=0; i2<2047; i2++)
            {
                if (names[i2] == unresn[i])
                {
                    resolved[i] = true;
                    if (unresbits[i] == 16)
                    {
                        mem[ unrespos[i]+256 ] = nvalues[i2]%256;
                        mem[ unrespos[i]+257 ] = int (nvalues[i2]/256);
                    }
                    else
                    {
                        mem[ unrespos[i]+256 ] = nvalues[i2]%256;
                    }
                }
            }
            if (resolved[i] == false)
            {
                error ("Undeclared symbol",unresline[i]);
                return false;
            }
        }
    }

    //Open the binary file and write data
    if (f.open (QIODevice::WriteOnly))
    {
        QDataStream s (&f);
        s.writeBytes ( (char *) mem,RAMAMOUNT+256);
        f.close();
    }
    else
    {
        error ("Couldn't open output file " + f.fileName(),0);
        return false;
    }

    return true;
}

/**
	* Shows a message from the assembler and an OK button.
	* It also sets the current editing line to line
	*/
void CreateBot::error (const QString &msg, int line)
{
    QMessageBox::information (0,"Message from the almighty assembler", msg);
    if (line >= 0)	edittxt->setTextCursor(QTextCursor(edittxt->document()->findBlockByLineNumber(line)));
}

/**
	* Starts a battle between the current edited bot and the bots specified
	* in the quick battle config
	*/
bool CreateBot::startquick()
{
    if (!assemble()) {
        return false;
    }

    QString quickconf = QStandardPaths::locate(QStandardPaths::AppConfigLocation, "quick.conf");
    QFile f2 (quickconf);
    QString names[8];
    int xsize,ysize,numfights,lengthfights;
    bool ifteams;
    int teams[8];
    if (f2.exists() && f2.open (QIODevice::ReadOnly))
    {
        QTextStream s (&f2);
        QString temp;
        for (int x=0; x<8; x++)
        {
            s >> names[x];
            s >> temp;
            if (names[x] == QString ("fff"))
                names[x] = "";
            teams[x] = temp.toInt();
        }
        names[7] = QFileInfo(m_fileName).absoluteDir().filePath(QFileInfo(botname).baseName() + ".bot");
        s >> temp;
        ifteams = temp.toInt();
        s >> temp;
        numfights = temp.toInt();
        s >> temp;
        lengthfights = temp.toInt();
        s >> temp;
        xsize = temp.toInt();
        s >> temp;
        ysize = temp.toInt();
        f2.close();
    }
    else
    {
        error ("config file for quick battle not found",0);
        return false;
    }

    batt = new BattleArea ( names[0], names[1],
                            names[2], names[3],
                            names[4], names[5],
                            names[6], names[7],
                            numfights,lengthfights,xsize,ysize,ifteams,teams,
                            false,false,0,0,true, edittxt,&debuglines[0],
                            &debugmem[0]);
    batt->show();
    return true;
}

void CreateBot::runquick()
{
    if (startquick()) {
        batt->play();
    }
}

/**
	* Show window for editing quick battle config
	*/
void CreateBot::confquick()
{
    qc = new StartsBatt("quick.conf");
    connect (qc,&StartsBatt::cancelclicked,this,&CreateBot::stopconf);
    connect (qc,&StartsBatt::okclicked,this,&CreateBot::stopconf);
    qc->resize (300,570);
    qc->show();
}

/**
	* Delete config window
	*/
void CreateBot::stopconf()
{
    delete qc;
}

/**
	* Reports how the current bot compares to what's allowed in the
	* current config
	*/
void CreateBot::checkconf()
{
    QString confFileName = QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg");
    QFile f (confFileName);
    if (!f.open (QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Unable to find config", "No current configuration file found");
        return;
    }

    QTextStream s (&f);
    int x,y;

    QString dummy;

    int i;
//	bool ch;

    s >> dummy;
    s >> i;
    curconfig.maxdev = i;
    s >> dummy;
    s >> i;
    curconfig.maxcost = i;
    s >> dummy;
    s >> i;
    curconfig.maxram = i;
    s >> dummy;
    for (x=0; x<9; x++)
    {
        s >> i;
        curconfig.ramcost[x] = i;
    }
    for (x=0; x<NUMDEV; x++)
    {
        s >> dummy;
        s >> i;
        if (i == 1)
            curconfig.enabled[x] = true;
        else
            curconfig.enabled[x] = false;
        for (y=0; y<5; y++)
        {
            s >> i;
            curconfig.cost[y][x] = i;
            s >> dummy;
        }
    }
    f.close();

    int amountram;
    int totalcost;
    int numdev=0;
    int devicesenabled[32];
    for (int l=0; l<32; devicesenabled[l++]=0) {};

    amountram = amountRAM->currentIndex();
    totalcost = curconfig.ramcost[amountram];

    for (x=0; x<32; x++)
    {
        int dev = devices[x]->getitem();
        int devlev = devices[x]->getlevel();
        if (dev > 0)
        {
            if (curconfig.enabled[dev-1])
                devicesenabled[x] = 0;
            else
                devicesenabled[x] = 1;
            totalcost += curconfig.cost[devlev][dev-1];
            numdev++;
        }
    }

    QString resulttext;
    resulttext = "Checked bot against current.cfg :\n\n";

    resulttext += "RAM used: " + QString::number(amountram);
    resulttext += "  RAM allowed: " + QString::number(curconfig.maxram);

    resulttext += "\nDevices used: "  + QString::number(numdev);
    resulttext += "  Devices allowed: " + QString::number(curconfig.maxdev);

    resulttext += "\nTotal cost: " + QString::number(totalcost);
    resulttext += "  cost allowed: " + QString::number(curconfig.maxcost);

    for (x=0; x<32; x++)
    {
        if (devicesenabled[x] == 1)
        {
            resulttext += "\n\n device " + QString::number(x);
            resulttext += " is a disabled device";
        }
    }
    error ( resulttext, 0);
}

/**
	* Adds the number integ to the string str
	*/
void CreateBot::addint (QString & str,int integ)
{
    bool ready=false;
    QString temp;
    QString t2;
    while (!ready)
    {
        t2 = (integ%10+'0');
        temp = t2 + temp;
        integ /= 10;
        if (!integ) ready=true;
    }
    str += temp;
}

void CreateBot::scrollview (int)
{
//	showlatency->setYoffset( x );
}

int CreateBot::devnum (int sort,int num)
{
    int number=0;
    for (int x=0; x<num; x++)
    {
        if (devices[x]->getitem() == sort) number++;
    }
    return number;
}

void CreateBot::setEdittxtScrollValue (int i)
{
    if (!edittxt) {
        QMessageBox::critical(this, "Internal error", "Internal error.\nNo editor available!", QMessageBox::Ok);
        return;
    }
    edittxt->verticalScrollBar()->setValue (i);
}

void CreateBot::setShowlatencyScrollValue (int i)
{
    if (!showlatency) {
        QMessageBox::critical(this, "Internal error", "Internal error.\nNo latency view available!", QMessageBox::Ok);
        return;
    }

    showlatency->verticalScrollBar()->setValue (i);
}

void CreateBot::onHelpAction()
{
    QTextCursor cursor = edittxt->textCursor();

    cursor.select(QTextCursor::WordUnderCursor);
    QString currentWord = cursor.selectedText();

    // qtextcursor is dumb
    int selectEnd = cursor.selectionEnd();
    cursor.setPosition(cursor.selectionStart() - 1);
    cursor.setPosition(selectEnd, QTextCursor::KeepAnchor);
    QString maybe = cursor.selectedText();
    if (maybe.startsWith(":") || maybe.startsWith("#") || maybe.startsWith("$") || maybe.startsWith("@")) {
        emit helpRequested(maybe);
    } else {
        emit helpRequested(currentWord);
    }
}

void CreateBot::onAssembleAction()
{
    if (assemble()) {
        error ("Assemble successful",-1);
    }
}
