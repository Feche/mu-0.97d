#pragma once

#include <windows.h>

#define WIN32_LEAN_AND_MEAN

#define TEXTURE_INDEX		    0x088A3428
#define OPEN_PLAYER_TEXTURES    0x0050BCD6
#define OPEN_ITEM_TEXTURES	    0x0050BCE0
#define FIND_TEXTURE_BY_NAME    0x00500C9C
#define BITMAPS				    0x088A6FC0

#define FIND_TEXTURE_BY_NAME_Wz 0x00500BC0
#define OPEN_PLAYER_TEXTURES_Wz 0x00502560
#define OPEN_ITEM_TEXTURES_Wz   0x00503BF0

#define BITMAPS_SIZE		    56
#define PLAYER_TEXTURES_START   301
#define ITEM_TEXTURES_START	    500
#define START_TEXTURES_INDEX    2000

#define PLAYER_TEXTURES		    1
#define ITEM_TEXTURES		    2

#define TextureIndex			*(int*)(0x088A3428)

void WzTexInit();
void SetCall(DWORD Address, void* Func);