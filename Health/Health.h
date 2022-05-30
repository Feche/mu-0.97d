/* 
	By Feche - https://github.com/Feche/
	- Health bug fix for MuOnline 0.97d -
*/

#ifndef HEALTH_H
#define HEALTH_H

#include "PartyClass.h"

void GCReFillSendEX(int aIndex, WORD Health, BYTE Ipos, BYTE flag);
void gObjRestPotionFill(OBJECTSTRUCT* lpObj);
void gObjSkillUseProc(OBJECTSTRUCT* lpObj);
void gObjMonsterDieLifePlus(OBJECTSTRUCT* lpObj, OBJECTSTRUCT* lpTargetObj);

void Health();

#endif