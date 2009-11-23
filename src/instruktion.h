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

class instruktion
{

public:

    instruktion (char mnem[],int arg1t,int arg2t,int bit,int arg1b,int arg2b,
                 int op);
    ~instruktion();
    bool checkmatch (QString &mnem, int arg1t, int arg2t, int bits);
    unsigned char getopcode();
    int getarg1bits();
    int getarg2bits();

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
