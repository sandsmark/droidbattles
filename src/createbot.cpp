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
#include <q3scrollview.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <Q3PopupMenu>
#include <QCloseEvent>
#include "commonsymbols.h"
#include "instruktion.h"
#include <qregexp.h>
#include <q3textstream.h>
#include <unistd.h>
#include "battlearea.h"
#include "quickconf.h"

/**
	* Constructor Inits GUI
	*/
createbot::createbot()
{
    setMinimumSize (600,500);
    edittxt = new myQMultiLineEdit (this);
    edittxt->setFont (QFont ("helvetica",9));
    edittxt->setGeometry (75,30,300,400);
    showlatency = new myQMultiLineEdit (this);
    showlatency->setFont (QFont ("helvetica",9));
    connect (edittxt->myVerticalScrollBar(),SIGNAL (valueChanged (int)),
             this,SLOT (setShowlatencyScrollValue (int)));
    connect (showlatency->myVerticalScrollBar(),SIGNAL (valueChanged (int)),
             this,SLOT (setEdittxtScrollValue (int)));
    showlatency->setGeometry (5,30,65,400);
    showlatency->setReadOnly (true);

    File = new Q3PopupMenu();
    File->insertItem ("&New", this, SLOT (newb()));
    File->insertItem ("&Open", this, SLOT (open()));
    File->insertItem ("&Save", this, SLOT (save()));
    File->insertItem ("S&ave As", this, SLOT (saveas()));
    File->insertItem ("&Close", this, SLOT (closec()));

    Edit = new Q3PopupMenu();
    Edit->insertItem ("&Copy", this, SLOT (copy()));
    Edit->insertItem ("C&ut", this, SLOT (cut()));
    Edit->insertItem ("&Paste", this, SLOT (paste()));

    Assemble = new Q3PopupMenu();
    Assemble->insertItem ("&Assemble", this, SLOT (assemble()));

    tests = new Q3PopupMenu();
    tests->insertItem ("&Quick battle", this, SLOT (startquick()));
    tests->insertItem ("&Config quick battle", this, SLOT (confquick()));
    tests->insertItem ("C&heck against config", this, SLOT (checkconf()));

    menb = new QMenuBar (this);
    menb->insertItem ("&File",File);
    menb->insertItem ("&Edit",Edit);
    menb->insertItem ("&Assemble",Assemble);
    menb->insertItem ("&Tests", tests);

    scrvw = new Q3ScrollView (this);
    scrvw->setGeometry (380,40,210,400);
    boxarea = new QWidget();
    boxarea->setGeometry (0,0,184,1720);
    scrvw->addChild (boxarea);

    int x;
    for (x=0; x<32; x++)
    {
        devices[x] = new devchoice (this,boxarea,"",x);
        devices[x]->setGeometry (10,60+x*50,170,50);
        devices[x]->show();
        QObject::connect (devices[x],SIGNAL (change()),this,
                          SLOT (devchanged()));
    }

    amountRAM = new QComboBox (FALSE,boxarea);
    amountRAM->insertItem ("1k RAM");
    amountRAM->insertItem ("2k RAM");
    amountRAM->insertItem ("4k RAM");
    amountRAM->insertItem ("8k RAM");
    amountRAM->insertItem ("16k RAM");
    amountRAM->insertItem ("24k RAM");
    amountRAM->insertItem ("32k RAM");
    amountRAM->insertItem ("48k RAM");
    amountRAM->insertItem ("64k RAM");
    amountRAM->move (0,0);
    amountRAM->adjustSize();
    amountRAM->move (10,10);
    amountRAM->show();

    dirname = new char[100];
    botname = QDir::homeDirPath();
    botname += "/droidbattles/unnamed";

    gfxbutton = new QPushButton (this);
    gfxbutton->setGeometry (10,450,520,36);
    gfxbutton->setPixmap (gfx);
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
}

void createbot::resizeEvent (QResizeEvent *)
{
    int wid1 = width() /9;
    if (wid1 > 100) wid1 = 100;
    showlatency->resize (wid1, height()-100);
    int wid2 = width()-wid1-235;
    edittxt->setGeometry (wid1+10,30,wid2,height()-100);
    scrvw->setGeometry (wid1+wid2+15,40,210,height()-100);
    gfxbutton->setGeometry (10,height()-50,520,36);
}

/**
	* Loads the bot graphics
	*/
void createbot::choosepic()
{
    QString filename = Q3FileDialog::getOpenFileName (0,"*.bmp",this);
    if (!filename.isEmpty())
        gfx.load (filename);
    gfxbutton->setPixmap (gfx);
    changed = true;
}

/**
	* Destructor, Asks if bot should be saved before closing
	*/
createbot::~createbot()
{
    if (changed || edittxt->edited())
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
    delete dirname;
//	delete backpm;
}

/**
	* Deletes window (if user clicksthe X )
	*/
void createbot::closeEvent (QCloseEvent*)
{
    delete this;
}

/**
	* Creates an empty bot
	*/
void createbot::newb()
{
    if (changed || edittxt->edited())
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
    amountRAM->setCurrentItem (0);
    botname = QDir::homeDirPath();
    botname += "/droidbattles/unnamed";
    gfx.resize (0,0);
    changed = false;
    edittxt->setEdited (false);
}

/**
	* Opens a bot source file, and lets the user choose the file.
	* TODO: Check if the contents of the file is correctly
	*       formatted
	* TODO: Add "are you sure" dialog if the current bot loaded
	*       is unsaved
	*/
void createbot::open()
{

    if (changed || edittxt->edited())
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
    QString tempname = Q3FileDialog::getOpenFileName (0,"*.basm",this);
    if (!tempname.isEmpty())
    {
        QFile f (tempname);
        if (!f.open (QIODevice::ReadOnly))
        {
            error ("Couldn't open file!",0);
            return;
        }
        QString tline;
        Q3TextStream s (&f);
        unsigned short i;
//		char v;
        s >> tline;
        s >> i;
        amountRAM->setCurrentItem (i);
        int x;
        for (x=0; x<32; x++)
        {
            s >> tline;
            s >> i;
            devices[x]->setitem (i);
            s >> i;
            devices[x]->levelchosen (i);
            s >> tline;
            devices[x]->setarg1 ( (char *) tline.data());
        }
        tline = s.readLine();
        tline = s.readLine();
        edittxt->clear();
        while (!s.atEnd())
        {
            tline = s.readLine();
            edittxt->append (tline);
        }
        f.close();
        botname = tempname.left (tempname.length()-5);
        tempname = botname;
        tempname += ".bmp";
        QFile f2 (tempname);
        if (f2.exists())
            gfx.load (tempname);
        else
            gfx.resize (0,0);
    }
    changed = false;
    edittxt->setEdited (false);
}

/**
	* Saves changes to file
	*/
void createbot::save()
{
    QString tempname = botname;
    tempname += ".basm";
    if (!tempname.isEmpty())
    {
        QFile f (tempname);
        if (!f.open (QIODevice::WriteOnly))
        {
            saveas();
            return;
        }
        Q3TextStream s (&f);
        s << "RAM: " << amountRAM->currentItem() << endl <<  endl;
        int x;
        for (x=0; x<32; x++)
            s << "DEVICE: " << devices[x]->getitem() << " " <<
            devices[x]->getlevel() << " " << devices[x]->getarg1() << endl;
        s << endl;
        QString tempdata = edittxt->text();
        s << tempdata;
        f.close();
    }
    if (gfx.width() > 31 && gfx.height() > 31)
    {
        tempname = botname;
        tempname += ".bmp";
        gfx.save (tempname, "BMP");
    }
    changed = false;
    edittxt->setEdited (false);
}

/**
	* Saves the current bot to a bot source file
	* (and lets the user choose file)
	* TODO: If the user specifies a file without
	*       .basm at the end, add that end.
	*/
void createbot::saveas()
{
    QString tempname = Q3FileDialog::getSaveFileName (0,"*.basm",this);
    if (!tempname.isEmpty())
    {
        QFile f (tempname);
        if (!f.open (QIODevice::WriteOnly))
        {
            error ("Couldn't open file!",0);
            return;
        }
        Q3TextStream s (&f);
        s << "RAM: " << amountRAM->currentItem() << endl <<  endl;
        int x;
        for (x=0; x<32; x++)
            s << "DEVICE: " << devices[x]->getitem() << " " <<
            devices[x]->getlevel() << " " << devices[x]->getarg1() << endl;
        s << endl;
        QString tempdata = edittxt->text();
        s << tempdata;
        f.close();
    }
    botname = tempname.left (tempname.length()-5);
    if (gfx.width() > 31 && gfx.height() > 31)
    {
        tempname = botname;
        tempname += ".bmp";
        gfx.save (tempname, "BMP");
    }
    changed = false;
    edittxt->setEdited (false);
}

/**
	* TODO: add "are you sure" dialog
	*/
void createbot::closec()
{
    delete this;
}


void createbot::copy()
{
    edittxt->copy();
}

void createbot::cut()
{
    edittxt->cut();
}

void createbot::paste()
{
    edittxt->paste();
}

void createbot::devchanged()
{
    changed = true;
}

/**
	* Makes a binary file out of the
	* current bot.
	* TODO: Document this beast (or rewrite it from scratch)
	*/
void createbot::assemble()
{
    int i;

    //Memory where the file contents are stored during assemble
    mem = new unsigned char[65536+256];
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
    mem[1] = amountRAM->currentItem();
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

    bool end=false;
    int linenum=0;
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
    int type[16];
    unsigned char value[16][2];
    int tpos;
    instruktion *instr[255];
    int bits;
    showlatency->clear();

    // Declare all mnemonics available
    // ( mnemonic,arg1type,arg2type,bits,arg1bits,arg2bits,opcode )
    instr[0] = new instruktion ("nop", none, none, bit0, bit0, bit0, 0x0);

    instr[1] = new instruktion ("mov", reg, reg, bit16, bit8, bit8, 0x1);
    instr[2] = new instruktion ("mov", reg, reg, bit8, bit8, bit8, 0x2);
    instr[3] = new instruktion ("mov", reg, memc, bit16, bit8, bit16, 0x3);
    instr[4] = new instruktion ("mov", reg, memc, bit8, bit8, bit16, 0x4);
    instr[5] = new instruktion ("mov", reg, mreg, bit16, bit8, bit8, 0x5);
    instr[6] = new instruktion ("mov", reg, mreg, bit8, bit8, bit8, 0x6);
    instr[7] = new instruktion ("mov", memc, reg, bit16, bit16, bit8, 0x7);
    instr[8] = new instruktion ("mov", memc, reg, bit8, bit16, bit8, 0x8);
    instr[9] = new instruktion ("mov", mreg, reg, bit16, bit8, bit8, 0x9);
    instr[10] = new instruktion ("mov", mreg, reg, bit8, bit8, bit8, 0xA);
    instr[11] = new instruktion ("mov", reg, val, bit16, bit8, bit16, 0xB);
    instr[12] = new instruktion ("mov", reg, val, bit8, bit8, bit8, 0xC);
    instr[13] = new instruktion ("mov", mreg, val, bit16, bit8, bit16, 0xD);
    instr[14] = new instruktion ("mov", mreg, val, bit8, bit8, bit8, 0xE);
    instr[15] = new instruktion ("mov", memc, val, bit16, bit16, bit16, 0xF);
    instr[16] = new instruktion ("mov", memc, val, bit8, bit16, bit8, 0x10);

    instr[17] = new instruktion ("movsb", none, none, bit0, bit0, bit0, 0x11);
    instr[18] = new instruktion ("movsw", none, none, bit0, bit0, bit0, 0x12);
    instr[19] = new instruktion ("stosb", none, none, bit0, bit0, bit0, 0x13);
    instr[20] = new instruktion ("stosw", none, none, bit0, bit0, bit0, 0x14);

    instr[21] = new instruktion ("push", reg, none, bit16, bit8, bit0, 0x15);
    instr[22] = new instruktion ("push", reg, none, bit8, bit8, bit0, 0x16);
    instr[23] = new instruktion ("push", memc, none, bit16, bit16, bit0, 0x17);
    instr[24] = new instruktion ("push", memc, none, bit8, bit16, bit0, 0x18);
    instr[25] = new instruktion ("push", mreg, none, bit16, bit8, bit0, 0x19);
    instr[26] = new instruktion ("push", mreg, none, bit8, bit8, bit0, 0x1A);
    instr[27] = new instruktion ("push", val, none, bit16, bit16, bit0, 0x1B);
    instr[28] = new instruktion ("push", val, none, bit8, bit8, bit0, 0x1C);
    instr[29] = new instruktion ("pop", reg, none, bit16, bit8, bit0, 0x1D);
    instr[30] = new instruktion ("pop", reg, none, bit8, bit8, bit0, 0x1E);
    instr[31] = new instruktion ("pop", memc, none, bit16, bit16, bit0, 0x1F);
    instr[32] = new instruktion ("pop", memc, none, bit8, bit16, bit0, 0x20);
    instr[33] = new instruktion ("pop", mreg, none, bit16, bit8, bit0, 0x21);
    instr[34] = new instruktion ("pop", mreg, none, bit8, bit8, bit0, 0x22);

    instr[35] = new instruktion ("xchg", reg, reg, bit16, bit8, bit8, 0x23);
    instr[36] = new instruktion ("xchg", reg, reg, bit8, bit8, bit8, 0x24);
    instr[37] = new instruktion ("xchg", reg, memc, bit16, bit8, bit16, 0x25);
    instr[38] = new instruktion ("xchg", reg, memc, bit8, bit8, bit16, 0x26);
    instr[39] = new instruktion ("xchg", reg, mreg, bit16, bit8, bit8, 0x27);
    instr[40] = new instruktion ("xchg", reg, mreg, bit8, bit8, bit8, 0x28);

    instr[41] = new instruktion ("test", reg, val, bit16, bit8, bit8, 0x29);
    instr[42] = new instruktion ("test", memc, val, bit16, bit16, bit8, 0x2A);
    instr[43] = new instruktion ("test", mreg, val, bit16, bit8, bit8, 0x2B);
    instr[44] = new instruktion ("test", reg, none, bit16, bit8, bit0, 0x2C);
    instr[45] = new instruktion ("test", memc, none, bit16, bit16, bit0, 0x2D);
    instr[46] = new instruktion ("test", mreg, none, bit16, bit8, bit0, 0x2E);

    instr[47] = new instruktion ("cmp", reg, reg, bit16, bit8, bit8, 0x2F);
    instr[48] = new instruktion ("cmp", reg, reg, bit8, bit8, bit8, 0x30);
    instr[49] = new instruktion ("cmp", reg, memc, bit16, bit8, bit16, 0x31);
    instr[50] = new instruktion ("cmp", reg, memc, bit8, bit8, bit16, 0x32);
    instr[51] = new instruktion ("cmp", reg, mreg, bit16, bit8, bit8, 0x33);
    instr[52] = new instruktion ("cmp", reg, mreg, bit8, bit8, bit8, 0x34);
    instr[53] = new instruktion ("cmp", reg, val, bit16, bit8, bit16, 0x35);
    instr[54] = new instruktion ("cmp", reg, val, bit8, bit8, bit8, 0x36);
    instr[55] = new instruktion ("cmp", mreg, val, bit16, bit8, bit16, 0x37);
    instr[56] = new instruktion ("cmp", mreg, val, bit8, bit8, bit8, 0x38);
    instr[57] = new instruktion ("cmp", memc, val, bit16, bit16, bit16, 0x39);
    instr[58] = new instruktion ("cmp", memc, val, bit8, bit16, bit8, 0x3A);
    instr[59] = new instruktion ("cmpsb", none, none, bit0, bit0, bit0, 0x3B);

    instr[60] = new instruktion ("jmp", val, none, bit0, bit16, bit0, 0x3C);
    instr[61] = new instruktion ("jz", val, none, bit0, bit16, bit0, 0x3D);
    instr[62] = new instruktion ("jnz", val, none, bit0, bit16, bit0, 0x3E);
    instr[63] = new instruktion ("jae", val, none, bit0, bit16, bit0, 0x3F);
    instr[64] = new instruktion ("jnb", val, none, bit0, bit16, bit0, 0x3F);
    instr[65] = new instruktion ("jbe", val, none, bit0, bit16, bit0, 0x40);
    instr[66] = new instruktion ("jna", val, none, bit0, bit16, bit0, 0x40);
    instr[67] = new instruktion ("jmp", reg, none, bit16, bit8, bit0, 0x41);
    instr[68] = new instruktion ("loop", val, none, bit0, bit16, bit0, 0x42);
    instr[69] = new instruktion ("call", val, none, bit0, bit16, bit0, 0x43);
    instr[70] = new instruktion ("ret", none, none, bit0, bit16, bit0, 0x44);
    instr[71] = new instruktion ("iret", none, none, bit0, bit16, bit0, 0x45);

    instr[72] = new instruktion ("cli", none, none, bit0, bit0, bit0, 0x46);
    instr[73] = new instruktion ("sti", none, none, bit0, bit0, bit0, 0x47);

    instr[74] = new instruktion ("out", val, val, bit0, bit8, bit16, 0x48);
    instr[75] = new instruktion ("out", val, reg, bit16, bit8, bit8, 0x49);
    instr[76] = new instruktion ("out", val, mreg, bit16, bit8, bit8, 0x4A);
    instr[77] = new instruktion ("in", reg, val, bit16, bit8, bit8, 0x4B);

    instr[78] = new instruktion ("inc", reg, none, bit16, bit8, bit0, 0x4C);
    instr[79] = new instruktion ("inc", reg, none, bit8, bit8, bit0, 0x4D);
    instr[80] = new instruktion ("inc", memc, none, bit16, bit16, bit0, 0x4E);
    instr[81] = new instruktion ("inc", memc, none, bit8, bit16, bit0, 0x4F);
    instr[82] = new instruktion ("inc", mreg, none, bit16, bit8, bit0, 0x50);
    instr[83] = new instruktion ("inc", mreg, none, bit8, bit8, bit0, 0x51);
    instr[84] = new instruktion ("dec", reg, none, bit16, bit8, bit0, 0x52);
    instr[85] = new instruktion ("dec", reg, none, bit8, bit8, bit0, 0x53);
    instr[86] = new instruktion ("dec", memc, none, bit16, bit16, bit0, 0x54);
    instr[87] = new instruktion ("dec", memc, none, bit8, bit16, bit0, 0x55);
    instr[88] = new instruktion ("dec", mreg, none, bit16, bit8, bit0, 0x56);
    instr[89] = new instruktion ("dec", mreg, none, bit8, bit8, bit0, 0x57);

    instr[90] = new instruktion ("add", reg, reg, bit16, bit8, bit8, 0x58);
    instr[91] = new instruktion ("add", reg, reg, bit8, bit8, bit8, 0x59);
    instr[92] = new instruktion ("add", reg, val, bit16, bit8, bit16, 0x5A);
    instr[93] = new instruktion ("add", reg, val, bit8, bit8, bit8, 0x5B);
    instr[94] = new instruktion ("add", reg, mreg, bit16, bit8, bit8, 0x5C);
    instr[95] = new instruktion ("add", reg, mreg, bit8, bit8, bit8, 0x5D);
    instr[96] = new instruktion ("add", reg, memc, bit16, bit8, bit16, 0x5E);
    instr[97] = new instruktion ("add", reg, memc, bit8, bit8, bit16, 0x5F);
    instr[98] = new instruktion ("add", mreg, reg, bit16, bit8, bit8, 0x60);
    instr[99] = new instruktion ("add", mreg, reg, bit8, bit8, bit8, 0x61);
    instr[100] = new instruktion ("add", mreg, val, bit16, bit8, bit16, 0x62);
    instr[101] = new instruktion ("add", mreg, val, bit8, bit8, bit8, 0x63);
    instr[102] = new instruktion ("add", memc, reg, bit16, bit16, bit8, 0x64);
    instr[103] = new instruktion ("add", memc, reg, bit8, bit16, bit8, 0x65);
    instr[104] = new instruktion ("add", memc, val, bit16, bit16, bit16, 0x66);
    instr[105] = new instruktion ("add", memc, val, bit8, bit16, bit8, 0x67);

    instr[106] = new instruktion ("sub", reg, reg, bit16, bit8, bit8, 0x68);
    instr[107] = new instruktion ("sub", reg, reg, bit8, bit8, bit8, 0x69);
    instr[108] = new instruktion ("sub", reg, val, bit16, bit8, bit16, 0x6A);
    instr[109] = new instruktion ("sub", reg, val, bit8, bit8, bit8, 0x6B);
    instr[110] = new instruktion ("sub", reg, mreg, bit16, bit8, bit8, 0x6C);
    instr[111] = new instruktion ("sub", reg, mreg, bit8, bit8, bit8, 0x6D);
    instr[112] = new instruktion ("sub", reg, memc, bit16, bit8, bit16, 0x6E);
    instr[113] = new instruktion ("sub", reg, memc, bit8, bit8, bit16, 0x6F);
    instr[114] = new instruktion ("sub", mreg, reg, bit16, bit8, bit8, 0x70);
    instr[115] = new instruktion ("sub", mreg, reg, bit8, bit8, bit8, 0x71);
    instr[116] = new instruktion ("sub", mreg, val, bit16, bit8, bit16, 0x72);
    instr[117] = new instruktion ("sub", mreg, val, bit8, bit8, bit8, 0x73);
    instr[118] = new instruktion ("sub", memc, reg, bit16, bit16, bit8, 0x74);
    instr[119] = new instruktion ("sub", memc, reg, bit8, bit16, bit8, 0x75);
    instr[120] = new instruktion ("sub", memc, val, bit16, bit16, bit16, 0x76);
    instr[121] = new instruktion ("sub", memc, val, bit8, bit16, bit8, 0x77);

    instr[122] = new instruktion ("rol", reg, reg, bit16, bit8, bit8, 0x78);
    instr[123] = new instruktion ("rol", reg, val, bit16, bit8, bit8, 0x79);
    instr[124] = new instruktion ("rol", mreg, val, bit16, bit8, bit8, 0x7A);
    instr[125] = new instruktion ("rol", mreg, reg, bit16, bit8, bit8, 0x7B);
    instr[126] = new instruktion ("rol", memc, reg, bit16, bit16, bit8, 0x7C);
    instr[127] = new instruktion ("rol", memc, val, bit16, bit16, bit8, 0x7D);
    instr[128] = new instruktion ("ror", reg, reg, bit16, bit8, bit8, 0x7E);
    instr[129] = new instruktion ("ror", reg, val, bit16, bit8, bit8, 0x7F);
    instr[130] = new instruktion ("ror", mreg, val, bit16, bit8, bit8, 0x80);
    instr[131] = new instruktion ("ror", mreg, reg, bit16, bit8, bit8, 0x81);
    instr[132] = new instruktion ("ror", memc, reg, bit16, bit16, bit8, 0x82);
    instr[133] = new instruktion ("ror", memc, val, bit16, bit16, bit8, 0x83);
    instr[134] = new instruktion ("imul", none, none, bit0, bit0, bit0, 0x84);
    instr[135] = new instruktion ("idiv", none, none, bit0, bit0, bit0, 0x85);
    instr[136] = new instruktion ("ja", val, none, bit0, bit16, bit0, 0x86);
    instr[137] = new instruktion ("jb", val, none, bit0, bit16, bit0, 0x87);

    instr[138] = new instruktion ("atanfunc", none, none, bit0, bit0, bit0,
                                  0x88);
    instr[139] = new instruktion ("sqr", none, none, bit0, bit0, bit0, 0x89);
    instr[140] = new instruktion ("icmp", reg, reg, bit16, bit8, bit8, 0x8A);
    instr[141] = new instruktion ("icmp", reg, memc, bit16, bit8, bit16, 0x8B);
    instr[142] = new instruktion ("icmp", reg, mreg, bit16, bit8, bit8, 0x8C);
    instr[143] = new instruktion ("icmp", reg, val, bit16, bit8, bit16, 0x8D);
    instr[144] = new instruktion ("icmp", mreg, val, bit16, bit8, bit16, 0x8E);
    instr[145] = new instruktion ("icmp", memc, val, bit16, bit16, bit16,
                                  0x8F);
    instr[146] = new instruktion ("msg", mreg, none, bit16, bit8, bit0, 0x90);
    instr[147] = new instruktion ("msg", memc, none, bit16, bit16, bit0, 0x91);
    instr[148] = new instruktion ("err", val, none, bit0, bit8, bit0, 0x92);
    instr[149] = new instruktion ("readfile", none, none, bit0, bit0, bit0,
                                  0x93);
    instr[150] = new instruktion ("writefile", none, none, bit0, bit0, bit0,
                                  0x94);
    instr[151] = new instruktion ("lz", reg, none, bit16, bit8, bit0, 0x95);
    instr[152] = new instruktion ("lnz", reg, none, bit16, bit8, bit0, 0x96);
    instr[153] = new instruktion ("la", reg, none, bit16, bit8, bit0, 0x97);

    instr[154] = new instruktion ("and", reg, reg, bit16, bit8, bit8, 0x98);
    instr[155] = new instruktion ("and", reg, reg, bit8, bit8, bit8, 0x99);
    instr[156] = new instruktion ("and", reg, val, bit16, bit8, bit16, 0x9A);
    instr[157] = new instruktion ("and", reg, val, bit8, bit8, bit8, 0x9B);
    instr[158] = new instruktion ("and", reg, mreg, bit16, bit8, bit8, 0x9C);
    instr[159] = new instruktion ("and", reg, mreg, bit8, bit8, bit8, 0x9D);
    instr[160] = new instruktion ("and", reg, memc, bit16, bit8, bit16, 0x9E);
    instr[161] = new instruktion ("and", reg, memc, bit8, bit8, bit16, 0x9F);
    instr[162] = new instruktion ("and", mreg, reg, bit16, bit8, bit8, 0xA0);
    instr[163] = new instruktion ("and", mreg, reg, bit8, bit8, bit8, 0xA1);
    instr[164] = new instruktion ("and", mreg, val, bit16, bit8, bit16, 0xA2);
    instr[165] = new instruktion ("and", mreg, val, bit8, bit8, bit8, 0xA3);
    instr[166] = new instruktion ("and", memc, reg, bit16, bit16, bit8, 0xA4);
    instr[167] = new instruktion ("and", memc, reg, bit8, bit16, bit8, 0xA5);
    instr[168] = new instruktion ("and", memc, val, bit16, bit16, bit16, 0xA6);
    instr[169] = new instruktion ("and", memc, val, bit8, bit16, bit8, 0xA7);

    instr[170] = new instruktion ("or", reg, reg, bit16, bit8, bit8, 0xA8);
    instr[171] = new instruktion ("or", reg, reg, bit8, bit8, bit8, 0xA9);
    instr[172] = new instruktion ("or", reg, val, bit16, bit8, bit16, 0xAA);
    instr[173] = new instruktion ("or", reg, val, bit8, bit8, bit8, 0xAB);
    instr[174] = new instruktion ("or", reg, mreg, bit16, bit8, bit8, 0xAC);
    instr[175] = new instruktion ("or", reg, mreg, bit8, bit8, bit8, 0xAD);
    instr[176] = new instruktion ("or", reg, memc, bit16, bit8, bit16, 0xAE);
    instr[177] = new instruktion ("or", reg, memc, bit8, bit8, bit16, 0xAF);
    instr[178] = new instruktion ("or", mreg, reg, bit16, bit8, bit8, 0xB0);
    instr[179] = new instruktion ("or", mreg, reg, bit8, bit8, bit8, 0xB1);
    instr[180] = new instruktion ("or", mreg, val, bit16, bit8, bit16, 0xB2);
    instr[181] = new instruktion ("or", mreg, val, bit8, bit8, bit8, 0xB3);
    instr[182] = new instruktion ("or", memc, reg, bit16, bit16, bit8, 0xB4);
    instr[183] = new instruktion ("or", memc, reg, bit8, bit16, bit8, 0xB5);
    instr[184] = new instruktion ("or", memc, val, bit16, bit16, bit16, 0xB6);
    instr[185] = new instruktion ("or", memc, val, bit8, bit16, bit8, 0xB7);

    instr[186] = new instruktion ("xor", reg, reg, bit16, bit8, bit8, 0xB8);
    instr[187] = new instruktion ("xor", reg, reg, bit8, bit8, bit8, 0xB9);
    instr[188] = new instruktion ("xor", reg, val, bit16, bit8, bit16, 0xBA);
    instr[189] = new instruktion ("xor", reg, val, bit8, bit8, bit8, 0xBB);
    instr[190] = new instruktion ("xor", reg, mreg, bit16, bit8, bit8, 0xBC);
    instr[191] = new instruktion ("xor", reg, mreg, bit8, bit8, bit8, 0xBD);
    instr[192] = new instruktion ("xor", reg, memc, bit16, bit8, bit16, 0xBE);
    instr[193] = new instruktion ("xor", reg, memc, bit8, bit8, bit16, 0xBF);
    instr[194] = new instruktion ("xor", mreg, reg, bit16, bit8, bit8, 0xC0);
    instr[195] = new instruktion ("xor", mreg, reg, bit8, bit8, bit8, 0xC1);
    instr[196] = new instruktion ("xor", mreg, val, bit16, bit8, bit16, 0xC2);
    instr[197] = new instruktion ("xor", mreg, val, bit8, bit8, bit8, 0xC3);
    instr[198] = new instruktion ("xor", memc, reg, bit16, bit16, bit8, 0xC4);
    instr[199] = new instruktion ("xor", memc, reg, bit8, bit16, bit8, 0xC5);
    instr[200] = new instruktion ("xor", memc, val, bit16, bit16, bit16, 0xC6);
    instr[201] = new instruktion ("xor", memc, val, bit8, bit16, bit8, 0xC7);

    instr[202] = new instruktion ("shl", reg, val, bit16, bit8, bit8, 0xC8);
    instr[203] = new instruktion ("shl", reg, reg, bit16, bit8, bit8, 0xC9);
    instr[204] = new instruktion ("shl", mreg, val, bit16, bit8, bit8, 0xCA);
    instr[205] = new instruktion ("shl", mreg, reg, bit16, bit8, bit8, 0xCB);
    instr[206] = new instruktion ("shl", memc, val, bit16, bit16, bit8, 0xCC);
    instr[207] = new instruktion ("shl", memc, reg, bit16, bit16, bit8, 0xCD);
    instr[208] = new instruktion ("shr", reg, val, bit16, bit8, bit8, 0xCE);
    instr[209] = new instruktion ("shr", reg, reg, bit16, bit8, bit8, 0xCF);
    instr[210] = new instruktion ("shr", mreg, val, bit16, bit8, bit8, 0xD0);
    instr[211] = new instruktion ("shr", mreg, reg, bit16, bit8, bit8, 0xD1);
    instr[212] = new instruktion ("shr", memc, val, bit16, bit16, bit8, 0xD2);
    instr[213] = new instruktion ("shr", memc, reg, bit16, bit16, bit8, 0xD3);

    instr[214] = new instruktion ("ishl", reg, val, bit16, bit8, bit8, 0xD4);
    instr[215] = new instruktion ("ishl", reg, reg, bit16, bit8, bit8, 0xD5);
    instr[216] = new instruktion ("ishl", mreg, val, bit16, bit8, bit8, 0xD6);
    instr[217] = new instruktion ("ishl", mreg, reg, bit16, bit8, bit8, 0xD7);
    instr[218] = new instruktion ("ishl", memc, val, bit16, bit16, bit8, 0xD8);
    instr[219] = new instruktion ("ishl", memc, reg, bit16, bit16, bit8, 0xD9);
    instr[220] = new instruktion ("ishr", reg, val, bit16, bit8, bit8, 0xDA);
    instr[221] = new instruktion ("ishr", reg, reg, bit16, bit8, bit8, 0xDB);
    instr[222] = new instruktion ("ishr", mreg, val, bit16, bit8, bit8, 0xDC);
    instr[223] = new instruktion ("ishr", mreg, reg, bit16, bit8, bit8, 0xDD);
    instr[224] = new instruktion ("ishr", memc, val, bit16, bit16, bit8, 0xDE);
    instr[225] = new instruktion ("ishr", memc, reg, bit16, bit16, bit8, 0xDF);

    instr[226] = new instruktion ("int", val, none, bit0, bit16, bit0, 0xE0);
    instr[227] = new instruktion ("mul", none, none, bit0, bit0, bit0, 0xE1);
    instr[228] = new instruktion ("div", none, none, bit0, bit0, bit0, 0xE2);

    instr[229] = new instruktion ("ret", val, none, bit0, bit8, bit0, 0xE3);
    instr[230] = new instruktion ("lodsb", none, none, bit0, bit0, bit0, 0xE4);
    instr[231] = new instruktion ("lodsw", none, none, bit0, bit0, bit0, 0xE5);
    instr[232] = new instruktion ("sinfunc", none, none, bit0, bit0, bit0,
                                  0xE6);
    instr[233] = new instruktion ("cosfunc", none, none, bit0, bit0, bit0,
                                  0xE7);
    instr[234] = new instruktion ("sin", none, none, bit0, bit0, bit0, 0xE8);
    instr[235] = new instruktion ("cos", none, none, bit0, bit0, bit0, 0xE9);

    instr[245] = new instruktion ("mov", val, val, bit16, bit16, bit8, 0xEA);
    instr[246] = new instruktion ("mov", val, val, bit16, bit16, bit8, 0xEB);
    instr[236] = new instruktion ("rnd", none, none, bit0, bit0, bit0, 0xEC);
    instr[237] = new instruktion ("hwait", none, none, bit0, bit0, bit0, 0xED);

    instr[238] = new instruktion ("lb", reg, none, bit16, bit8, bit0, 0xEE);
    instr[239] = new instruktion ("lae", reg, none, bit16, bit8, bit0, 0xEF);
    instr[240] = new instruktion ("lnb", reg, none, bit16, bit8, bit0, 0xEF);
    instr[241] = new instruktion ("lbe", reg, none, bit16, bit8, bit0, 0xF0);
    instr[242] = new instruktion ("lna", reg, none, bit16, bit8, bit0, 0xF0);
    instr[243] = new instruktion ("cj", reg, val, bit16, bit8, bit16, 0xF1);
    instr[244] = new instruktion ("cjn", reg, val, bit16, bit8, bit16, 0xF2);


    QString tempname = botname;
    tempname += ".bot";
    QFile f (tempname);
    while (end != true)              //If we still have lines left to compile
    {
        if (edittxt->numLines() > linenum)
        {
            curline = edittxt->textLine (linenum);   //Load one line
            QString insertstr = "";
            for (i=0; i<15; i++)
            {
                value[i][0]=0;
                value[i][1]=0;
                exist[i]=false;
                tunres[i]=false;
                token[i]="";
                type[i]=0;
                unresnum[i]=0;
            }
            bits=0;
            if (curline.length() > 1)
            {
                //Chop of line comments and such
                tpos = curline.find (QRegExp ("[;\\n\\r]"),0);
                tempstring = curline.left (tpos);
                curline = tempstring.copy();
                tpos = curline.find (QRegExp ("[a-zA-Z0-9_#:%@$]"),0);
                curline = curline.right (curline.length()-tpos);
                if (curline.length() <= 1)
                {
                    showlatency->insertLine ("",-1);
                    goto newline;
                }

                // divide into tokens
                /////////////////////
                // take the tokens
                for (i=0; i<15; i++)
                {
                    tpos = curline.find (QRegExp ("[\\s,\\x0]"),0);

                    if (tpos < curline.length())
                        token[i] = curline.left (tpos);
                    else
                    {
                        token[i] = curline.copy();
                        exist[i] = true;
                        break;
                    }
                    curline = curline.right (curline.length()-tpos);
                    tpos = curline.find (QRegExp ("[a-zA-Z0-9_#:%@$+-]"),0);
                    curline = curline.right (curline.length()-tpos);
                    exist[i] = true;

                }
                for (i=0; i<15; i++)     //Check which tokens actually exists
                {
                    if (token[i].length() <= 0)
                        exist[i] = false;
                    type[i] = 0;
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
                    if (token[0].length() > 1)
                    {
                        type[0] = 1;
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
                            goto ende;
                        }
                    }
                    else
                    {
                        error ("Expected: name of label",linenum);
                        goto ende;
                    }
                }
                //Check for vardeclaration
                if (type[0] == 0 && token[0].left (1) == QString ("#"))
                {
                    if (token[0].length() > 1)
                    {
                        type[0] = 6;
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
                            goto ende;
                        }
                    }
                    else
                    {
                        error ("Expected: name of variable", linenum);
                        goto ende;
                    }
                }

                //Check for const declarations
                if (type[0] == 0 && token[0].left (1) == QString ("$"))
                {
                    if (token[0].length() > 1)
                    {
                        type[0] = 8;
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
                            goto ende;
                        }
                        if (exist[2] == true)
                        {
                            error ("Expected: only two tokens",linenum);
                            goto ende;
                        }
                    }
                    else
                    {
                        error ("Expected: name of constant", linenum);
                        goto ende;
                    }
                }
                //Check for db
                if (type[0]==0 && token[0] == QString ("db"))
                {
                    type[0] = 11;
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
                if (type[0]==0 && token[0] == QString ("dw"))
                {
                    type[0] = 11;
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
                if (type[0] == 0 && token[0] == QString ("%org"))
                {
                    type[0] = 7;
                    if (exist[1] == true)
                    {
                        bool isplus = ! (token[1].left (1) == "+");
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
                                    goto ende;
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
                        goto ende;
                    }
                }

                //Check for %CPUboot
                if (type[0] == 0 && token[0] == QString ("%CPUboot"))
                {
                    type[0] = 9;
                    if (exist[1] == true)
                    {
                        tpos = token[1].toInt (&ok);
                        if (ok == false)
                        {
                            int x;
                            for (x=0; x<2047; x++)
                            {
                                if (existn[x] == true)
                                {
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
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    error ("Unknown symbol",linenum);
                                    goto ende;
                                }
                            }
                        }
                        else
                        {
                            //Code for non-symbol value
                            if (tpos < 32 && mem[tpos*6+2] == 1)
                            {
                                mem[tpos*6+4] = posinmem%256;
                                mem[tpos*6+5] = int (posinmem/256);
                            }
                            else
                            {
                                error ("Value must be the number of a CPU device",linenum);
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        error ("Expected: number of CPU device",linenum);
                        goto ende;
                    }
                }
                //Check for %CPUstack
                if (type[0] == 0 && token[0] == QString ("%CPUstack"))
                {
                    type[0] = 10;
                    if (exist[1] == true)
                    {
                        tpos = token[1].toInt (&ok);
                        if (ok == false)
                        {
                            int x;
                            for (x=0; x<2047; x++)
                            {
                                if (existn[x] == true)
                                {
                                    if (token[1] == names[x])
                                    {
                                        if (nvalues[x]<32 && mem[nvalues[x]*6+2] == 1)
                                        {
                                            mem[nvalues[x]*6+6] = posinmem%256;
                                            mem[nvalues[x]*6+7] = int (posinmem/256);
                                        }
                                        else
                                        {
                                            //Code for error in dev-value
                                            error ("Value must be the number of a CPU device",
                                                   linenum);
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    error ("Unknown symbol",linenum);
                                    goto ende;
                                }
                            }
                        }
                        else
                        {
                            //Code for non-symbol value
                            if (tpos < 32 && mem[tpos*6+2] == 1)
                            {
                                mem[tpos*6+6] = posinmem%256;
                                mem[tpos*6+7] = int (posinmem/256);
                            }
                            else
                            {
                                error ("Value must be the number of a CPU device",linenum);
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        error ("Expected: number of CPU device",linenum);
                        goto ende;
                    }
                }

                //Check for %interrupt
                if (type[0] == 0 && token[0] == QString ("%interrupt"))
                {
                    type[0] = 14;
                    if (exist[1] == true)
                    {
                        tpos = token[1].toInt (&ok);
                        if (ok == false)
                        {
                            int x;
                            for (x=0; x<2047; x++)
                            {
                                if (existn[x] == true)
                                {
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
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    error ("Unknown symbol",linenum);
                                    goto ende;
                                }
                            }
                        }
                        else
                        {
                            //Code for non-symbol value
                            if (tpos < 256)
                            {
                                mem[ (RAMAMOUNT+256- (tpos*2+2)) ] = posinmem%256;
                                mem[ (RAMAMOUNT+256- (tpos*2+1)) ] = int (posinmem/256);
                            }
                            else
                            {
                                error ("Value must be lower than 256",linenum);
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        error ("Expected: number of interrupt",linenum);
                        goto ende;
                    }
                }

                //Assign as mnemonic
                if (type[0] == 0)
                {
                    type[0] = 2;
                    curmnem = token[0];
                }
                //If mnemonic Assign types to all other tokens
                if (type[0] == 2)
                {

                    //Check for register
                    for (i=1; i<4; i++)
                    {
                        if (exist[i] == true && type[i] == 0)
                        {
                            if (token[i] == QString ("ax"))
                            {
                                type[i] = 5;
                                value[i][0] = ax;
                                bits = 16;
                            }
                            if (token[i] == "bx")
                            {
                                type[i] = 5;
                                value[i][0] = bx;
                                bits = 16;
                            }
                            if (token[i] == "cx")
                            {
                                type[i] = 5;
                                value[i][0] = cx;
                                bits = 16;
                            }
                            if (token[i] == "dx")
                            {
                                type[i] = 5;
                                value[i][0] = dx;
                                bits = 16;
                            }
                            if (token[i] == "sp")
                            {
                                type[i] = 5;
                                value[i][0] = sp;
                                bits = 16;
                            }
                            if (token[i] == "bp")
                            {
                                type[i] = 5;
                                value[i][0] = bp;
                                bits = 16;
                            }
                            if (token[i] == "si")
                            {
                                type[i] = 5;
                                value[i][0] = si;
                                bits = 16;
                            }
                            if (token[i] == QString ("di"))
                            {
                                type[i] = 5;
                                value[i][0] = di;
                                bits = 16;
                            }
                            if (token[i] == QString ("eip"))
                            {
                                type[i] = 5;
                                value[i][0] = eip;
                                bits = 16;
                            }
                            if (token[i] == QString ("flags"))
                            {
                                type[i] = 5;
                                value[i][0] = 0;
                                bits = 16;
                            }
                            if (token[i] == QString ("ah"))
                            {
                                type[i] = 5;
                                value[i][0] = ah;
                                bits = 8;
                            }
                            if (token[i] == QString ("al"))
                            {
                                type[i] = 5;
                                value[i][0] = al;
                                bits = 8;
                            }
                            if (token[i] == QString ("bh"))
                            {
                                type[i] = 5;
                                value[i][0] = bh;
                                bits = 8;
                            }
                            if (token[i] == QString ("bl"))
                            {
                                type[i] = 5;
                                value[i][0] = bl;
                                bits = 8;
                            }
                            if (token[i] == QString ("ch"))
                            {
                                type[i] = 5;
                                value[i][0] = ch;
                                bits = 8;
                            }
                            if (token[i] == QString ("cl"))
                            {
                                type[i] = 5;
                                value[i][0] = cl;
                                bits = 8;
                            }
                            if (token[i] == QString ("dh"))
                            {
                                type[i] = 5;
                                value[i][0] = dh;
                                bits = 8;
                            }
                            if (token[i] == QString ("dl"))
                            {
                                type[i] = 5;
                                value[i][0] = dl;
                                bits = 8;
                            }
                        }
                    }

                    //Check for @register
                    for (i=1; i<3; i++)
                    {
                        if (exist[i] == true && type[i] == 0 && token[i].left (1) == "@")
                        {
                            QString tempstring = token[i].right (token[i].length()-1);
                            if (tempstring == QString ("ax"))
                            {
                                type[i] = 13;
                                value[i][0] = ax;
                            }
                            if (tempstring == QString ("bx"))
                            {
                                type[i] = 13;
                                value[i][0] = bx;
                            }
                            if (tempstring == QString ("cx"))
                            {
                                type[i] = 13;
                                value[i][0] = cx;
                            }
                            if (tempstring == QString ("dx"))
                            {
                                type[i] = 13;
                                value[i][0] = dx;
                            }
                            if (tempstring == QString ("sp"))
                            {
                                type[i] = 13;
                                value[i][0] = sp;
                            }
                            if (tempstring == QString ("bp"))
                            {
                                type[i] = 13;
                                value[i][0] = bp;
                            }
                            if (tempstring == QString ("si"))
                            {
                                type[i] = 13;
                                value[i][0] = si;
                            }
                            if (tempstring == QString ("di"))
                            {
                                type[i] = 13;
                                value[i][0] = di;
                            }
                            if (tempstring == QString ("eip"))
                            {
                                type[i] = 13;
                                value[i][0] = eip;
                            }
                            if (tempstring == QString ("flags"))
                            {
                                type[i] = 13;
                                value[i][0] = 0;
                            }
                            if (tempstring == QString ("ah"))
                            {
                                type[i] = 13;
                                value[i][0] = ah;
                            }
                            if (tempstring == QString ("al"))
                            {
                                type[i] = 13;
                                value[i][0] = al;
                            }
                            if (tempstring == QString ("bh"))
                            {
                                type[i] = 13;
                                value[i][0] = bh;
                            }
                            if (tempstring == QString ("bl"))
                            {
                                type[i] = 13;
                                value[i][0] = bl;
                            }
                            if (tempstring == QString ("ch"))
                            {
                                type[i] = 13;
                                value[i][0] = ch;
                            }
                            if (tempstring == QString ("cl"))
                            {
                                type[i] = 13;
                                value[i][0] = cl;
                            }
                            if (tempstring == QString ("dh"))
                            {
                                type[i] = 13;
                                value[i][0] = dh;
                            }
                            if (tempstring == QString ("dl"))
                            {
                                type[i] = 13;
                                value[i][0] = dl;
                            }
                        }
                    }

                    //Check for bit identifier
                    for (i=1; i<3; i++)
                    {
                        if (exist[i] == true && type[i] == 0)
                        {
                            if (token[i] == QString ("byte"))
                            {
                                type[i] = 12;
                                value[i][0] = 8;
                                bits = 8;
                            }
                            if (token[i] == QString ("word"))
                            {
                                type[i] = 12;
                                value[i][0] = 16;
                                bits = 16;
                            }
                        }
                    }


                    //Check for @value
                    for (i=1; i<3; i++)
                    {
                        if (exist[i] == true && type[i] == 0 && token[i].left (1) == "@")
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
                                            type[i] = 4;
                                        }
                                    }
                                }
                                if (type[i] == 0)
                                {
                                    type[i] = 4;
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
                                type[i] = 4;
                            }
                        }
                    }


                    //Check for value
                    for (i=1; i<4; i++)
                    {
                        if (exist[i] == true && type[i] == 0)
                        {
                            bool isplus = ! (token[i].left (1) == "+");
                            QString comp;
                            if (isplus)
                                comp = token[i].right (token[i].length()-1);
                            else
                                comp = token[i];
                            tpos = comp.toInt (&ok);
                            if (ok == false)
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
                                            type[i] = 3;
                                        }
                                    }
                                }
                                if (type[i] == 0)
                                {
                                    type[i] = 3;
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
                                type[i] = 3;
                            }
                        }
                    }

                    if ( (curmnem == "mov") && (type[1] == 5) &&
                            (type[2] == 13) && (type[3] == 3))
                    {
                        value[1][1] = value[2][0];
                        value[2][0] = value[3][0];
                        i = 245;
                        if (tunres[3] == true)
                        {
                            error ("Sorry, this instruction can't use symbols not declared yet",
                                   linenum);
                            goto ende;
                        }
                        goto found;
                    }
                    if ( (curmnem == "mov") && (type[1] == 13) &&
                            (type[2] == 3) && (type[3] == 5))
                    {
                        value[1][1] = value[2][0];
                        value[2][0] =	value[3][0];
                        i = 246;
                        if (tunres[2] == true)
                        {
                            error ("Sorry, this instruction can't use symbols not declared yet",
                                   linenum);
                            goto ende;
                        }
                        goto found;
                    }

                    //Run through all available mnemonic-operand combinations available
                    for (i=0; i<245; i++)
                    {
                        if (instr[i]->checkmatch (curmnem,type[1],type[2],bits) ==true)
                            goto found;
                    }
                    //If not success return error
                    error ("Error: unknown mnemonic/operand combination",linenum);
                    goto ende;
                    //If success write result
found:
                    mem[posinmem+256] = instr[i]->getopcode();
                    debugmem[debugentry] = posinmem;
                    debuglines[debugentry++] = linenum;
                    ///////////////
                    int q;
                    q = instrlatency[instr[i]->getopcode() ];
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
                        if (instr[i]->getarg1bits() > 0)
                        {
                            unresbits[ unresnum[1] ] = 8;
                            posinmem++;
                        }
                        if (instr[i]->getarg1bits() > 8)
                        {
                            unresbits[ unresnum[1] ] = 16;
                            posinmem++;
                        }
                    }
                    else
                    {
                        if (instr[i]->getarg1bits() > 0)
                        {
                            mem[posinmem+256] = value[1][0];
                            posinmem++;
                        }
                        if (instr[i]->getarg1bits() > 8)
                        {
                            mem[posinmem+256] = value[1][1];
                            posinmem++;
                        }
                    }

                    if (tunres[2] == true)
                    {
                        unrespos[ unresnum[2] ] = posinmem;
                        if (instr[i]->getarg2bits() > 0)
                        {
                            unresbits[ unresnum[2] ] = 8;
                            posinmem++;
                        }
                        if (instr[i]->getarg2bits() > 8)
                        {
                            unresbits[ unresnum[2] ] = 16;
                            posinmem++;
                        }
                    }
                    else
                    {
                        if (instr[i]->getarg2bits() > 0)
                        {
                            mem[posinmem+256] = value[2][0];
                            posinmem++;
                        }
                        if (instr[i]->getarg2bits() > 8)
                        {
                            mem[posinmem+256] = value[2][1];
                            posinmem++;
                        }
                    }
                }
            }

            showlatency->insertLine (insertstr,-1);
        }
        else
        {
            end = true;
            mem[RAMAMOUNT+256] = 255;
        }
newline:
        linenum++;
        if (linenum > edittxt->numLines()-1)
        {
            end=true;
        }
    }
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
                goto ende;
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
        error ("couldn't open file",0);
        goto ende;
    }

    error ("Assemble successful",-1);
ende:
    delete mem;
    for (i=0; i<247; i++)
        delete instr[i];
}

/**
	* Shows a message from the assembler and an OK button.
	* It also sets the current editing line to line
	*/
void createbot::error (const char *msg,int line)
{
    QMessageBox::information (0,"Message from the almighty assembler", msg);
    if (line >= 0)	edittxt->setCursorPosition (line,0);
}

/**
	* Starts a battle between the current edited bot and the bots specified
	* in the quick battle config
	*/
void createbot::startquick()
{
    QString temp = botname;
    temp += ".bot";
    QFile f (temp);
    if (!f.exists())
    {
        error ("You need to assemble the bot...",0);
        return;
    }
    temp = QDir::homeDirPath();
    temp += "/droidbattles/quick.conf";
    QFile f2 (temp);
    QString names[8];
    int xsize,ysize,numfights,lengthfights;
    bool ifteams;
    int teams[8];
    if (f2.exists() && f2.open (QIODevice::ReadOnly))
    {
        Q3TextStream s (&f2);
        for (int x=0; x<8; x++)
        {
            s >> names[x];
            s >> temp;
            if (names[x] == QString ("fff"))
                names[x] = "";
            teams[x] = temp.toInt();
        }
        names[7] = botname;
        names[7] += ".bot";
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
        return;
    }
    batt = new battlearea ( (char *) names[0].data(), (char *) names[1].data(),
                            (char *) names[2].data(), (char *) names[3].data(),
                            (char *) names[4].data(), (char *) names[5].data(),
                            (char *) names[6].data(), (char *) names[7].data(),
                            numfights,lengthfights,xsize,ysize,ifteams,teams,
                            false,false,0,0,true, edittxt,&debuglines[0],
                            &debugmem[0]);
    batt->show();
}

/**
	* Show window for editing quick battle config
	*/
void createbot::confquick()
{
    qc = new quickconf();
    QObject::connect (qc,SIGNAL (cancelclicked()),this,SLOT (stopconf()));
    qc->resize (300,570);
    qc->show();
}

/**
	* Delete config window
	*/
void createbot::stopconf()
{
    delete qc;
}

/**
	* Reports how the current bot compares to what's allowed in the
	* current config
	*/
void createbot::checkconf()
{
    QString tempname = QDir::homeDirPath();
    tempname += "/droidbattles/current.cfg";
    QFile f (tempname);
    if (!f.open (QIODevice::ReadOnly))
    {
        //TODO: add error message
        return;
    }

    Q3TextStream s (&f);
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
    for (int l=0; l<32; devicesenabled[l++]=0);

    amountram = amountRAM->currentItem();
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

    resulttext += "RAM used: ";
    addint (resulttext,amountram);
    resulttext += "  RAM allowed: ";
    addint (resulttext,curconfig.maxram);

    resulttext += "\nDevices used: ";
    addint (resulttext,numdev);
    resulttext += "  Devices allowed: ";
    addint (resulttext,curconfig.maxdev);

    resulttext += "\nTotal cost: ";
    addint (resulttext,totalcost);
    resulttext += "  cost allowed: ";
    addint (resulttext,curconfig.maxcost);

    for (x=0; x<32; x++)
    {
        if (devicesenabled[x] == 1)
        {
            resulttext += "\n\n device ";
            addint (resulttext,x);
            resulttext += " is a disabled device";
        }
    }
    error ( (char *) resulttext.data(),0);
}

/**
	* Adds the number integ to the string str
	*/
void createbot::addint (QString & str,int integ)
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

void createbot::scrollview (int)
{
//	showlatency->setYoffset( x );
}

int createbot::devnum (int sort,int num)
{
    int number=0;
    for (int x=0; x<num; x++)
    {
        if (devices[x]->getitem() == sort) number++;
    }
    return number;
}

void createbot::setEdittxtScrollValue (int i)
{
    assert (edittxt);
    edittxt->myVerticalScrollBar()->setValue (i);
}

void createbot::setShowlatencyScrollValue (int i)
{
    assert (showlatency);
    showlatency->myVerticalScrollBar()->setValue (i);
}
