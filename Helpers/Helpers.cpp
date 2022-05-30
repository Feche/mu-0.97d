/* 
	By Feche - https://github.com/Feche/
	- Add two (2) new helpers (Fairy, Demon) for MuOnline 0.97d -
*/

#include "StdAfx.h"

char Str[255];

Naked(AngelFairyRestLife)
{
	_asm
	{
		CMP EAX, 0x1A0 // Angel
		JE True
		CMP EAX, 0x1A4 // Fairy
		JE True
		MOV EAX, 1
		RETN
True:
		MOV EAX, 0
		RETN
	}
}

Naked(SatanDemonRestLife)
{
	_asm
	{
		CMP EDX, 0x1A1 // Satan
		JE True
		CMP EDX, 0x1A5 // Demon
		JE True
		MOV EAX, 1
		RETN
True:
		MOV EAX, 0
		RETN
	}
}

BOOL IsHelper(short int a1)
{
	if(a1 == 416 || a1 == 417 || a1 == 420 || a1 == 421)
		return TRUE;
	return FALSE;
}

void Helpers()
{
	*(BYTE*)(0x00419409 + 2) = 0xA7;
	*(BYTE*)(0x0041CF9C + 3) = 0xA7;

	// Decrease helper life on hit
	*(BYTE*)(0x00465B71 + 0) = 0xE8;
	*(DWORD*)(0x00465B71 + 1) = (DWORD)&AngelFairyRestLife - (0x00465B71 + 5);

	*(BYTE*)(0x00465BB8 + 0) = 0xE8;
	*(DWORD*)(0x00465BB8 + 1) = (DWORD)&SatanDemonRestLife - (0x00465BB8 + 5);

	// Call1
	*(BYTE*)(0x00465D7B + 0) = 0x8B;
	*(BYTE*)(0x00465D7B + 1) = 0x45;
	*(BYTE*)(0x00465D7B + 2) = 0xF0;
	*(BYTE*)(0x00465D7B + 3) = 0x50;
	*(BYTE*)(0x00465D7B + 4) = 0xE8;
	*(DWORD*)(0x00465D7B + 5) = (DWORD)&IsHelper - (0x00465D7B + 9);
	*(BYTE*)(0x00465D7B + 9) = 0x85;
	*(BYTE*)(0x00465D7B + 10) = 0xC0;
	*(BYTE*)(0x00465D7B + 11) = 0x58;
	*(BYTE*)(0x00465D7B + 12) = 0x0F;
	*(BYTE*)(0x00465D7B + 13) = 0x84;
	*(BYTE*)(0x00465D7B + 14) = 0x12;
	*(BYTE*)(0x00465D7B + 15) = 0x01;
	*(BYTE*)(0x00465D7B + 16) = 0x00;
	*(BYTE*)(0x00465D7B + 17) = 0x00;
	SetNop(0x00465D7B + 18, 4);
}