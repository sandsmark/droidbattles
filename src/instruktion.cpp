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
    { "nop", None, None, Size0, Size0, Size0, 0x0 },

    { "mov", Register, Register, Size16, Size8, Size8, 0x1 },
    { "mov", Register, Register, Size8, Size8, Size8, 0x2 },
    { "mov", Register, MemAddress, Size16, Size8, Size16, 0x3 },
    { "mov", Register, MemAddress, Size8, Size8, Size16, 0x4 },
    { "mov", Register, RegisterRef, Size16, Size8, Size8, 0x5 },
    { "mov", Register, RegisterRef, Size8, Size8, Size8, 0x6 },
    { "mov", MemAddress, Register, Size16, Size16, Size8, 0x7 },
    { "mov", MemAddress, Register, Size8, Size16, Size8, 0x8 },
    { "mov", RegisterRef, Register, Size16, Size8, Size8, 0x9 },
    { "mov", RegisterRef, Register, Size8, Size8, Size8, 0xA },
    { "mov", Register, Value, Size16, Size8, Size16, 0xB },
    { "mov", Register, Value, Size8, Size8, Size8, 0xC },
    { "mov", RegisterRef, Value, Size16, Size8, Size16, 0xD },
    { "mov", RegisterRef, Value, Size8, Size8, Size8, 0xE },
    { "mov", MemAddress, Value, Size16, Size16, Size16, 0xF },
    { "mov", MemAddress, Value, Size8, Size16, Size8, 0x10 },

    { "movsb", None, None, Size0, Size0, Size0, 0x11 },
    { "movsw", None, None, Size0, Size0, Size0, 0x12 },
    { "stosb", None, None, Size0, Size0, Size0, 0x13 },
    { "stosw", None, None, Size0, Size0, Size0, 0x14 },

    { "push", Register, None, Size16, Size8, Size0, 0x15 },
    { "push", Register, None, Size8, Size8, Size0, 0x16 },
    { "push", MemAddress, None, Size16, Size16, Size0, 0x17 },
    { "push", MemAddress, None, Size8, Size16, Size0, 0x18 },
    { "push", RegisterRef, None, Size16, Size8, Size0, 0x19 },
    { "push", RegisterRef, None, Size8, Size8, Size0, 0x1A },
    { "push", Value, None, Size16, Size16, Size0, 0x1B },
    { "push", Value, None, Size8, Size8, Size0, 0x1C },
    { "pop", Register, None, Size16, Size8, Size0, 0x1D },
    { "pop", Register, None, Size8, Size8, Size0, 0x1E },
    { "pop", MemAddress, None, Size16, Size16, Size0, 0x1F },
    { "pop", MemAddress, None, Size8, Size16, Size0, 0x20 },
    { "pop", RegisterRef, None, Size16, Size8, Size0, 0x21 },
    { "pop", RegisterRef, None, Size8, Size8, Size0, 0x22 },

    { "xchg", Register, Register, Size16, Size8, Size8, 0x23 },
    { "xchg", Register, Register, Size8, Size8, Size8, 0x24 },
    { "xchg", Register, MemAddress, Size16, Size8, Size16, 0x25 },
    { "xchg", Register, MemAddress, Size8, Size8, Size16, 0x26 },
    { "xchg", Register, RegisterRef, Size16, Size8, Size8, 0x27 },
    { "xchg", Register, RegisterRef, Size8, Size8, Size8, 0x28 },

    { "test", Register, Value, Size16, Size8, Size8, 0x29 },
    { "test", MemAddress, Value, Size16, Size16, Size8, 0x2A },
    { "test", RegisterRef, Value, Size16, Size8, Size8, 0x2B },
    { "test", Register, None, Size16, Size8, Size0, 0x2C },
    { "test", MemAddress, None, Size16, Size16, Size0, 0x2D },
    { "test", RegisterRef, None, Size16, Size8, Size0, 0x2E },

    { "cmp", Register, Register, Size16, Size8, Size8, 0x2F },
    { "cmp", Register, Register, Size8, Size8, Size8, 0x30 },
    { "cmp", Register, MemAddress, Size16, Size8, Size16, 0x31 },
    { "cmp", Register, MemAddress, Size8, Size8, Size16, 0x32 },
    { "cmp", Register, RegisterRef, Size16, Size8, Size8, 0x33 },
    { "cmp", Register, RegisterRef, Size8, Size8, Size8, 0x34 },
    { "cmp", Register, Value, Size16, Size8, Size16, 0x35 },
    { "cmp", Register, Value, Size8, Size8, Size8, 0x36 },
    { "cmp", RegisterRef, Value, Size16, Size8, Size16, 0x37 },
    { "cmp", RegisterRef, Value, Size8, Size8, Size8, 0x38 },
    { "cmp", MemAddress, Value, Size16, Size16, Size16, 0x39 },
    { "cmp", MemAddress, Value, Size8, Size16, Size8, 0x3A },
    { "cmpsb", None, None, Size0, Size0, Size0, 0x3B },

    { "jmp", Value, None, Size0, Size16, Size0, 0x3C },
    { "jz", Value, None, Size0, Size16, Size0, 0x3D },
    { "jnz", Value, None, Size0, Size16, Size0, 0x3E },
    { "jae", Value, None, Size0, Size16, Size0, 0x3F },
    { "jnb", Value, None, Size0, Size16, Size0, 0x3F },
    { "jbe", Value, None, Size0, Size16, Size0, 0x40 },
    { "jna", Value, None, Size0, Size16, Size0, 0x40 },
    { "jmp", Register, None, Size16, Size8, Size0, 0x41 },
    { "loop", Value, None, Size0, Size16, Size0, 0x42 },
    { "call", Value, None, Size0, Size16, Size0, 0x43 },
    { "ret", None, None, Size0, Size16, Size0, 0x44 },
    { "iret", None, None, Size0, Size16, Size0, 0x45 },

    { "cli", None, None, Size0, Size0, Size0, 0x46 },
    { "sti", None, None, Size0, Size0, Size0, 0x47 },

    { "out", Value, Value, Size0, Size8, Size16, 0x48 },
    { "out", Value, Register, Size16, Size8, Size8, 0x49 },
    { "out", Value, RegisterRef, Size16, Size8, Size8, 0x4A },
    { "in", Register, Value, Size16, Size8, Size8, 0x4B },

    { "inc", Register, None, Size16, Size8, Size0, 0x4C },
    { "inc", Register, None, Size8, Size8, Size0, 0x4D },
    { "inc", MemAddress, None, Size16, Size16, Size0, 0x4E },
    { "inc", MemAddress, None, Size8, Size16, Size0, 0x4F },
    { "inc", RegisterRef, None, Size16, Size8, Size0, 0x50 },
    { "inc", RegisterRef, None, Size8, Size8, Size0, 0x51 },
    { "dec", Register, None, Size16, Size8, Size0, 0x52 },
    { "dec", Register, None, Size8, Size8, Size0, 0x53 },
    { "dec", MemAddress, None, Size16, Size16, Size0, 0x54 },
    { "dec", MemAddress, None, Size8, Size16, Size0, 0x55 },
    { "dec", RegisterRef, None, Size16, Size8, Size0, 0x56 },
    { "dec", RegisterRef, None, Size8, Size8, Size0, 0x57 },

    { "add", Register, Register, Size16, Size8, Size8, 0x58 },
    { "add", Register, Register, Size8, Size8, Size8, 0x59 },
    { "add", Register, Value, Size16, Size8, Size16, 0x5A },
    { "add", Register, Value, Size8, Size8, Size8, 0x5B },
    { "add", Register, RegisterRef, Size16, Size8, Size8, 0x5C },
    { "add", Register, RegisterRef, Size8, Size8, Size8, 0x5D },
    { "add", Register, MemAddress, Size16, Size8, Size16, 0x5E },
    { "add", Register, MemAddress, Size8, Size8, Size16, 0x5F },
    { "add", RegisterRef, Register, Size16, Size8, Size8, 0x60 },
    { "add", RegisterRef, Register, Size8, Size8, Size8, 0x61 },
    { "add", RegisterRef, Value, Size16, Size8, Size16, 0x62 },
    { "add", RegisterRef, Value, Size8, Size8, Size8, 0x63 },
    { "add", MemAddress, Register, Size16, Size16, Size8, 0x64 },
    { "add", MemAddress, Register, Size8, Size16, Size8, 0x65 },
    { "add", MemAddress, Value, Size16, Size16, Size16, 0x66 },
    { "add", MemAddress, Value, Size8, Size16, Size8, 0x67 },

    { "sub", Register, Register, Size16, Size8, Size8, 0x68 },
    { "sub", Register, Register, Size8, Size8, Size8, 0x69 },
    { "sub", Register, Value, Size16, Size8, Size16, 0x6A },
    { "sub", Register, Value, Size8, Size8, Size8, 0x6B },
    { "sub", Register, RegisterRef, Size16, Size8, Size8, 0x6C },
    { "sub", Register, RegisterRef, Size8, Size8, Size8, 0x6D },
    { "sub", Register, MemAddress, Size16, Size8, Size16, 0x6E },
    { "sub", Register, MemAddress, Size8, Size8, Size16, 0x6F },
    { "sub", RegisterRef, Register, Size16, Size8, Size8, 0x70 },
    { "sub", RegisterRef, Register, Size8, Size8, Size8, 0x71 },
    { "sub", RegisterRef, Value, Size16, Size8, Size16, 0x72 },
    { "sub", RegisterRef, Value, Size8, Size8, Size8, 0x73 },
    { "sub", MemAddress, Register, Size16, Size16, Size8, 0x74 },
    { "sub", MemAddress, Register, Size8, Size16, Size8, 0x75 },
    { "sub", MemAddress, Value, Size16, Size16, Size16, 0x76 },
    { "sub", MemAddress, Value, Size8, Size16, Size8, 0x77 },

    { "rol", Register, Register, Size16, Size8, Size8, 0x78 },
    { "rol", Register, Value, Size16, Size8, Size8, 0x79 },
    { "rol", RegisterRef, Value, Size16, Size8, Size8, 0x7A },
    { "rol", RegisterRef, Register, Size16, Size8, Size8, 0x7B },
    { "rol", MemAddress, Register, Size16, Size16, Size8, 0x7C },
    { "rol", MemAddress, Value, Size16, Size16, Size8, 0x7D },
    { "ror", Register, Register, Size16, Size8, Size8, 0x7E },
    { "ror", Register, Value, Size16, Size8, Size8, 0x7F },
    { "ror", RegisterRef, Value, Size16, Size8, Size8, 0x80 },
    { "ror", RegisterRef, Register, Size16, Size8, Size8, 0x81 },
    { "ror", MemAddress, Register, Size16, Size16, Size8, 0x82 },
    { "ror", MemAddress, Value, Size16, Size16, Size8, 0x83 },
    { "imul", None, None, Size0, Size0, Size0, 0x84 },
    { "idiv", None, None, Size0, Size0, Size0, 0x85 },
    { "ja", Value, None, Size0, Size16, Size0, 0x86 },
    { "jb", Value, None, Size0, Size16, Size0, 0x87 },

    { "atanfunc", None, None, Size0, Size0, Size0, 0x88 },
    { "sqr", None, None, Size0, Size0, Size0, 0x89 },
    { "icmp", Register, Register, Size16, Size8, Size8, 0x8A },
    { "icmp", Register, MemAddress, Size16, Size8, Size16, 0x8B },
    { "icmp", Register, RegisterRef, Size16, Size8, Size8, 0x8C },
    { "icmp", Register, Value, Size16, Size8, Size16, 0x8D },
    { "icmp", RegisterRef, Value, Size16, Size8, Size16, 0x8E },
    { "icmp", MemAddress, Value, Size16, Size16, Size16, 0x8F },
    { "msg", RegisterRef, None, Size16, Size8, Size0, 0x90 },
    { "msg", MemAddress, None, Size16, Size16, Size0, 0x91 },
    { "err", Value, None, Size0, Size8, Size0, 0x92 },
    { "readfile", None, None, Size0, Size0, Size0, 0x93 },
    { "writefile", None, None, Size0, Size0, Size0, 0x94 },
    { "lz", Register, None, Size16, Size8, Size0, 0x95 },
    { "lnz", Register, None, Size16, Size8, Size0, 0x96 },
    { "la", Register, None, Size16, Size8, Size0, 0x97 },

    { "and", Register, Register, Size16, Size8, Size8, 0x98 },
    { "and", Register, Register, Size8, Size8, Size8, 0x99 },
    { "and", Register, Value, Size16, Size8, Size16, 0x9A },
    { "and", Register, Value, Size8, Size8, Size8, 0x9B },
    { "and", Register, RegisterRef, Size16, Size8, Size8, 0x9C },
    { "and", Register, RegisterRef, Size8, Size8, Size8, 0x9D },
    { "and", Register, MemAddress, Size16, Size8, Size16, 0x9E },
    { "and", Register, MemAddress, Size8, Size8, Size16, 0x9F },
    { "and", RegisterRef, Register, Size16, Size8, Size8, 0xA0 },
    { "and", RegisterRef, Register, Size8, Size8, Size8, 0xA1 },
    { "and", RegisterRef, Value, Size16, Size8, Size16, 0xA2 },
    { "and", RegisterRef, Value, Size8, Size8, Size8, 0xA3 },
    { "and", MemAddress, Register, Size16, Size16, Size8, 0xA4 },
    { "and", MemAddress, Register, Size8, Size16, Size8, 0xA5 },
    { "and", MemAddress, Value, Size16, Size16, Size16, 0xA6 },
    { "and", MemAddress, Value, Size8, Size16, Size8, 0xA7 },

    { "or", Register, Register, Size16, Size8, Size8, 0xA8 },
    { "or", Register, Register, Size8, Size8, Size8, 0xA9 },
    { "or", Register, Value, Size16, Size8, Size16, 0xAA },
    { "or", Register, Value, Size8, Size8, Size8, 0xAB },
    { "or", Register, RegisterRef, Size16, Size8, Size8, 0xAC },
    { "or", Register, RegisterRef, Size8, Size8, Size8, 0xAD },
    { "or", Register, MemAddress, Size16, Size8, Size16, 0xAE },
    { "or", Register, MemAddress, Size8, Size8, Size16, 0xAF },
    { "or", RegisterRef, Register, Size16, Size8, Size8, 0xB0 },
    { "or", RegisterRef, Register, Size8, Size8, Size8, 0xB1 },
    { "or", RegisterRef, Value, Size16, Size8, Size16, 0xB2 },
    { "or", RegisterRef, Value, Size8, Size8, Size8, 0xB3 },
    { "or", MemAddress, Register, Size16, Size16, Size8, 0xB4 },
    { "or", MemAddress, Register, Size8, Size16, Size8, 0xB5 },
    { "or", MemAddress, Value, Size16, Size16, Size16, 0xB6 },
    { "or", MemAddress, Value, Size8, Size16, Size8, 0xB7 },

    { "xor", Register, Register, Size16, Size8, Size8, 0xB8 },
    { "xor", Register, Register, Size8, Size8, Size8, 0xB9 },
    { "xor", Register, Value, Size16, Size8, Size16, 0xBA },
    { "xor", Register, Value, Size8, Size8, Size8, 0xBB },
    { "xor", Register, RegisterRef, Size16, Size8, Size8, 0xBC },
    { "xor", Register, RegisterRef, Size8, Size8, Size8, 0xBD },
    { "xor", Register, MemAddress, Size16, Size8, Size16, 0xBE },
    { "xor", Register, MemAddress, Size8, Size8, Size16, 0xBF },
    { "xor", RegisterRef, Register, Size16, Size8, Size8, 0xC0 },
    { "xor", RegisterRef, Register, Size8, Size8, Size8, 0xC1 },
    { "xor", RegisterRef, Value, Size16, Size8, Size16, 0xC2 },
    { "xor", RegisterRef, Value, Size8, Size8, Size8, 0xC3 },
    { "xor", MemAddress, Register, Size16, Size16, Size8, 0xC4 },
    { "xor", MemAddress, Register, Size8, Size16, Size8, 0xC5 },
    { "xor", MemAddress, Value, Size16, Size16, Size16, 0xC6 },
    { "xor", MemAddress, Value, Size8, Size16, Size8, 0xC7 },

    { "shl", Register, Value, Size16, Size8, Size8, 0xC8 },
    { "shl", Register, Register, Size16, Size8, Size8, 0xC9 },
    { "shl", RegisterRef, Value, Size16, Size8, Size8, 0xCA },
    { "shl", RegisterRef, Register, Size16, Size8, Size8, 0xCB },
    { "shl", MemAddress, Value, Size16, Size16, Size8, 0xCC },
    { "shl", MemAddress, Register, Size16, Size16, Size8, 0xCD },
    { "shr", Register, Value, Size16, Size8, Size8, 0xCE },
    { "shr", Register, Register, Size16, Size8, Size8, 0xCF },
    { "shr", RegisterRef, Value, Size16, Size8, Size8, 0xD0 },
    { "shr", RegisterRef, Register, Size16, Size8, Size8, 0xD1 },
    { "shr", MemAddress, Value, Size16, Size16, Size8, 0xD2 },
    { "shr", MemAddress, Register, Size16, Size16, Size8, 0xD3 },

    { "ishl", Register, Value, Size16, Size8, Size8, 0xD4 },
    { "ishl", Register, Register, Size16, Size8, Size8, 0xD5 },
    { "ishl", RegisterRef, Value, Size16, Size8, Size8, 0xD6 },
    { "ishl", RegisterRef, Register, Size16, Size8, Size8, 0xD7 },
    { "ishl", MemAddress, Value, Size16, Size16, Size8, 0xD8 },
    { "ishl", MemAddress, Register, Size16, Size16, Size8, 0xD9 },
    { "ishr", Register, Value, Size16, Size8, Size8, 0xDA },
    { "ishr", Register, Register, Size16, Size8, Size8, 0xDB },
    { "ishr", RegisterRef, Value, Size16, Size8, Size8, 0xDC },
    { "ishr", RegisterRef, Register, Size16, Size8, Size8, 0xDD },
    { "ishr", MemAddress, Value, Size16, Size16, Size8, 0xDE },
    { "ishr", MemAddress, Register, Size16, Size16, Size8, 0xDF },

    { "int", Value, None, Size0, Size16, Size0, 0xE0 },
    { "mul", None, None, Size0, Size0, Size0, 0xE1 },
    { "div", None, None, Size0, Size0, Size0, 0xE2 },

    { "ret", Value, None, Size0, Size8, Size0, 0xE3 },
    { "lodsb", None, None, Size0, Size0, Size0, 0xE4 },
    { "lodsw", None, None, Size0, Size0, Size0, 0xE5 },
    { "sinfunc", None, None, Size0, Size0, Size0, 0xE6 },
    { "cosfunc", None, None, Size0, Size0, Size0, 0xE7 },
    { "sin", None, None, Size0, Size0, Size0, 0xE8 },
    { "cos", None, None, Size0, Size0, Size0, 0xE9 },

    { "mov", Value, Value, Size16, Size16, Size8, 0xEA },
    { "mov", Value, Value, Size16, Size16, Size8, 0xEB },
    { "rnd", None, None, Size0, Size0, Size0, 0xEC },
    { "hwait", None, None, Size0, Size0, Size0, 0xED },

    { "lb", Register, None, Size16, Size8, Size0, 0xEE },
    { "lae", Register, None, Size16, Size8, Size0, 0xEF },
    { "lnb", Register, None, Size16, Size8, Size0, 0xEF },
    { "lbe", Register, None, Size16, Size8, Size0, 0xF0 },
    { "lna", Register, None, Size16, Size8, Size0, 0xF0 },
    { "cj", Register, Value, Size16, Size8, Size16, 0xF1 },
    { "cjn", Register, Value, Size16, Size8, Size16, 0xF2 }
};

//Contains info about one mnemonic/operand combination for the assembler

Instruction::Instruction(const char mnem[], int arg1t, int arg2t, int bit, int arg1b,
                         int arg2b, int op)
{
    mnemonic = new char[strlen(mnem) + 1];
    for (unsigned int x = 0; x < strlen(mnem) + 1; x++) {
        mnemonic[x] = mnem[x];
    }
    arg1type = arg1t;
    arg2type = arg2t;
    bits = bit;
    arg1bits = arg1b;
    arg2bits = arg2b;
    opcode = op;
}

Instruction::~Instruction()
{
    delete[] mnemonic;
}

/**
	* Compares the mnemonic it has stored
	* with the parameters
	*/
bool Instruction::checkmatch(QString &mnem, int arg1t, int arg2t, int bit) const
{
    if (mnem == mnemonic && arg1type == arg1t && arg2type == arg2t && ((bit == bits || bits == 0) || (bit == 0 && bits == 16))) {
        return true;
    } else {
        return false;
    }
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

Instruction::Types Instruction::getarg1type() const
{
    return Types(arg1type);
}

Instruction::Types Instruction::getarg2type() const
{
    return Types(arg2type);
}

QString Instruction::token() const
{
    return QString::fromLatin1(mnemonic);
}
