/***************************************************************************
                          instruktion.cpp  -  description
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

#include "instruktion.h"
#include "commonsymbols.h"

// Declare all mnemonics available
// ( mnemonic,arg1type,arg2type,bits,arg1bits,arg2bits,opcode )
const Instruction Instruction::instructions[247] = {
    {"nop", none, none, bit0, bit0, bit0, 0x0},

    {"mov", reg, reg, bit16, bit8, bit8, 0x1},
    {"mov", reg, reg, bit8, bit8, bit8, 0x2},
    {"mov", reg, memc, bit16, bit8, bit16, 0x3},
    {"mov", reg, memc, bit8, bit8, bit16, 0x4},
    {"mov", reg, mreg, bit16, bit8, bit8, 0x5},
    {"mov", reg, mreg, bit8, bit8, bit8, 0x6},
    {"mov", memc, reg, bit16, bit16, bit8, 0x7},
    {"mov", memc, reg, bit8, bit16, bit8, 0x8},
    {"mov", mreg, reg, bit16, bit8, bit8, 0x9},
    {"mov", mreg, reg, bit8, bit8, bit8, 0xA},
    {"mov", reg, val, bit16, bit8, bit16, 0xB},
    {"mov", reg, val, bit8, bit8, bit8, 0xC},
    {"mov", mreg, val, bit16, bit8, bit16, 0xD},
    {"mov", mreg, val, bit8, bit8, bit8, 0xE},
    {"mov", memc, val, bit16, bit16, bit16, 0xF},
    {"mov", memc, val, bit8, bit16, bit8, 0x10},

    {"movsb", none, none, bit0, bit0, bit0, 0x11},
    {"movsw", none, none, bit0, bit0, bit0, 0x12},
    {"stosb", none, none, bit0, bit0, bit0, 0x13},
    {"stosw", none, none, bit0, bit0, bit0, 0x14},

    {"push", reg, none, bit16, bit8, bit0, 0x15},
    {"push", reg, none, bit8, bit8, bit0, 0x16},
    {"push", memc, none, bit16, bit16, bit0, 0x17},
    {"push", memc, none, bit8, bit16, bit0, 0x18},
    {"push", mreg, none, bit16, bit8, bit0, 0x19},
    {"push", mreg, none, bit8, bit8, bit0, 0x1A},
    {"push", val, none, bit16, bit16, bit0, 0x1B},
    {"push", val, none, bit8, bit8, bit0, 0x1C},
    {"pop", reg, none, bit16, bit8, bit0, 0x1D},
    {"pop", reg, none, bit8, bit8, bit0, 0x1E},
    {"pop", memc, none, bit16, bit16, bit0, 0x1F},
    {"pop", memc, none, bit8, bit16, bit0, 0x20},
    {"pop", mreg, none, bit16, bit8, bit0, 0x21},
    {"pop", mreg, none, bit8, bit8, bit0, 0x22},

    {"xchg", reg, reg, bit16, bit8, bit8, 0x23},
    {"xchg", reg, reg, bit8, bit8, bit8, 0x24},
    {"xchg", reg, memc, bit16, bit8, bit16, 0x25},
    {"xchg", reg, memc, bit8, bit8, bit16, 0x26},
    {"xchg", reg, mreg, bit16, bit8, bit8, 0x27},
    {"xchg", reg, mreg, bit8, bit8, bit8, 0x28},

    {"test", reg, val, bit16, bit8, bit8, 0x29},
    {"test", memc, val, bit16, bit16, bit8, 0x2A},
    {"test", mreg, val, bit16, bit8, bit8, 0x2B},
    {"test", reg, none, bit16, bit8, bit0, 0x2C},
    {"test", memc, none, bit16, bit16, bit0, 0x2D},
    {"test", mreg, none, bit16, bit8, bit0, 0x2E},

    {"cmp", reg, reg, bit16, bit8, bit8, 0x2F},
    {"cmp", reg, reg, bit8, bit8, bit8, 0x30},
    {"cmp", reg, memc, bit16, bit8, bit16, 0x31},
    {"cmp", reg, memc, bit8, bit8, bit16, 0x32},
    {"cmp", reg, mreg, bit16, bit8, bit8, 0x33},
    {"cmp", reg, mreg, bit8, bit8, bit8, 0x34},
    {"cmp", reg, val, bit16, bit8, bit16, 0x35},
    {"cmp", reg, val, bit8, bit8, bit8, 0x36},
    {"cmp", mreg, val, bit16, bit8, bit16, 0x37},
    {"cmp", mreg, val, bit8, bit8, bit8, 0x38},
    {"cmp", memc, val, bit16, bit16, bit16, 0x39},
    {"cmp", memc, val, bit8, bit16, bit8, 0x3A},
    {"cmpsb", none, none, bit0, bit0, bit0, 0x3B},

    {"jmp", val, none, bit0, bit16, bit0, 0x3C},
    {"jz", val, none, bit0, bit16, bit0, 0x3D},
    {"jnz", val, none, bit0, bit16, bit0, 0x3E},
    {"jae", val, none, bit0, bit16, bit0, 0x3F},
    {"jnb", val, none, bit0, bit16, bit0, 0x3F},
    {"jbe", val, none, bit0, bit16, bit0, 0x40},
    {"jna", val, none, bit0, bit16, bit0, 0x40},
    {"jmp", reg, none, bit16, bit8, bit0, 0x41},
    {"loop", val, none, bit0, bit16, bit0, 0x42},
    {"call", val, none, bit0, bit16, bit0, 0x43},
    {"ret", none, none, bit0, bit16, bit0, 0x44},
    {"iret", none, none, bit0, bit16, bit0, 0x45},

    {"cli", none, none, bit0, bit0, bit0, 0x46},
    {"sti", none, none, bit0, bit0, bit0, 0x47},

    {"out", val, val, bit0, bit8, bit16, 0x48},
    {"out", val, reg, bit16, bit8, bit8, 0x49},
    {"out", val, mreg, bit16, bit8, bit8, 0x4A},
    {"in", reg, val, bit16, bit8, bit8, 0x4B},

    {"inc", reg, none, bit16, bit8, bit0, 0x4C},
    {"inc", reg, none, bit8, bit8, bit0, 0x4D},
    {"inc", memc, none, bit16, bit16, bit0, 0x4E},
    {"inc", memc, none, bit8, bit16, bit0, 0x4F},
    {"inc", mreg, none, bit16, bit8, bit0, 0x50},
    {"inc", mreg, none, bit8, bit8, bit0, 0x51},
    {"dec", reg, none, bit16, bit8, bit0, 0x52},
    {"dec", reg, none, bit8, bit8, bit0, 0x53},
    {"dec", memc, none, bit16, bit16, bit0, 0x54},
    {"dec", memc, none, bit8, bit16, bit0, 0x55},
    {"dec", mreg, none, bit16, bit8, bit0, 0x56},
    {"dec", mreg, none, bit8, bit8, bit0, 0x57},

    {"add", reg, reg, bit16, bit8, bit8, 0x58},
    {"add", reg, reg, bit8, bit8, bit8, 0x59},
    {"add", reg, val, bit16, bit8, bit16, 0x5A},
    {"add", reg, val, bit8, bit8, bit8, 0x5B},
    {"add", reg, mreg, bit16, bit8, bit8, 0x5C},
    {"add", reg, mreg, bit8, bit8, bit8, 0x5D},
    {"add", reg, memc, bit16, bit8, bit16, 0x5E},
    {"add", reg, memc, bit8, bit8, bit16, 0x5F},
    {"add", mreg, reg, bit16, bit8, bit8, 0x60},
    {"add", mreg, reg, bit8, bit8, bit8, 0x61},
    {"add", mreg, val, bit16, bit8, bit16, 0x62},
    {"add", mreg, val, bit8, bit8, bit8, 0x63},
    {"add", memc, reg, bit16, bit16, bit8, 0x64},
    {"add", memc, reg, bit8, bit16, bit8, 0x65},
    {"add", memc, val, bit16, bit16, bit16, 0x66},
    {"add", memc, val, bit8, bit16, bit8, 0x67},

    {"sub", reg, reg, bit16, bit8, bit8, 0x68},
    {"sub", reg, reg, bit8, bit8, bit8, 0x69},
    {"sub", reg, val, bit16, bit8, bit16, 0x6A},
    {"sub", reg, val, bit8, bit8, bit8, 0x6B},
    {"sub", reg, mreg, bit16, bit8, bit8, 0x6C},
    {"sub", reg, mreg, bit8, bit8, bit8, 0x6D},
    {"sub", reg, memc, bit16, bit8, bit16, 0x6E},
    {"sub", reg, memc, bit8, bit8, bit16, 0x6F},
    {"sub", mreg, reg, bit16, bit8, bit8, 0x70},
    {"sub", mreg, reg, bit8, bit8, bit8, 0x71},
    {"sub", mreg, val, bit16, bit8, bit16, 0x72},
    {"sub", mreg, val, bit8, bit8, bit8, 0x73},
    {"sub", memc, reg, bit16, bit16, bit8, 0x74},
    {"sub", memc, reg, bit8, bit16, bit8, 0x75},
    {"sub", memc, val, bit16, bit16, bit16, 0x76},
    {"sub", memc, val, bit8, bit16, bit8, 0x77},

    {"rol", reg, reg, bit16, bit8, bit8, 0x78},
    {"rol", reg, val, bit16, bit8, bit8, 0x79},
    {"rol", mreg, val, bit16, bit8, bit8, 0x7A},
    {"rol", mreg, reg, bit16, bit8, bit8, 0x7B},
    {"rol", memc, reg, bit16, bit16, bit8, 0x7C},
    {"rol", memc, val, bit16, bit16, bit8, 0x7D},
    {"ror", reg, reg, bit16, bit8, bit8, 0x7E},
    {"ror", reg, val, bit16, bit8, bit8, 0x7F},
    {"ror", mreg, val, bit16, bit8, bit8, 0x80},
    {"ror", mreg, reg, bit16, bit8, bit8, 0x81},
    {"ror", memc, reg, bit16, bit16, bit8, 0x82},
    {"ror", memc, val, bit16, bit16, bit8, 0x83},
    {"imul", none, none, bit0, bit0, bit0, 0x84},
    {"idiv", none, none, bit0, bit0, bit0, 0x85},
    {"ja", val, none, bit0, bit16, bit0, 0x86},
    {"jb", val, none, bit0, bit16, bit0, 0x87},

    {"atanfunc", none, none, bit0, bit0, bit0, 0x88},
    {"sqr", none, none, bit0, bit0, bit0, 0x89},
    {"icmp", reg, reg, bit16, bit8, bit8, 0x8A},
    {"icmp", reg, memc, bit16, bit8, bit16, 0x8B},
    {"icmp", reg, mreg, bit16, bit8, bit8, 0x8C},
    {"icmp", reg, val, bit16, bit8, bit16, 0x8D},
    {"icmp", mreg, val, bit16, bit8, bit16, 0x8E},
    {"icmp", memc, val, bit16, bit16, bit16, 0x8F},
    {"msg", mreg, none, bit16, bit8, bit0, 0x90},
    {"msg", memc, none, bit16, bit16, bit0, 0x91},
    {"err", val, none, bit0, bit8, bit0, 0x92},
    {"readfile", none, none, bit0, bit0, bit0, 0x93},
    {"writefile", none, none, bit0, bit0, bit0, 0x94},
    {"lz", reg, none, bit16, bit8, bit0, 0x95},
    {"lnz", reg, none, bit16, bit8, bit0, 0x96},
    {"la", reg, none, bit16, bit8, bit0, 0x97},

    {"and", reg, reg, bit16, bit8, bit8, 0x98},
    {"and", reg, reg, bit8, bit8, bit8, 0x99},
    {"and", reg, val, bit16, bit8, bit16, 0x9A},
    {"and", reg, val, bit8, bit8, bit8, 0x9B},
    {"and", reg, mreg, bit16, bit8, bit8, 0x9C},
    {"and", reg, mreg, bit8, bit8, bit8, 0x9D},
    {"and", reg, memc, bit16, bit8, bit16, 0x9E},
    {"and", reg, memc, bit8, bit8, bit16, 0x9F},
    {"and", mreg, reg, bit16, bit8, bit8, 0xA0},
    {"and", mreg, reg, bit8, bit8, bit8, 0xA1},
    {"and", mreg, val, bit16, bit8, bit16, 0xA2},
    {"and", mreg, val, bit8, bit8, bit8, 0xA3},
    {"and", memc, reg, bit16, bit16, bit8, 0xA4},
    {"and", memc, reg, bit8, bit16, bit8, 0xA5},
    {"and", memc, val, bit16, bit16, bit16, 0xA6},
    {"and", memc, val, bit8, bit16, bit8, 0xA7},

    {"or", reg, reg, bit16, bit8, bit8, 0xA8},
    {"or", reg, reg, bit8, bit8, bit8, 0xA9},
    {"or", reg, val, bit16, bit8, bit16, 0xAA},
    {"or", reg, val, bit8, bit8, bit8, 0xAB},
    {"or", reg, mreg, bit16, bit8, bit8, 0xAC},
    {"or", reg, mreg, bit8, bit8, bit8, 0xAD},
    {"or", reg, memc, bit16, bit8, bit16, 0xAE},
    {"or", reg, memc, bit8, bit8, bit16, 0xAF},
    {"or", mreg, reg, bit16, bit8, bit8, 0xB0},
    {"or", mreg, reg, bit8, bit8, bit8, 0xB1},
    {"or", mreg, val, bit16, bit8, bit16, 0xB2},
    {"or", mreg, val, bit8, bit8, bit8, 0xB3},
    {"or", memc, reg, bit16, bit16, bit8, 0xB4},
    {"or", memc, reg, bit8, bit16, bit8, 0xB5},
    {"or", memc, val, bit16, bit16, bit16, 0xB6},
    {"or", memc, val, bit8, bit16, bit8, 0xB7},

    {"xor", reg, reg, bit16, bit8, bit8, 0xB8},
    {"xor", reg, reg, bit8, bit8, bit8, 0xB9},
    {"xor", reg, val, bit16, bit8, bit16, 0xBA},
    {"xor", reg, val, bit8, bit8, bit8, 0xBB},
    {"xor", reg, mreg, bit16, bit8, bit8, 0xBC},
    {"xor", reg, mreg, bit8, bit8, bit8, 0xBD},
    {"xor", reg, memc, bit16, bit8, bit16, 0xBE},
    {"xor", reg, memc, bit8, bit8, bit16, 0xBF},
    {"xor", mreg, reg, bit16, bit8, bit8, 0xC0},
    {"xor", mreg, reg, bit8, bit8, bit8, 0xC1},
    {"xor", mreg, val, bit16, bit8, bit16, 0xC2},
    {"xor", mreg, val, bit8, bit8, bit8, 0xC3},
    {"xor", memc, reg, bit16, bit16, bit8, 0xC4},
    {"xor", memc, reg, bit8, bit16, bit8, 0xC5},
    {"xor", memc, val, bit16, bit16, bit16, 0xC6},
    {"xor", memc, val, bit8, bit16, bit8, 0xC7},

    {"shl", reg, val, bit16, bit8, bit8, 0xC8},
    {"shl", reg, reg, bit16, bit8, bit8, 0xC9},
    {"shl", mreg, val, bit16, bit8, bit8, 0xCA},
    {"shl", mreg, reg, bit16, bit8, bit8, 0xCB},
    {"shl", memc, val, bit16, bit16, bit8, 0xCC},
    {"shl", memc, reg, bit16, bit16, bit8, 0xCD},
    {"shr", reg, val, bit16, bit8, bit8, 0xCE},
    {"shr", reg, reg, bit16, bit8, bit8, 0xCF},
    {"shr", mreg, val, bit16, bit8, bit8, 0xD0},
    {"shr", mreg, reg, bit16, bit8, bit8, 0xD1},
    {"shr", memc, val, bit16, bit16, bit8, 0xD2},
    {"shr", memc, reg, bit16, bit16, bit8, 0xD3},

    {"ishl", reg, val, bit16, bit8, bit8, 0xD4},
    {"ishl", reg, reg, bit16, bit8, bit8, 0xD5},
    {"ishl", mreg, val, bit16, bit8, bit8, 0xD6},
    {"ishl", mreg, reg, bit16, bit8, bit8, 0xD7},
    {"ishl", memc, val, bit16, bit16, bit8, 0xD8},
    {"ishl", memc, reg, bit16, bit16, bit8, 0xD9},
    {"ishr", reg, val, bit16, bit8, bit8, 0xDA},
    {"ishr", reg, reg, bit16, bit8, bit8, 0xDB},
    {"ishr", mreg, val, bit16, bit8, bit8, 0xDC},
    {"ishr", mreg, reg, bit16, bit8, bit8, 0xDD},
    {"ishr", memc, val, bit16, bit16, bit8, 0xDE},
    {"ishr", memc, reg, bit16, bit16, bit8, 0xDF},

    {"int", val, none, bit0, bit16, bit0, 0xE0},
    {"mul", none, none, bit0, bit0, bit0, 0xE1},
    {"div", none, none, bit0, bit0, bit0, 0xE2},

    {"ret", val, none, bit0, bit8, bit0, 0xE3},
    {"lodsb", none, none, bit0, bit0, bit0, 0xE4},
    {"lodsw", none, none, bit0, bit0, bit0, 0xE5},
    {"sinfunc", none, none, bit0, bit0, bit0, 0xE6},
    {"cosfunc", none, none, bit0, bit0, bit0, 0xE7},
    {"sin", none, none, bit0, bit0, bit0, 0xE8},
    {"cos", none, none, bit0, bit0, bit0, 0xE9},

    {"mov", val, val, bit16, bit16, bit8, 0xEA},
    {"mov", val, val, bit16, bit16, bit8, 0xEB},
    {"rnd", none, none, bit0, bit0, bit0, 0xEC},
    {"hwait", none, none, bit0, bit0, bit0, 0xED},

    {"lb", reg, none, bit16, bit8, bit0, 0xEE},
    {"lae", reg, none, bit16, bit8, bit0, 0xEF},
    {"lnb", reg, none, bit16, bit8, bit0, 0xEF},
    {"lbe", reg, none, bit16, bit8, bit0, 0xF0},
    {"lna", reg, none, bit16, bit8, bit0, 0xF0},
    {"cj", reg, val, bit16, bit8, bit16, 0xF1},
    {"cjn", reg, val, bit16, bit8, bit16, 0xF2}
};

//Contains info about one mnemonic/operand combination for the assembler

Instruction::Instruction (const char mnem[],int arg1t,int arg2t,int bit,int arg1b,
                          int arg2b,int op)
{
    mnemonic = new char[strlen (mnem) + 1];
    for (unsigned int x=0; x<strlen (mnem) +1; x++)
        mnemonic[x] = mnem[x];
    arg1type = arg1t;
    arg2type = arg2t;
    bits = bit;
    arg1bits = arg1b;
    arg2bits = arg2b;
    opcode = op;
}

Instruction::~Instruction()
{
    delete mnemonic;
}

/**
	* Compares the mnemonic it has stored
	* with the parameters
	*/
bool Instruction::checkmatch (QString &mnem, int arg1t, int arg2t, int bit) const
{
    if (mnem == mnemonic && arg1type == arg1t && arg2type ==
            arg2t && ( (bit == bits || bits == 0) || (bit == 0 && bits == 16)))
        return true;
    else
        return false;
}

/**
	* returns the objects opcode
	*/
unsigned char Instruction::getopcode() const
{
    return opcode;
}

/**
	* Returns the sizes of the operands
	*/

int Instruction::getarg1bits() const
{
    return arg1bits;
}
int Instruction::getarg2bits() const
{
    return arg2bits;
}
