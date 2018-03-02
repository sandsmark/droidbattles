/***************************************************************************
                          robcpu.cpp  -  description
                             -------------------
    begin                : Mon Apr 3 2000
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

#include "robcpu.h"
extern bool SingleStepMode;  // defined in battlearea.h

//#include <qmessagebox.h>
robCPU::robCPU( )
{
}

robCPU::robCPU( RAM &ramdev,screenobject &object,int arg1,int arg2,int arg3,
								int arg4,int arg5 )
{
	ourlevel = arg1;
	mem = &ramdev;
	ourbot = &object;
	registers = new unsigned short[256];
	bit8reg = ( unsigned char* ) &registers[0];
	iregisters = ( signed short* ) &registers[0];
	ibit8reg = ( signed char* ) &registers[0];
	bootmem = arg2+arg3*256;
	stackmem = arg4+arg5*256;
	registers[eip] = bootmem;
	registers[sp] = stackmem;

	int count,count2;
	for( count=0;count<4;count++ )
	{
		for( count2=0;count2<4;count2++ )
		{
			stacktaken[count][count2]=false;
			portstack[count][count2]=0;
		}
	}
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
	cyclesleft = 0;
}


robCPU::~robCPU( )
{
	delete registers;
}

void robCPU::execute( )
{
	cyclesleft += ourlevel;
	if( stacktaken[0][0] == true )// Port 0, cause interrupt
	{
		int inter = portstack[0][0];
		moveportstack( 0 );

		int temp = mem->returnsize( )-(inter*2+2);// Get interrupt vector
		if( mem->getword(temp) != 0xFFFF )
		{
			mem->setword( registers[sp], registers[eip] );// Save current eip on stack
			int tt = mem->returnsize( );
			registers[eip] = mem->getword( tt-(inter*2+2) );
			registers[sp] += 2;
			registers[flags] &= 0xFBFF; // clear interrupt flag
		}
	}
	execinstr( );  //Execute instruction
}

int robCPU::returntype( )
{
	return 9;
}

	/**
		* If ints is enabled return 5, else 4
		*/
int robCPU::returnspecial( )
{
	if( (registers[flags] & 0x0400) == 0x0400 )
		return 5;
	else
		return 4;
}

	/**
		* Returns debug information in a struct
		*/
struct debugcontents robCPU::returndbg( )
{
	struct debugcontents temp;
	temp.flags = registers[flags];
	temp.ax = registers[ax];
	temp.bx = registers[bx];
	temp.cx = registers[cx];
	temp.dx = registers[dx];
	temp.bp = registers[bp];
	temp.sp = registers[sp];
	temp.si = registers[si];
	temp.di = registers[di];
	temp.ip = registers[eip];

	int x;
	for( x=-4;x<5;x++ )
	{
		temp.ipcontents[x+4] = mem->getbyte( registers[eip]+x );
		temp.spcontents[x+4] = mem->getbyte( registers[sp]+x );
		temp.dicontents[x+4] = mem->getbyte( registers[di]+x );
		temp.sicontents[x+4] = mem->getbyte( registers[si]+x );
	}

	for( x=0;x<30;x++ )
		temp.execmem[x] = lastexecmem[x];

	return temp;
}

	/**
		* Sends a "message" to the infowindow
		*/
void robCPU::sendmsg( char *msg )
{
	ourbot->sendmsg( msg );
}

void robCPU::execinstr( )
{
	//Declare the temporary variables used
	int test1;
	int test2;
	int x;
	int temp;
	int test,tt,argum;
	unsigned int intpart,restpart,result;
	signed int iintpart,irestpart,iresult;
	unsigned short rtemp;
	char status;
	unsigned char bit;
	char message[20];
	int execmementry=0;
	for( x=0;x<30;x++ )
		lastexecmem[x] = -1;

	while( cyclesleft > 0 )
	{
		unsigned char instr = mem->getbyte( registers[eip] );  //Get the opcode
		if( execmementry < 30 )lastexecmem[execmementry++] = registers[eip];
		cyclesleft -= instrlatency[instr];
		switch ( instr )
		{
			//NOP
			case 0x00 :
				registers[eip]++;
			break;

			//MOV reg,reg 16 bit
			case 0x01 :
				registers[mem->getbyte(registers[eip]+1)] =
					registers[mem->getbyte(registers[eip]+2)];
				registers[eip] += 3;
			break;

			//MOV reg,reg 8 bit
			case 0x02 :
				bit8reg[mem->getbyte(registers[eip]+1)] =
					bit8reg[mem->getbyte(registers[eip]+2)];
				registers[eip] += 3;
			break;

			//MOV reg,mem 16 bit
			case 0x03 :
				registers[mem->getbyte(registers[eip]+1)] =
					mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] +=4;
			break;

			//MOV reg,mem 8 bit
			case 0x04 :
				bit8reg[mem->getbyte(registers[eip]+1)] =
					mem->getbyte(mem->getword(registers[eip]+2));
				registers[eip] += 4;
			break;

			//MOV reg,[reg] 16 bit
			case 0x05 :
				registers[mem->getbyte(registers[eip]+1)] =
					mem->getword(registers[mem->getbyte(registers[eip]+2)]);
				registers[eip] += 3;
			break;

			//MOV reg,[reg] 8 bit
			case 0x06 :
				bit8reg[mem->getbyte(registers[eip]+1)] =
					mem->getbyte(registers[mem->getbyte(registers[eip]+2)]);
				registers[eip] += 3;
			break;

			//MOV mem,reg 16 bit
			case 0x07 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					registers[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//MOV mem,reg 8 bit
			case 0x08 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					bit8reg[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//MOV [reg],reg 16 bit
			case 0x09 :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )],
					registers[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//MOV [reg],reg 8 bit
			case 0x0A :
				mem->setbyte( registers[mem->getbyte( registers[eip]+1 )],
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//MOV reg,imm 16 bit
			case 0x0B :
				registers[mem->getbyte(registers[eip]+1)] =
					mem->getword(registers[eip]+2);
				registers[eip] += 4;
			break;

			//MOV reg,imm 8 bit
			case 0x0C :
				bit8reg[mem->getbyte(registers[eip]+1)] =
					mem->getbyte(registers[eip]+2);
				registers[eip] += 3;
			break;

			//MOV [reg],imm 16 bit
			case 0x0D :
				mem->setword( registers[mem->getbyte(registers[eip]+1)],
					mem->getword( registers[eip]+2 ));
				registers[eip] += 4;
			break;

			//MOV [reg],imm 8 bit
			case 0x0E :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)],
					mem->getbyte( registers[eip]+2 ));
				registers[eip] += 3;
			break;

			//MOV mem,imm 16 bit
			case 0x0F :
				mem->setword( mem->getword(registers[eip]+1),
					mem->getword(registers[eip]+3) );
				registers[eip] += 5;
			break;

			//MOV mem,imm 8 bit
			case 0x10 :
				mem->setbyte( mem->getword(registers[eip]+1),
					mem->getbyte(registers[eip]+3) );
				registers[eip] += 4;
			break;

			//MOVSB
			case 0x11 :
				temp = registers[cx];
				for( x=0;x<temp;x++ )
				{
					mem->setbyte( registers[di],mem->getbyte( registers[si] ) );
					registers[di]++;
					registers[si]++;
				}
				registers[eip]++;
			break;

			//MOVSW
			case 0x12 :
				temp = registers[cx];
				for( x=0;x<temp;x++ )
				{
					mem->setword( registers[di],mem->getword( registers[si] ) );
					registers[di] += 2;
					registers[si] += 2;
				}
				registers[eip]++;
			break;

			//STOSB
			case 0x13 :
				temp = registers[cx];
				for( x=0;x<temp;x++ )
				{
					mem->setbyte( registers[di],bit8reg[ah]);
					registers[di]++;
				}
				registers[eip]++;
			break;

			//STOSW
			case 0x14 :
				temp = registers[cx];
				for( x=0;x<temp;x++ )
				{
					mem->setword( registers[di],registers[ax]);
					registers[di] += 2;
				}
				registers[eip]++;
			break;

			//PUSH r 16 bit
			case 0x15 :
				mem->setword( registers[sp],
											registers[ mem->getbyte(registers[eip]+1) ] );
				registers[sp] += 2;
				registers[eip] += 2;
			break;

			//PUSH r 8 bit
			case 0x16 :
				mem->setbyte( registers[sp],
											bit8reg[ mem->getbyte(registers[eip]+1) ] );
				registers[sp]++;
				registers[eip] += 2;
			break;

			//PUSH mem 16 bit
			case 0x17 :
				mem->setword( registers[sp],
											mem->getword(mem->getword( registers[eip]+1 )) );
				registers[sp] += 2;
				registers[eip] += 3;
			break;

			//PUSH mem 8 bit
			case 0x18 :
				mem->setbyte( registers[sp],
											mem->getbyte(mem->getword( registers[eip]+1 )) );
				registers[sp]++;
				registers[eip] += 3;
			break;

			//PUSH [reg] 16 bit
			case 0x19 :
				mem->setword( registers[sp],mem->getword( registers[
											mem->getbyte( registers[eip]+1 )] ) );
				registers[sp] += 2;
				registers[eip] += 2;
			break;

			//PUSH [reg] 8 bit
			case 0x1A :
				mem->setbyte( registers[sp], mem->getbyte( registers[
											mem->getbyte( registers[eip]+1 )] ) );
				registers[sp]++;
				registers[eip] += 2;
			break;

			//PUSH imm 16 bit
			case 0x1B :
				mem->setword( registers[sp], mem->getword( registers[eip]+1 ));
				registers[sp] += 2;
				registers[eip] += 3;
			break;

			//PUSH imm 8 bit
			case 0x1C :
				mem->setbyte( registers[sp], mem->getbyte( registers[eip]+1 ));
				registers[sp]++;
				registers[eip] += 2;
			break;

			//POP reg 16 bit
			case 0x1D :
				registers[sp] -= 2;
				registers[mem->getbyte(registers[eip]+1)] =
									mem->getword(registers[sp]);
				registers[eip] += 2;
			break;

			//POP reg 8 bit
			case 0x1E :
				registers[sp]--;
				bit8reg[mem->getbyte(registers[eip]+1)] =
									mem->getbyte(registers[sp]);
				registers[eip] += 2;
			break;

			//POP mem 16 bit
			case 0x1F :
				registers[sp] -= 2;
				mem->setword( mem->getword(registers[eip]+1) ,
											mem->getword(registers[sp]) );
				registers[eip] += 3;
			break;

			//POP mem 8 bit
			case 0x20 :
				registers[sp]--;
				mem->setbyte( mem->getword(registers[eip]+1) ,
											mem->getbyte(registers[sp]) );
				registers[eip] += 3;
			break;

			//POP [reg] 16 bit
			case 0x21 :
				registers[sp] -= 2;
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
											mem->getword(registers[sp]) );
				registers[eip] += 2;
			break;

			//POP [reg] 8 bit
			case 0x22 :
				registers[sp]--;
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)],
											mem->getbyte(registers[sp]) );
				registers[eip] += 2;
			break;

			//XCHG reg,reg 16 bit
			case 0x23 :
				temp = registers[ mem->getbyte( registers[eip]+1 )];
				registers[mem->getbyte( registers[eip]+1 )] =
									registers[mem->getbyte( registers[eip]+2 )];
				registers[mem->getbyte( registers[eip]+2 )] = temp;
				registers[eip] += 3;
			break;

			//XCHG reg,reg 8 bit
			case 0x24 :
				temp = bit8reg[ mem->getbyte( registers[eip]+1 )];
				bit8reg[mem->getbyte( registers[eip]+1 )] =
								bit8reg[mem->getbyte( registers[eip]+2 )];
				bit8reg[mem->getbyte( registers[eip]+2 )] = temp;
				registers[eip] += 3;
			break;

			//XCHG reg,mem 16 bit
			case 0x25 :
				temp = registers[ mem->getbyte( registers[eip]+1 )];
				registers[mem->getbyte( registers[eip]+1 )] =
									mem->getword( mem->getword( registers[eip]+2 ) );
				mem->setword( mem->getword( registers[eip]+2 ) , temp);
				registers[eip] += 4;
			break;

			//XCHG reg,mem 8 bit
			case 0x26 :
				temp = bit8reg[ mem->getbyte( registers[eip]+1 )];
				bit8reg[  mem->getbyte( registers[eip]+1 )] =
									mem->getbyte( mem->getword( registers[eip]+2 ) );
				mem->setbyte( mem->getword( registers[eip]+2 ) , temp);
				registers[eip] += 4;
			break;

			//XCHG reg,[reg] 16 bit
			case 0x27 :
				temp = registers[ mem->getbyte( registers[eip]+1 ) ];
				registers[ mem->getbyte( registers[eip]+1 ) ] =
									 mem->getword( registers[ mem->getbyte(registers[eip]+2)]);
				mem->setword( registers[ mem->getbyte(registers[eip]+2)] , temp);
				registers[eip] += 3;
			break;

			//XCHG reg,[reg] 8 bit (broken)
			case 0x28 :
				temp = bit8reg[ mem->getbyte( registers[eip]+1 ) ];
				bit8reg[ mem->getbyte( registers[eip]+1 ) ] =
								mem->getbyte( registers[ mem->getbyte( registers[eip]+2)]);
				mem->setbyte(registers[mem->getbyte(registers[eip]+2)], temp);
				registers[eip] += 3;
			break;

			//TEST reg,imm 16 bit
			case 0x29 :
				test = registers[ mem->getbyte( registers[eip]+1 ) ];
				bit = mem->getbyte( registers[eip]+2 );
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 3;
			break;

			//TEST mem,imm 16 bit
			case 0x2A :
				test = mem->getword( mem->getword( registers[eip]+1 ));
				bit = mem->getbyte( registers[eip]+2 );
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 4;
			break;

			//TEST [reg],imm 16 bit
			case 0x2B :
				test = mem->getword( registers[mem->getbyte( registers[eip]+1 )]);
				bit = mem->getbyte( registers[eip]+2 );
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 3;
			break;

			//TEST reg,cl 16 bit
			case 0x2C :
				test = registers[mem->getbyte( registers[eip]+1 )];
				bit = bit8reg[cl];
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 2;
			break;

			//TEST mem,cl 16 bit
			case 0x2D :
				test = mem->getword( mem->getword( registers[eip]+1 ));
				bit = bit8reg[cl];
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 3;
			break;

			//TEST [reg],cl 16 bit
			case 0x2E :
				test = mem->getword( registers[mem->getbyte( registers[eip]+1 )]);
				bit = bit8reg[cl];
				if( bit <= 15 )
				{
					test <<= ( 15 - bit );
					test >>= 15;
					if(test == 1)
						registers[flags] |= setequalflag;
					else
						registers[flags] &= setunequalflag;
				}
				registers[eip] += 2;
			break;

			//CMP reg,reg 16
			case 0x2F :
				test1 = registers[ mem->getbyte( registers[eip]+1 ) ];
				test2 = registers[ mem->getbyte( registers[eip]+2 ) ];
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP reg,reg 8
			case 0x30 :
				test1 = bit8reg[ mem->getbyte( registers[eip]+1 ) ];
				test2 = bit8reg[ mem->getbyte( registers[eip]+2 ) ];
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP reg,mem 16
			case 0x31 :
				test1 = registers[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getword( mem->getword( registers[eip]+2 ) );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//CMP reg,mem 8
			case 0x32 :
				test1 = bit8reg[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getbyte( mem->getword( registers[eip]+2 ) );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//CMP reg,[reg] 16
			case 0x33 :
				test1 = registers[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getword( registers[mem->getbyte( registers[eip]+2 ) ] );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP reg,[reg] 8
			case 0x34 :
				test1 = bit8reg[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getbyte( registers[mem->getbyte( registers[eip]+2 ) ] );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP reg,imm 16
			case 0x35 :
				test1 = registers[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getword( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//CMP reg,imm 8
			case 0x36 :
				test1 = bit8reg[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getbyte( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP [reg],imm 16
			case 0x37 :
				test1 = mem->getword(registers[ mem->getbyte( registers[eip]+1 ) ] );
				test2 = mem->getword( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//CMP [reg],imm 8
			case 0x38 :
				test1 = mem->getbyte(registers[ mem->getbyte( registers[eip]+1 ) ] );
				test2 = mem->getbyte( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//CMP mem,imm 16
			case 0x39 :
				test1 = mem->getword( mem->getword( registers[eip]+1 ) );
				test2 = mem->getword( registers[eip]+3 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 5;
			break;

			//CMP mem,imm 8
			case 0x3A :
				test1 = mem->getbyte( mem->getword( registers[eip]+1 ) );
				test2 = mem->getbyte( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//CMPSB
			case 0x3B :
				status = 0;
				for(unsigned char times = bit8reg[cl];times>0;times--)
				{
					test1 = mem->getbyte(registers[di]+times);
					test2 = mem->getbyte(registers[si]+times);
					if(test1 != test2)
					{
						if(test1 > test2)status = 1;
						if(test1 < test2)status = 2;
						break;	
					}
				}
				if(status == 0)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(status == 1)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}  	
				if(status == 2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip]++;
			break;

			//JMP imm
			case 0x3C :
				registers[eip] = mem->getword( registers[eip]+1 );
			break;

			//JZ imm
			case 0x3D :
				if( (registers[flags] & equalflag) == equalflag)
					registers[eip] = mem->getword( registers[eip]+1 );
				else
					registers[eip] += 3;
			break;

			//JNZ imm
			case 0x3E :
			if( (registers[flags] & equalflag) != equalflag)
				registers[eip] = mem->getword( registers[eip]+1 );
			else
				registers[eip] += 3;
			break;

			//JAE/JNB imm
			case 0x3F :
				if( (registers[flags] & belowflag) != belowflag)
					registers[eip] = mem->getword( registers[eip]+1 );
				else
					registers[eip] += 3;
			break;

			//JBE/JNA imm
			case 0x40 :
				if( (registers[flags] & aboveflag) != aboveflag)
					registers[eip] = mem->getword( registers[eip]+1 );
				else
					registers[eip] += 3;
			break;

			//JMP reg
			case 0x41 :
				registers[eip] = registers[ mem->getbyte( registers[eip]+1 ) ];
			break;

			//LOOP imm
			case 0x42 :
				if(registers[cx] > 0)
				{
					registers[cx]--;
					registers[eip] = mem->getword( registers[eip]+1 );
				}
				else
				{
					registers[eip] += 3;
				}
			break;

			//CALL imm
			case 0x43 :
				mem->setword( registers[sp], registers[eip]+3 );
				registers[eip] = mem->getword(registers[eip]+1);
				registers[sp] += 2;
			break;

			//RET
			case 0x44 :
				registers[sp] -= 2;
				registers[eip] = mem->getword(registers[sp]);
			break;

			//IRET
			case 0x45 :
				registers[sp] -= 2;
				registers[eip] = mem->getword(registers[sp]);
				registers[flags] |= setinterruptflag;
			break;

			//CLI
			case 0x46 :
				registers[flags] &= clearinterruptflag;
				registers[eip]++;
			break;

			//STI
			case 0x47 :
				registers[flags] |= setinterruptflag;
				registers[eip]++;
			break;

			//OUT imm,imm
			case 0x48 :
				callobout( mem->getbyte( registers[eip]+1 ),
									 mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//OUT imm,reg
			case 0x49 :
				callobout( mem->getbyte( registers[eip]+1 ),
									 registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//OUT imm,[reg]
			case 0x4A :
				callobout( mem->getbyte( registers[eip]+1 ),
					mem->getword(registers[mem->getbyte( registers[eip]+2 )]) );
				registers[eip] += 3;
			break;

			//IN reg,imm
			case 0x4B :
				registers[ mem->getbyte( registers[eip]+1 ) ] =
									 callobin( mem->getbyte( registers[eip]+2 ) );
				registers[eip] += 3;
			break;

			//INC reg 16
			case 0x4C :
				registers[ mem->getbyte( registers[eip]+1 ) ]++;
				registers[eip] += 2;
			break;

			//INC reg 8
			case 0x4D :
				bit8reg[ mem->getbyte( registers[eip]+1 ) ]++;
				registers[eip] += 2;
			break;

			//INC mem 16
			case 0x4E :
				mem->setword( mem->getword(registers[eip]+1),
											mem->getword(mem->getword(registers[eip]+1))+1);
				registers[eip] += 3;
			break;

			//INC mem 8
			case 0x4F :
				mem->setbyte( mem->getword(registers[eip]+1),
											mem->getbyte(mem->getword(registers[eip]+1))+1);
				registers[eip] += 3;
			break;

			//INC [reg] 16
			case 0x50 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)],
									mem->getword(registers[mem->getbyte(registers[eip]+1)])+1);
				registers[eip] += 2;
			break;

			//INC [reg] 8
			case 0x51 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)],
									mem->getbyte(registers[mem->getbyte(registers[eip]+1)])+1);
				registers[eip] += 2;
			break;

			//DEC reg 16
			case 0x52 :
				registers[ mem->getbyte( registers[eip]+1 ) ]--;
				registers[eip] += 2;
			break;

			//DEC reg 8
			case 0x53 :
				bit8reg[ mem->getbyte( registers[eip]+1 ) ]--;
				registers[eip] += 2;
			break;

			//DEC mem 16
			case 0x54 :
				mem->setword( mem->getword(registers[eip]+1),
											mem->getword(mem->getword(registers[eip]+1))-1);
				registers[eip] += 3;
			break;

			//DEC mem 8
			case 0x55 :
				mem->setbyte( mem->getword(registers[eip]+1),
											mem->getbyte(mem->getword(registers[eip]+1))-1);
				registers[eip] += 3;
			break;

			//DEC [reg] 16
			case 0x56 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)],
								mem->getword(registers[mem->getbyte(registers[eip]+1)])-1);
				registers[eip] += 2;
			break;

			//DEC [reg] 8
			case 0x57 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)],
								mem->getbyte(registers[mem->getbyte(registers[eip]+1)])-1);
				registers[eip] += 2;
			break;

			//ADD reg,reg 16
			case 0x58 :
				registers[ mem->getbyte( registers[eip]+1 )] +=
									 registers[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//ADD reg,reg 8
			case 0x59 :
				bit8reg[ mem->getbyte( registers[eip]+1 )] +=
								 bit8reg[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//ADD reg,imm 16
			case 0x5A :
				registers[ mem->getbyte( registers[eip]+1 )] +=
									 mem->getword( registers[eip]+2 );
				registers[eip] += 4;
			break;

			//ADD reg,imm 8
			case 0x5B :
				bit8reg[ mem->getbyte( registers[eip]+1 )] +=
								 mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//ADD reg,[reg] 16
			case 0x5C :
				registers[ mem->getbyte( registers[eip]+1 )] +=
					mem->getword( registers[ mem->getbyte( registers[eip]+2 ) ] );
				registers[eip] += 3;
			break;

			//ADD reg,[reg] 8
			case 0x5D :
				bit8reg[ mem->getbyte( registers[eip]+1 )] +=
					mem->getbyte( registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//ADD reg,mem 16
			case 0x5E :
				registers[ mem->getbyte( registers[eip]+1 )] +=
									 mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//ADD reg,mem 8
			case 0x5F :
				bit8reg[ mem->getbyte(registers[eip]+1 )] +=
								 mem->getbyte( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//ADD [reg],reg 16
			case 0x60 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword( registers[mem->getbyte(registers[eip]+1)]) +
					registers[ mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//ADD [reg],reg 8
			case 0x61 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) +
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//ADD [reg],imm 16
			case 0x62 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword(registers[mem->getbyte(registers[eip]+1)]) +
					mem->getword(registers[eip]+2) );
				registers[eip] += 4;
			break;

			//ADD [reg],imm 8
			case 0x63 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) +
					mem->getbyte(registers[eip]+2) );
				registers[eip] += 3;
			break;

			//ADD mem,reg 16
			case 0x64 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) +
					registers[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//ADD mem,reg 8
			case 0x65 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) +
					bit8reg[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//ADD mem,imm 16
			case 0x66 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) +
					mem->getword( registers[eip]+3 ) );
				registers[eip] += 5;
			break;

			//ADD mem,imm 8
			case 0x67 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) +
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//SUB reg,reg 16
			case 0x68 :
				registers[ mem->getbyte( registers[eip]+1 )] -=
					registers[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//SUB reg,reg 8
			case 0x69 :
				bit8reg[ mem->getbyte( registers[eip]+1 )] -=
					bit8reg[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//SUB reg,imm 16
			case 0x6A :
				registers[ mem->getbyte( registers[eip]+1 )] -=
					mem->getword( registers[eip]+2 );
				registers[eip] += 4;
			break;

			//SUB reg,imm 8
			case 0x6B :
				bit8reg[ mem->getbyte( registers[eip]+1 )] -=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//SUB reg,[reg] 16
			case 0x6C :
				registers[ mem->getbyte( registers[eip]+1 )] -=
					mem->getword( registers[ mem->getbyte( registers[eip]+2 ) ] );
				registers[eip] += 3;
			break;

			//SUB reg,[reg] 8
			case 0x6D :
				bit8reg[ mem->getbyte( registers[eip]+1 )] -=
					mem->getbyte( registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//SUB reg,mem 16
			case 0x6E :
				registers[ mem->getbyte( registers[eip]+1 )] -=
					mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//SUB reg,mem 8
			case 0x6F :
				bit8reg[ mem->getbyte(registers[eip]+1 )] -=
					mem->getbyte( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//SUB [reg],reg 16
			case 0x70 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword( registers[mem->getbyte(registers[eip]+1)]) -
					registers[ mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//SUB [reg],reg 8
			case 0x71 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) -
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//SUB [reg],imm 16
			case 0x72 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword(registers[mem->getbyte(registers[eip]+1)]) -
					mem->getword(registers[eip]+2) );
				registers[eip] += 4;
			break;

			//SUB [reg],imm 8
			case 0x73 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) -
					mem->getbyte(registers[eip]+2) );
				registers[eip] += 3;
			break;

			//SUB mem,reg 16
			case 0x74 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) -
					registers[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//SUB mem,reg 8
			case 0x75 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) -
					bit8reg[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//SUB mem,imm 16
			case 0x76 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) -
					mem->getword( registers[eip]+3 ) );
				registers[eip] += 5;
			break;

			//SUB mem,imm 8
			case 0x77 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) -
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;


			//ROL reg,reg
			case 0x78 :
				tt = registers[ mem->getbyte( registers[eip]+2 )];
				rtemp = registers[ mem->getbyte( registers[eip]+1 )];
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				registers[ mem->getbyte( registers[eip]+1 )] = rtemp;
				registers[eip] += 3;
			break;

			//ROL reg,imm
			case 0x79 :
				tt = mem->getbyte( registers[eip]+2 );
				rtemp = registers[ mem->getbyte( registers[eip]+1 )];
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				registers[ mem->getbyte( registers[eip]+1 )] = rtemp;
				registers[eip] += 3;
			break;

			//ROL [reg],imm 16
			case 0x7A :
				tt = mem->getbyte( registers[eip]+2 );
				rtemp = mem->getword( registers[ mem->getbyte( registers[eip]+1 )] );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				mem->setword( registers[ mem->getbyte( registers[eip]+1 )], rtemp );
				registers[eip] += 3;
			break;

			//ROL [reg],reg 8
			case 0x7B :
				tt = registers[ mem->getbyte( registers[eip]+2 )];
				rtemp = mem->getword( registers[ mem->getbyte( registers[eip]+1 )] );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				mem->setword( registers[ mem->getbyte( registers[eip]+1 )], rtemp );
				registers[eip] += 3;
			break;

			//ROL mem,reg
			case 0x7C :
				tt = registers[ mem->getbyte( registers[eip]+3 )];
				rtemp = mem->getword( mem->getword( registers[eip]+1 ) );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				mem->setword( mem->getword( registers[eip]+1 ), rtemp );
				registers[eip] += 4;
			break;

			//ROL mem,imm
			case 0x7D :
				tt = mem->getbyte( registers[eip]+3 );
				rtemp = mem->getword( mem->getword( registers[eip]+1 ) );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 0x8000)==0x8000 )
						rtemp = (rtemp << 1) + 1;
					else
						rtemp <<= 1;
				}
				mem->setword( mem->getword( registers[eip]+1 ), rtemp );
				registers[eip] += 4;
			break;


			//ROR reg,reg
			case 0x7E :
				tt = registers[ mem->getbyte( registers[eip]+2 )];
				rtemp = registers[ mem->getbyte( registers[eip]+1 )];
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				registers[ mem->getbyte( registers[eip]+1 )] = rtemp;
				registers[eip] += 3;
			break;

			//ROR reg,imm
			case 0x7F :
				tt = mem->getbyte( registers[eip]+2 );
				rtemp = registers[ mem->getbyte( registers[eip]+1 )];
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				registers[ mem->getbyte( registers[eip]+1 )] = rtemp;
				registers[eip] += 3;
			break;

			//ROR [reg],imm
			case 0x80 :
				tt = mem->getbyte( registers[eip]+2 );
				rtemp = mem->getword( registers[ mem->getbyte( registers[eip]+1 )] );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				mem->setword( registers[ mem->getbyte( registers[eip]+1 )], rtemp );
				registers[eip] += 3;
			break;

			//ROR [reg],reg
			case 0x81 :
				tt = registers[ mem->getbyte( registers[eip]+2 )];
				rtemp = mem->getword( registers[ mem->getbyte( registers[eip]+1 )] );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				mem->setword( registers[ mem->getbyte( registers[eip]+1 )], rtemp );
				registers[eip] += 3;
			break;

			//ROR mem,reg
			case 0x82 :
				tt = registers[ mem->getbyte( registers[eip]+3 )];
				rtemp = mem->getword( mem->getword( registers[eip]+1 ) );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				mem->setword( mem->getword( registers[eip]+1 ), rtemp );
				registers[eip] += 4;
			break;

			//ROR mem,imm
			case 0x83 :
				tt = mem->getbyte( registers[eip]+3 );
				rtemp = mem->getword( mem->getword( registers[eip]+1 ) );
				for( x=0;x<tt;x++ )
				{
					if( (rtemp & 1)==1 )
						rtemp = (rtemp >> 1) + 0x8000;
					else
						rtemp >>= 1;
				}
				mem->setword( mem->getword( registers[eip]+1 ), rtemp );
				registers[eip] += 4;
			break;


			//IMUL
			case 0x84 :
				iresult = iregisters[ax] * iregisters[dx];
				iregisters[ax] = iresult&0xffff;
				iregisters[dx] = iresult>>16;
				registers[eip]++;
			break;

			//IDIV
			case 0x85 :
				if( iregisters[dx] != 0 )
				{
					iintpart = int(iregisters[ax] /	iregisters[dx]);
					irestpart = iregisters[ax]%iregisters[dx];
					iregisters[ax] = iintpart;
					iregisters[dx] = irestpart;
				}
				registers[eip]++;
			break;

			//JA mem
			case 0x86 :
				if( (registers[flags] & aboveflag) == aboveflag)
					registers[eip] = mem->getword( registers[eip]+1 );
				else
					registers[eip] += 3;
			break;

			//JB mem
			case 0x87 :
				if( (registers[flags] & belowflag) == belowflag)
					registers[eip] = mem->getword( registers[eip]+1 );
				else
					registers[eip] += 3;
			break;

			//atanfunc
			// AX = atan2(BX,DX)
			case 0x88 :
				temp = int( atan2( iregisters[bx],iregisters[dx] )*512/pi );
				temp -= 256;
				if( temp < 0 )
					temp += 1024;
				temp = -temp+1024;
				if( temp >= 1024 )
					temp -= 1024;
				registers[ax] = temp;
				registers[eip]++;
			break;

			//SQR
			//AX = SQR AX
			//DX = decimalpart
			case 0x89 :
				temp = registers[ax];
				registers[ax] = int( sqrt( temp ) );
				registers[dx] = int( (sqrt( temp )-registers[ax]) * 65536 );
				registers[eip]++;
			break;

			//ICMP reg,reg 16
			case 0x8A :
				test1 = iregisters[ mem->getbyte( registers[eip]+1 ) ];
				test2 = iregisters[ mem->getbyte( registers[eip]+2 ) ];
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//ICMP reg,mem 16
			case 0x8B :
				test1 = iregisters[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getiword( mem->getword( registers[eip]+2 ) );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//ICMP reg,[reg] 16
			case 0x8C :
				test1 = iregisters[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getiword( registers[mem->getbyte( registers[eip]+2 ) ] );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 3;
			break;

			//ICMP reg,imm 16
			case 0x8D :
				test1 = iregisters[ mem->getbyte( registers[eip]+1 ) ];
				test2 = mem->getiword( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//ICMP [reg],imm 16
			case 0x8E :
				test1 = mem->getiword(registers[ mem->getbyte( registers[eip]+1 ) ] );
				test2 = mem->getiword( registers[eip]+2 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 4;
			break;

			//ICMP mem,imm 16
			case 0x8F :
				test1 = mem->getiword( mem->getword( registers[eip]+1 ) );
				test2 = mem->getiword( registers[eip]+3 );
				if(test1 == test2)
				{
					registers[flags] |= setequalflag;
					registers[flags] &= clearequalflags;
				}
				if(test1 > test2)
				{
					registers[flags] |= setaboveflag;
					registers[flags] &= clearaboveflags;
				}
				if(test1 < test2)
				{
					registers[flags] |= setbelowflag;
					registers[flags] &= clearbelowflags;
				}
				registers[eip] += 5;
			break;

			//MSG reg
			case 0x90 :
				temp = registers[mem->getbyte( registers[eip]+1 )];
				for( x=0;x<20;x++ )
					message[x] = mem->getbyte( temp+x );
				message[19] = 0;
				sendmsg( message );
				registers[eip] += 2;
			break;

			//MSG mem
			case 0x91 :
				temp = mem->getword( registers[eip]+1 );
				for( x=0;x<20;x++ )
					message[x] = mem->getbyte( temp+x );
				message[19] = 0;
				sendmsg( message );
				registers[eip] += 3;
			break;

			//ERR val
			case 0x92 :
				temp = mem->getbyte( registers[eip]+1 );
				strcpy( message,"ERROR #: " );
				message[9] = temp+'0';
				message[10] = 0;
				sendmsg( message );
				registers[eip] += 2;
			break;

			//READFILE
			// AX - start
			// CX - length
			// DI - adress

			// AX = number if bytes read or -1 if error
			case 0x93 :
				iregisters[ax] = readfile( registers[ax], registers[cx],
																	 registers[di] );
				registers[eip]++;
			break;

			//WRITEFILE
			// AX - start
			// CX - length
			// SI - adress

			// AX = number of bytes written or -1 if error
			case 0x94 :
				iregisters[ax] = writefile( registers[ax], registers[cx],
																		registers[si] );
				registers[eip]++;
			break;

			//LZ reg
			case 0x95 :
				if( (registers[flags] & equalflag) == equalflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//LNZ reg
			case 0x96 :
				if( registers[flags] & equalflag != equalflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//LA reg
			case 0x97 :
				if( registers[flags] & aboveflag == aboveflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//AND reg,reg 16
			case 0x98 :
				registers[ mem->getbyte( registers[eip]+1 )] &=
									registers[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//AND reg,reg 8
			case 0x99 :
				bit8reg[ mem->getbyte( registers[eip]+1 )] &=
								bit8reg[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//AND reg,imm 16
			case 0x9A :
				registers[ mem->getbyte( registers[eip]+1 )] &=
									 mem->getword( registers[eip]+2 );
				registers[eip] += 4;
			break;

			//AND reg,imm 8
			case 0x9B :
				bit8reg[ mem->getbyte( registers[eip]+1 )] &=
								 mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//AND reg,[reg] 16
			case 0x9C :
				registers[ mem->getbyte( registers[eip]+1 )] &=
							 mem->getword( registers[ mem->getbyte( registers[eip]+2 ) ] );
				registers[eip] += 3;
			break;

			//AND reg,[reg] 8
			case 0x9D :
				bit8reg[ mem->getbyte( registers[eip]+1 )] &=
								 mem->getbyte( registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//AND reg,mem 16
			case 0x9E :
				registers[ mem->getbyte( registers[eip]+1 )] &=
									 mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//AND reg,mem 8
			case 0x9F :
				bit8reg[ mem->getbyte(registers[eip]+1 )] &=
								 mem->getbyte( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//AND [reg],reg 16
			case 0xA0 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
											mem->getword( registers[mem->getbyte(registers[eip]+1)]) &
											registers[ mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//AND [reg],reg 8
			case 0xA1 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) &
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//AND [reg],imm 16
			case 0xA2 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword(registers[mem->getbyte(registers[eip]+1)]) &
					mem->getword(registers[eip]+2) );
				registers[eip] += 4;
			break;

			//AND [reg],imm 8
			case 0xA3 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) &
					mem->getbyte(registers[eip]+2) );
				registers[eip] += 3;
			break;

			//AND mem,reg 16
			case 0xA4 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) &
					registers[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//AND mem,reg 8
			case 0xA5 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) &
					bit8reg[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//AND mem,imm 16
			case 0xA6 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) &
					mem->getword( registers[eip]+3 ) );
				registers[eip] += 5;
			break;

			//AND mem,imm 8
			case 0xA7 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) &
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//OR reg,reg 16
			case 0xA8 :
				registers[ mem->getbyte( registers[eip]+1 )] |=
					registers[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//OR reg,reg 8
			case 0xA9 :
				bit8reg[ mem->getbyte( registers[eip]+1 )] |=
					bit8reg[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//OR reg,imm 16
			case 0xAA :
				registers[ mem->getbyte( registers[eip]+1 )] |=
					mem->getword( registers[eip]+2 );
				registers[eip] += 4;
			break;

			//OR reg,imm 8
			case 0xAB :
				bit8reg[ mem->getbyte( registers[eip]+1 )] |=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//OR reg,[reg] 16
			case 0xAC :
				registers[ mem->getbyte( registers[eip]+1 )] |=
					mem->getword( registers[ mem->getbyte( registers[eip]+2 ) ] );
				registers[eip] += 3;
			break;

			//OR reg,[reg] 8
			case 0xAD :
				bit8reg[ mem->getbyte( registers[eip]+1 )] |=
					mem->getbyte( registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//OR reg,mem 16
			case 0xAE :
				registers[ mem->getbyte( registers[eip]+1 )] |=
					mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//OR reg,mem 8
			case 0xAF :
				bit8reg[ mem->getbyte(registers[eip]+1 )] |=
					mem->getbyte( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//OR [reg],reg 16
			case 0xB0 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword( registers[mem->getbyte(registers[eip]+1)]) |
					registers[ mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//OR [reg],reg 8
			case 0xB1 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) |
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//OR [reg],imm 16
			case 0xB2 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword(registers[mem->getbyte(registers[eip]+1)]) |
					mem->getword(registers[eip]+2) );
				registers[eip] += 4;
			break;

			//OR [reg],imm 8
			case 0xB3 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) |
					mem->getbyte(registers[eip]+2) );
				registers[eip] += 3;
			break;

			//OR mem,reg 16
			case 0xB4 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) |
					registers[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//OR mem,reg 8
			case 0xB5 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) |
					bit8reg[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//OR mem,imm 16
			case 0xB6 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) |
					mem->getword( registers[eip]+3 ) );
				registers[eip] += 5;
			break;

			//OR mem,imm 8
			case 0xB7 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) |
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;
			//XOR reg,reg 16
			case 0xB8 :
				registers[ mem->getbyte( registers[eip]+1 )] ^=
					registers[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//XOR reg,reg 8
			case 0xB9 :
				bit8reg[ mem->getbyte( registers[eip]+1 )] ^=
					bit8reg[ mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//XOR reg,imm 16
			case 0xBA :
				registers[ mem->getbyte( registers[eip]+1 )] ^=
					mem->getword( registers[eip]+2 );
				registers[eip] += 4;
			break;

			//XOR reg,imm 8
			case 0xBB :
				bit8reg[ mem->getbyte( registers[eip]+1 )] ^=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//XOR reg,[reg] 16
			case 0xBC :
				registers[ mem->getbyte( registers[eip]+1 )] ^=
					mem->getword( registers[ mem->getbyte( registers[eip]+2 ) ] );
				registers[eip] += 3;
			break;

			//XOR reg,[reg] 8
			case 0xBD :
				bit8reg[ mem->getbyte( registers[eip]+1 )] ^=
					mem->getbyte( registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//XOR reg,mem 16
			case 0xBE :
				registers[ mem->getbyte( registers[eip]+1 )] ^=
					mem->getword( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//XOR reg,mem 8
			case 0xBF :
				bit8reg[ mem->getbyte(registers[eip]+1 )] ^=
					mem->getbyte( mem->getword( registers[eip]+2 ) );
				registers[eip] += 4;
			break;

			//XOR [reg],reg 16
			case 0xC0 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword( registers[mem->getbyte(registers[eip]+1)]) ^
					registers[ mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//XOR [reg],reg 8
			case 0xC1 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) ^
					bit8reg[mem->getbyte(registers[eip]+2)] );
				registers[eip] += 3;
			break;

			//XOR [reg],imm 16
			case 0xC2 :
				mem->setword( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getword(registers[mem->getbyte(registers[eip]+1)]) ^
					mem->getword(registers[eip]+2) );
				registers[eip] += 4;
			break;

			//XOR [reg],imm 8
			case 0xC3 :
				mem->setbyte( registers[mem->getbyte(registers[eip]+1)] ,
					mem->getbyte(registers[mem->getbyte(registers[eip]+1)]) ^
					mem->getbyte(registers[eip]+2) );
				registers[eip] += 3;
			break;

			//XOR mem,reg 16
			case 0xC4 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) ^
					registers[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//XOR mem,reg 8
			case 0xC5 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) ^
					bit8reg[ mem->getbyte( registers[eip]+3 ) ] );
				registers[eip] += 4;
			break;

			//XOR mem,imm 16
			case 0xC6 :
				mem->setword( mem->getword( registers[eip]+1 ) ,
					mem->getword( mem->getword( registers[eip]+1 ) ) ^
					mem->getword( registers[eip]+3 ) );
				registers[eip] += 5;
			break;

			//XOR mem,imm 8
			case 0xC7 :
				mem->setbyte( mem->getword( registers[eip]+1 ) ,
					mem->getbyte( mem->getword( registers[eip]+1 ) ) ^
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//SHL reg,imm 16
			case 0xC8 :
				registers[mem->getbyte( registers[eip]+1 )] <<=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//SHL reg,reg 16
			case 0xC9 :
				registers[mem->getbyte( registers[eip]+1 )] <<=
					registers[mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//SHL [reg],imm 16
			case 0xCA :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getword(registers[mem->getbyte( registers[eip]+1 )]) <<
					mem->getbyte( registers[eip]+2 ) );
				registers[eip] += 3;
			break;

			//SHL [reg],reg 16
			case 0xCB :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getword(registers[mem->getbyte( registers[eip]+1 )]) <<
					registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//SHL mem,imm 16
			case 0xCC :
				mem->setword( mem->getword( registers[eip]+1 ),
					mem->getword(mem->getword( registers[eip]+1 )) <<
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//SHL mem,reg 16
			case 0xCD :
				mem->setword( mem->getword( registers[eip]+1 ),
					mem->getword(mem->getword( registers[eip]+1 )) <<
					registers[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//SHR reg,imm 16
			case 0xCE :
				registers[mem->getbyte( registers[eip]+1 )] >>=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//SHR reg,reg 16
			case 0xCF :
				registers[mem->getbyte( registers[eip]+1 )] >>=
					registers[mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//SHR [reg],imm 16
			case 0xD0 :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getword(registers[mem->getbyte( registers[eip]+1 )]) >>
					mem->getbyte( registers[eip]+2 ) );
				registers[eip] += 3;
			break;

			//SHR [reg],reg 16
			case 0xD1 :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getword(registers[mem->getbyte( registers[eip]+1 )]) >>
					registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//SHR mem,imm 16
			case 0xD2 :
				mem->setword( mem->getword( registers[eip]+1 ),
					mem->getword(mem->getword( registers[eip]+1 )) >>
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//SHR mem,reg 16
			case 0xD3 :
				mem->setword( mem->getword( registers[eip]+1 ),
					mem->getword(mem->getword( registers[eip]+1 )) >>
					registers[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;


			//ISHL reg,imm 16
			case 0xD4 :
				iregisters[mem->getbyte( registers[eip]+1 )] <<=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//ISHL reg,reg 16
			case 0xD5 :
				iregisters[mem->getbyte( registers[eip]+1 )] <<=
					registers[mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//ISHL [reg],imm 16
			case 0xD6 :
				mem->setiword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getiword(registers[mem->getbyte( registers[eip]+1 )]) <<
					mem->getbyte( registers[eip]+2 ) );
				registers[eip] += 3;
			break;

			//ISHL [reg],reg 16
			case 0xD7 :
				mem->setiword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getiword(registers[mem->getbyte( registers[eip]+1 )]) <<
					registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//ISHL mem,imm 16
			case 0xD8 :
				mem->setiword( mem->getword( registers[eip]+1 ),
					mem->getiword(mem->getword( registers[eip]+1 )) <<
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//ISHL mem,reg 16
			case 0xD9 :
				mem->setiword( mem->getword( registers[eip]+1 ),
					mem->getiword(mem->getword( registers[eip]+1 )) <<
					registers[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//ISHR reg,imm 16
			case 0xDA :
				iregisters[mem->getbyte( registers[eip]+1 )] >>=
					mem->getbyte( registers[eip]+2 );
				registers[eip] += 3;
			break;

			//ISHR reg,reg 16
			case 0xDB :
				iregisters[mem->getbyte( registers[eip]+1 )] >>=
					registers[mem->getbyte( registers[eip]+2 )];
				registers[eip] += 3;
			break;

			//ISHR [reg],imm 16
			case 0xDC :
				mem->setiword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getiword(registers[mem->getbyte( registers[eip]+1 )]) >>
					mem->getbyte( registers[eip]+2 ) );
				registers[eip] += 3;
			break;

			//ISHR [reg],reg 16
			case 0xDD :
				mem->setiword( registers[mem->getbyte( registers[eip]+1 )],
					mem->getiword(registers[mem->getbyte( registers[eip]+1 )]) >>
					registers[mem->getbyte( registers[eip]+2 )] );
				registers[eip] += 3;
			break;

			//ISHR mem,imm 16
			case 0xDE :
				mem->setiword( mem->getword( registers[eip]+1 ),
					mem->getiword(mem->getword( registers[eip]+1 )) >>
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//ISHR mem,reg 16
			case 0xDF :
				mem->setiword( mem->getword( registers[eip]+1 ),
					mem->getiword(mem->getword( registers[eip]+1 )) >>
					registers[mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//INT imm
			case 0xE0 :
				mem->setword( registers[sp], registers[eip]+2 );
				tt = mem->returnsize( );
				argum = mem->getbyte( registers[eip]+1 );
				registers[eip] = mem->getword( tt-(argum*2+2) );
				registers[sp] += 2;
				registers[flags] &= 0xFBFF;
			break;

			//MUL
			case 0xE1 :
				result = registers[ax] * registers[dx];
				registers[ax] = result&0xffff;
				registers[dx] = result>>16;
				registers[eip]++;
			break;

			//DIV
			case 0xE2 :
				if( registers[dx] != 0 )
				{
					intpart = int(registers[ax] /	registers[dx]);
					restpart = registers[ax]%registers[dx];
					registers[ax] = intpart;
					registers[dx] = restpart;
				}
				registers[eip]++;
			break;

			//RET IMM
			case 0xE3 :
				temp = mem->getbyte( registers[eip]+1 );
				registers[sp] -= 2;
				registers[eip] = mem->getword( registers[sp] );
				registers[sp] -= temp;
			break;

			//LODSB
			case 0xE4 :
				bit8reg[al] = mem->getbyte( registers[si] );
				registers[si]++;
				registers[eip]++;
			break;

			//LODSW
			case 0xE5 :
				registers[ax] = mem->getword( registers[si] );
				registers[si] += 2;
				registers[eip]++;
			break;

			//SINFUNC
			// AX = AX + BX * SIN DX
			case 0xE6 :
				registers[ax] = (unsigned short)( registers[ax] +
					(registers[bx]*(sin( registers[dx]/512.0*3.1416 ))) );
				registers[eip]++;
			break;

			//COSFUNC
			// AX = AX + BX * COS DX
			case 0xE7 :
				registers[ax] = (unsigned short)( registers[ax] +
					(registers[bx]*(cos( registers[dx]/512.0*3.1416 ))) );
				registers[eip]++;
			break;

			//SIN
			//AX = SIN AX
			case 0xE8 :
				iregisters[ax] = short( sin( registers[ax]/512.0*3.1416 )*32768 );
				registers[eip]++;
			break;

			//COS
			//AX = COS AX
			case 0xE9 :
				iregisters[ax] = short( cos( registers[ax]/512.0*3.1416 )*32768 );
				registers[eip]++;
			break;

			//MOV reg,[reg+val]
			case 0xEA :
				registers[ mem->getbyte( registers[eip]+1 )] =
					mem->getword( registers[mem->getbyte( registers[eip]+2 )]+
					mem->getbyte( registers[eip]+3 ) );
				registers[eip] += 4;
			break;

			//MOV [reg+val],reg
			case 0xEB :
				mem->setword( registers[mem->getbyte( registers[eip]+1 )]+
					mem->getbyte( registers[eip]+2 ),
					registers[ mem->getbyte( registers[eip]+3 )] );
				registers[eip] += 4;
			break;

			//RND
			case 0xEC :
				registers[ax] = random( );
				registers[eip]++;
			break;

			//HWAIT
			case 0xED :
				registers[eip]++;
				if( cyclesleft>0 )cyclesleft = 0;
			break;

			//LB reg
			case 0xEE :
				if( registers[flags] & belowflag == belowflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//LAE/LNB reg
			case 0xEF :
				if( registers[flags] & belowflag != belowflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//LBE/LNA reg
			case 0xF0 :
				if( registers[flags] & aboveflag != aboveflag )
					registers[mem->getbyte( registers[eip]+1 )] = 1;
				else
					registers[mem->getbyte( registers[eip]+1 )] = 0;
				registers[eip] += 2;
			break;

			//CJ reg label
			case 0xF1 :
				if( registers[mem->getbyte( registers[eip]+1 )] >= 1 )
					registers[eip] = mem->getword( registers[eip]+2 );
				else
					registers[eip] += 4;
			break;

			//CJN reg label
			case 0xF2 :
				if( registers[mem->getbyte( registers[eip]+1 )] == 0 )
					registers[eip] = mem->getword( registers[eip]+2 );
				else
					registers[eip] += 4;
			break;

			default :
				registers[eip]++;
				cyclesleft--;
		}
		if( SingleStepMode )cyclesleft = 0;			
	}
}
