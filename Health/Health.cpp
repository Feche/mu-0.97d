/* 
	By Feche - https://github.com/Feche/
	- Health bug fix for MuOnline 0.97d -
*/

#include "StdAfx.h"

int GCDamageSendEX(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage)
{
	int result = GCDamageSend(aIndex, TargetIndex, AttackDamage, MSBFlag, MSBDamage);

	OBJECTSTRUCT* lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT* lpTargetObj = (OBJECTSTRUCT*)OBJECT_POINTER(TargetIndex);

	BYTE Buffer[9] = { NULL };
	Buffer[0] = 0xC1;
	Buffer[1] = sizeof(Buffer);
	Buffer[2] = 0xEA;
	Buffer[3] = 0x01;
	Buffer[4] = 0xFF;

	unsigned int Life = (int)lpObj->Life;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 5] = (Life >> (8 * (i + 1))) & 0xFF;
	}

	DataSend(aIndex, Buffer, sizeof(Buffer));

	unsigned int TargetLife = (int)lpTargetObj->Life;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 5] = (TargetLife >> (8 * (i + 1))) & 0xFF;
	}

	DataSend(TargetIndex, Buffer, sizeof(Buffer));
	return result;
}


void GCReFillSendEX(int aIndex, WORD Health, BYTE Ipos, BYTE flag)
{
	GCReFillSend(aIndex, Health, Ipos, flag);

	OBJECTSTRUCT* lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	BYTE Buffer[9] = { NULL };
	Buffer[0] = 0xC1;
	Buffer[1] = sizeof(Buffer);
	Buffer[2] = 0xEA;
	Buffer[3] = 0x01;
	Buffer[4] = Ipos;

	if(Ipos == 0xFF)
	{
		unsigned int Life = lpObj->Life;
		for(int i = 0; i < 4; i++)
		{
			Buffer[i + 5] = (Life >> (8 * (i + 1))) & 0xFF;
		}
	}
	else if(Ipos == 0xFE)
	{
		unsigned int TotalLife = AddLife[lpObj->m_Index] + lpObj->MaxLife;
		for(int i = 0; i < 4; i++)
		{
			Buffer[i + 5] = (TotalLife >> (8 * (i + 1))) & 0xFF;
		}
	}

	DataSend(aIndex, Buffer, sizeof(Buffer));
}

void SendDataSpawnEX(int aIndex, PBYTE Packet, DWORD Size)
{
	DataSend(aIndex, Packet, Size);

	OBJECTSTRUCT* lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	BYTE Buffer[13] = { NULL };
	Buffer[0] = 0xC1;
	Buffer[1] = sizeof(Buffer);
	Buffer[2] = 0xEA;
	Buffer[3] = 0x01;
	Buffer[4] = 0xFC;

	unsigned int Life = (int)lpObj->Life;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 5] = (Life >> (8 * (i + 1))) & 0xFF;
	}

	unsigned int MaxLife = (int)AddLife[lpObj->m_Index] + (int)lpObj->MaxLife;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 9] = (MaxLife >> (8 * (i + 1))) & 0xFF;
	}

	DataSend(aIndex, Buffer, sizeof(Buffer));

	ReSendLvlUpPoints(aIndex);
}

void SendDataRespawn(int aIndex, PBYTE Packet, DWORD Size)
{
	DataSend(aIndex, Packet, Size);

	OBJECTSTRUCT* lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	BYTE Buffer[13] = { NULL };
	Buffer[0] = 0xC1;
	Buffer[1] = sizeof(Buffer);
	Buffer[2] = 0xEA;
	Buffer[3] = 0x01;
	Buffer[4] = 0xFC;

	lpObj->Life = AddLife[lpObj->m_Index] + (int)lpObj->MaxLife;

	unsigned int Life = (int)lpObj->Life;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 5] = (Life >> (8 * (i + 1))) & 0xFF;
	}

	unsigned int MaxLife = (int)AddLife[lpObj->m_Index] + (int)lpObj->MaxLife;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 9] = (MaxLife >> (8 * (i + 1))) & 0xFF;
	}

	DataSend(aIndex, Buffer, sizeof(Buffer));

	FixInner(aIndex);
}

void gObjLevelUp(int aIndex)
{
	gObjCalcMaxLifePower(aIndex);

	OBJECTSTRUCT* lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	lpObj->Life = lpObj->MaxLife + AddLife[aIndex];

	BYTE Buffer[13] = { NULL };
	Buffer[0] = 0xC1;
	Buffer[1] = sizeof(Buffer);
	Buffer[2] = 0xEA;
	Buffer[3] = 0x01;
	Buffer[4] = 0xFC;

	unsigned int Life = (int)lpObj->Life;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 5] = (Life >> (8 * (i + 1))) & 0xFF;
	}

	unsigned int MaxLife = (int)AddLife[lpObj->m_Index] + (int)lpObj->MaxLife;
	for(int i = 0; i < 4; i++)
	{
		Buffer[i + 9] = (MaxLife >> (8 * (i + 1))) & 0xFF;
	}

	DataSend(aIndex, Buffer, sizeof(Buffer));

	ReSendLvlUpPoints(aIndex);
}

void GCDiePlayerSendEX(OBJECTSTRUCT* lpObj, int TargetIndex)
{
	GCDiePlayerSend(lpObj, TargetIndex);

	if(lpObj->Type == OBJECT_USER)
	{
		BYTE Buffer[9] = { NULL };
		Buffer[0] = 0xC1;
		Buffer[1] = sizeof(Buffer);
		Buffer[2] = 0xEA;
		Buffer[3] = 0x01;
		Buffer[4] = 0xFF;

		DataSend(TargetIndex, Buffer, Buffer[1]);
	}
}

void Health()
{
	HookThis((DWORD)&GCDamageSendEX, 0x004025A4);
	HookThis((DWORD)&GCReFillSendEX, 0x00401389);
	HookThis((DWORD)&SendDataSpawnEX, 0x00410EF0); // When user spawns
	HookThis((DWORD)&SendDataRespawn, 0x0047327B); // When user spawns after death
	HookThis((DWORD)&gObjRestPotionFill, 0x00402A9A);
	HookThis((DWORD)&gObjSkillUseProc, 0x00401A2D);
	HookThis((DWORD)&gObjLevelUp, 0x00462C93); // When user levels up
	HookThis((DWORD)&gObjMonsterDieLifePlus, 0x00401528);
	HookThis((DWORD)&GCDiePlayerSendEX, 0x00402685);
	// Party
	HookThis((DWORD)&CGPartyList, 0x00401D43);
	HookThis((DWORD)&PartyMemberLifeSend, 0x004011A4);
}