/***************************************************************************
                          instruktion.h  -  description
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

#ifndef INSTRUKTION_H
#define INSTRUKTION_H

#include <qstring.h>

/**
	* Contains one opcode and it's corresponding mnemonic/operand combination.
	* The assembler creates alot of objects of this type
  * @author Andreas Agorander
  */

class Instruction
{
public:
    //Assembler Instruction declaration constants
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
    //	  14-%interrupt
    enum Types {
        None = 0,
        Label = 1,
        Mnemonic = 2,
        Value = 3,
        MemAddress = 4,
        Register = 5,
        ConstDecl = 6,
        Offset = 7,
        VarDecl = 8,
        CpuBoot = 9,
        CpuStack = 10,
        Db = 11,
        BitId = 12,
        RegisterRef = 13,
        Interrupt = 14
    };

    enum Size {
        Size0 = 0,
        Size8 = 8,
        Size16 = 16
    };

    const static Instruction instructions[247];

    Instruction (const char mnem[],int arg1t,int arg2t,int bit,int arg1b,int arg2b,
                 int op);
    ~Instruction();
    bool checkmatch (QString &mnem, int arg1t, int arg2t, int bits) const;
    unsigned char getopcode() const;
    int getarg1bits() const;
    int getarg2bits() const;

private:

    char *mnemonic;
    int arg1type;
    int arg2type;
    int arg1bits;
    int arg2bits;
    int bits;
    unsigned char opcode;

};

#endif
