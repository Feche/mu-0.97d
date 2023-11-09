#include "CharacterMachine.h"

CHARACTER_MACHINE* CharacterMachine;

void UseCharacterMachine()
{
	CharacterMachine = (CHARACTER_MACHINE*)*(DWORD*)(0x081F1364);

	((void(__thiscall*)(void*, void*))0x00422500)((void*)0x055C4C20, CharacterMachine);
}

void SaveCharacterMachine()
{
	((void(__thiscall*)(void*, void*))0x0043C1E0)((void*)0x055C4C20, CharacterMachine);
}

void CallMe()
{
	UseCharacterMachine();

	char szTmp[64];

	sprintf_s(szTmp, "Name: %s, Level: %d, Life: %d", CharacterMachine->Character.Name, CharacterMachine->Character.Level, CharacterMachine->Character.Life);

	GCClientMsgStringSend("", szTmp, 0x00);

	SaveCharacterMachine();
}