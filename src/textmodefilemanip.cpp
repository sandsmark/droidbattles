/***************************************************************************
                          textmodefilemanip.cpp  -  description
                             -------------------
    begin                : Thu Nov 22 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@bluefire.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "textmodefilemanip.h"
//Added by qt3to4:
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>

TextModeFileManip::TextModeFileManip()
{
}

TextModeFileManip::~TextModeFileManip()
{
}

void TextModeFileManip::assemble (char *filename)
{
    QString fname = filename;
    fname += ".basm";
    QFile fin (fname);
    if (!fin.open (QIODevice::ReadOnly))
    {
        qDebug() << "could not open file" << endl;
        return;
    }
    QTextStream sin (&fin);
    QString curline;
    sin >> curline;
    if (curline != QString ("RAM:"))
    {
        qDebug() << "Botfile corrupt, (error reading RAM size)";
        return;
    }


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
    int RAMAMOUNT=0;

    mem[0] = 'B';

    //Put in the amount of RAM

    sin >> curline;
    bool ok;
    int tint = curline.toInt (&ok);
    if (!ok || tint > 8 || tint < 0)
    {
        qDebug() << "Botfile corrupt, (error reading RAM size)";
        return;
    }

    mem[1] = tint;
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
    }

    for (i=0; i<32; i++)
    {
        sin >> curline;
        if (curline != QString ("DEVICE:"))
        {
            qDebug() << "Botfile corrupt, (error reading DEVICES)";
            return;
        }
        sin >> curline;
        tint = curline.toInt (&ok);
        if (!ok)
        {
            qDebug() << "Botfile corrupt, (error reading DEVICES)";
            return;
        }

        mem[2+i*6] = tint;
        sin >> curline;
        tint = curline.toInt (&ok);
        if (!ok)
        {
            qDebug() << "Botfile corrupt, (error reading DEVICES)";
            return;
        }
        mem[3+i*6] = tint;
        sin >> curline;
        tint = curline.toInt (&ok);
        if (!ok)
        {
            qDebug() << "Botfile corrupt, (error reading DEVICES)";
            return;
        }
        mem[4+i*6] = tint;
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
    QString token[16];
    QString curmnem;
    bool tunres[16];
    short unresnum[16];
    for (i=0; i<15; i++)
        token[i] = "      ";
    bool exist[16];
    int type[16];
    unsigned char value[16][2];
    int tpos;
    int bits;

    QString tempname = filename;
    tempname += ".bot";
    QFile f (tempname);

    while (!end)              //If we still have lines left to compile
    {
        curline = sin.readLine();
        if (curline.isEmpty())
        {
            end = true;
        }
        if (!end)
        {
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
                tpos = curline.indexOf (QRegExp ("[;\\n\\r]"),0);
                tempstring = curline.left (tpos);
                curline = tempstring;
                tpos = curline.indexOf (QRegExp ("[a-zA-Z0-9_#:%@$]"),0);
                curline = curline.right (curline.length()-tpos);
                if (curline.length() <= 1)
                {
                    goto newline;
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
                            qDebug() << "Expected: only one token on line " << linenum << endl;
                            goto ende;
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: name of label on line" << linenum << endl;
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
                            qDebug() << "Expected: only one token, line " << linenum << endl;
                            goto ende;
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: name of variable on line " << linenum << endl;
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
                        }
                        else
                        {
                            qDebug() << "Expected: value of constant, line " << linenum << endl;
                            goto ende;
                        }
                        if (exist[2] == true)
                        {
                            qDebug() << "Expected: only two tokens, line " << linenum << endl;
                            goto ende;
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: name of constant on line " << linenum << endl;
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
                        bool isplus = token[1].startsWith('+');
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
                                    qDebug() << "Unknown symbol on line " << linenum << endl;
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
                        qDebug() << "Expected: value for org on line" << linenum << endl;
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
                                            qDebug() << "Value must be the number of a CPU device" << linenum << endl;
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    qDebug() << "Unknown symbol on line " << linenum << endl;
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
                                qDebug() << "Value must be the number of a CPU device, line " << linenum << endl;
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: number of CPU device on line " << linenum << endl;
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
                                            qDebug() << "Value must be the number of a CPU device, line " << linenum << endl;
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    qDebug() << "Unknown symbol on line " << linenum << endl;
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
                                qDebug() << "Value must be the number of a CPU device, line " << linenum << endl;
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: number of CPU device, line " << linenum << endl;
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
                                            qDebug() << "Value must be lower than 256" << linenum << endl;
                                            goto ende;
                                        }
                                    }
                                }
                                else
                                {
                                    qDebug() << "Unknown symbol ,line" << linenum << endl;
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
                                qDebug() << "Value must be lower than 256, line: " << linenum << endl;
                                goto ende;
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "Expected: number of interrupt, line: " << linenum << endl;
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
                            if (token[i].data(),"bx")
                            {
                                type[i] = 5;
                                value[i][0] = bx;
                                bits = 16;
                            }
                            if (token[i].data(),"cx")
                            {
                                type[i] = 5;
                                value[i][0] = cx;
                                bits = 16;
                            }
                            if (token[i].data(),"dx")
                            {
                                type[i] = 5;
                                value[i][0] = dx;
                                bits = 16;
                            }
                            if (token[i].data(),"sp")
                            {
                                type[i] = 5;
                                value[i][0] = sp;
                                bits = 16;
                            }
                            if (token[i].data(),"bp")
                            {
                                type[i] = 5;
                                value[i][0] = bp;
                                bits = 16;
                            }
                            if (token[i] == QString ("si"))
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
                            bool isplus = token[i].startsWith('+');
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

                    if (curmnem == "mov" && (type[1] == 5) &&
                            (type[2] == 13) && (type[3] == 3))
                    {
                        value[1][1] = value[2][0];
                        value[2][0] = value[3][0];
                        i = 245;
                        if (tunres[3] == true)
                        {
                            qDebug() << "Sorry, this instruction cant use symbols not declared yet " <<	linenum << endl;
                            goto ende;
                        }
                        goto found;
                    }
                    if (curmnem == "mov" && (type[1] == 13) &&
                            (type[2] == 3) && (type[3] == 5))
                    {
                        value[1][1] = value[2][0];
                        value[2][0] =	value[3][0];
                        i = 246;
                        if (tunres[2] == true)
                        {
                            qDebug() << "Sorry, this instruction cant use symbols not declared yet " <<	linenum << endl;
                            goto ende;
                        }
                        goto found;
                    }

                    //Run through all available mnemonic-operand combinations available
                    for (i=0; i<245; i++)
                    {
                        if (Instruction::instructions[i].checkmatch (curmnem,type[1],type[2],bits) ==true)
                            goto found;
                    }
                    //If not success return error
                    qDebug() << "Error: unknown mnemonic/operand combination on line " << linenum << endl;
                    goto ende;
                    //If success write result
found:
                    mem[posinmem+256] = Instruction::instructions[i].getopcode();
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
            }
        }
        else
        {
            end = true;
            mem[RAMAMOUNT+256] = 255;
        }
newline:
        linenum++;
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
                qWarning() << "Undeclared symbol " << unresn[i] << " on line " << unresline[i];
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
        qDebug() << "couldnt open outputfile" << endl;
        goto ende;
    }

    qDebug() << "Assemble successful" << endl;
ende:
    return;
}

void TextModeFileManip::checkConfig (char *filename)
{
    QString configFileName = QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg");
    QFile f (configFileName);
    if (!f.open (QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open config file" << endl;
        return;
    }

    QTextStream s (&f);
    QString dummy;
    int i,x,y;
    ConfStruct config;
//	bool ch;
    s >> dummy;
    s >> i;
    config.maxdev = i;
    s >> dummy;
    s >> i;
    config.maxcost = i;
    s >> dummy;
    s >> i;
    config.maxram = i;
    s >> dummy;
    for (x=0; x<9; x++)
    {
        s >> i;
        config.ramcost[x] = i;
    }
    for (x=0; x<NUMDEV; x++)
    {
        s >> dummy;
        s >> i;
        if (i == 1)
            config.enabled[x] = true;
        else
            config.enabled[x] = false;
        for (y=0; y<5; y++)
        {
            s >> i;
            config.cost[y][x] = i;
            s >> i;
            config.values[y][x] = i;
        }
    }
    f.close();

    QFile b (filename);
    if (!b.open (QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open bot-file" << endl;
        return;
    }
    QDataStream s2 (&b);
    unsigned int lng;
    int cost=0,numdev=0;
    char *tc;
    s2.readBytes (tc,lng);
    unsigned char *my = (unsigned char *) &tc[0];
    if (my[1] > config.maxram)          //Read in all devices
        qDebug() << "ERROR!, Max amount of ram" << endl;
    if (my[1] <= 9)
    {
        cost += config.ramcost[my[1]];
    }
    else
    {
        qDebug() << "ERROR!, file format error" << endl;
    }

    int levelvalue = 0;
    for (x=0; x<32; x++)
    {
        if (my[x*6+2] <= NUMDEV)
        {
            if (config.enabled[my[x*6+2]-1] == false && my[x*6+2] != 0)
                qDebug() << "ERROR!, Using disabled device" << endl;
            if (my[x*6+3] <= 4 && my[x*6+2] > 0)
            {
                numdev++;
                cost += config.cost[my[x*6+3]][my[x*6+2]-1];
                levelvalue = config.values[my[x*6+3]][my[x*6+2]-1];
            }
            if (my[x*6+3] > 4)
            {
                qDebug() << "ERROR!, File format error" << endl;
                levelvalue = 0;
            }
        }
        else
        {
            qDebug() << "ERROR!, File format error" << endl;
        }
    }
    if (numdev > config.maxdev)
        qDebug() << "ERROR!, Max number of devices" << endl;
    if (cost > config.maxcost)
        qDebug() << "ERROR!, Max cost fo bot" << endl;
    delete [] my;

    qDebug() << "Check finished" << endl;
}

void TextModeFileManip::loadConfig (char *filename)
{
    QString fname = QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg");
    QFile f (fname);
    if (!f.open (QIODevice::WriteOnly))
    {
        qDebug() << "Couldnt open current.cfg... check permissions" << endl;
        return;
    }
    fname = filename;
    QFile f2 (fname);
    if (!f2.open (QIODevice::ReadOnly))
    {
        qDebug() << "Couldnt open file ,"<< filename << " not found" << endl;
        return;
    }


    int x,y;

    QTextStream s (&f);
    QTextStream s2 (&f2);

    QString temp;
    s2 >> temp;
    s2 >> temp;
    s << "MAXDEVICES: " << temp << endl;
    s2 >> temp;
    s2 >> temp;
    s << "MAXCOSTS: " << temp << endl;
    s2 >> temp;
    s2 >> temp;
    s << "MAXRAM: " << temp << endl;
    s << "RAMCOSTS:";
    s2 >> temp;
    for (x=0; x<9; x++)
    {
        s2 >> temp;
        s << " " << temp ;
    }
    s << endl;
    for (x=0; x<numdev; x++)
    {
        s2 >> temp;
        s2 >> temp;
        s << "DEVICE: " << temp;
        for (y=0; y<5; y++)
        {
            s2 >> temp;
            s << " " << temp;
            s2 >> temp;
            s << " " << temp;
        }
        s << endl;
    }
    f.close();
    f2.close();
}
