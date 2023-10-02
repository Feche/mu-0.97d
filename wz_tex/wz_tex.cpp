#include "wz_tex.h"

BYTE  OpenType;
BYTE  UpdateMaxIndex;
short MaxIndex;

void FindTextureByName__(char* FileName, void* Texture)
{
    if (UpdateMaxIndex == 0)
    {
        if (OpenType == ITEM_TEXTURES)
        {
            if (TextureIndex >= 688)
            {
                UpdateMaxIndex = 1;
            }
        }
        else if (OpenType == PLAYER_TEXTURES)
        {
            if (TextureIndex > 490)
            {
                UpdateMaxIndex = 1;
            }
        }
    }

    if (UpdateMaxIndex == 1)
    {
        TextureIndex = MaxIndex;
        UpdateMaxIndex = 2;
    }

    ((void(*)(char*, void*))FIND_TEXTURE_BY_NAME_Wz)(FileName, Texture);
}

void OpenPlayerTextures__()
{
    // Set FindTextureByName hook
    SetCall(FIND_TEXTURE_BY_NAME, FindTextureByName__);

    TextureIndex = PLAYER_TEXTURES_START;
    OpenType = PLAYER_TEXTURES;

    // Call original OpenPlayerTextures function
    ((void(*)())OPEN_PLAYER_TEXTURES_Wz)();

    if (UpdateMaxIndex)
    {
        UpdateMaxIndex = 0;
        MaxIndex = TextureIndex;
    }

    OpenType = NULL;

    // Restore FindTextureByName hook
    SetCall(FIND_TEXTURE_BY_NAME, (void*)FIND_TEXTURE_BY_NAME_Wz);
}

void OpenItemTextures__()
{
    // Set hook
    SetCall(FIND_TEXTURE_BY_NAME, FindTextureByName__);

    TextureIndex = ITEM_TEXTURES_START;
    OpenType = ITEM_TEXTURES;

    // Call original OpenItemTextures function
    ((void(*)())OPEN_ITEM_TEXTURES_Wz)();

    if (UpdateMaxIndex)
    {
        UpdateMaxIndex = 0;
        MaxIndex = TextureIndex;
    }

    OpenType = NULL;

    // Restore hook
    SetCall(FIND_TEXTURE_BY_NAME, (void*)FIND_TEXTURE_BY_NAME_Wz);
}

void WzTexInit()
{
    SetCall(OPEN_PLAYER_TEXTURES, OpenPlayerTextures__);
    SetCall(OPEN_ITEM_TEXTURES,   OpenItemTextures__);

    MaxIndex = START_TEXTURES_INDEX;
}

void SetCall(DWORD Address, void* Func)
{
    *(BYTE*)(Address) = 0xE8; // 0xE8 - call
    *(DWORD*)(Address + 1) = (DWORD)Func - (Address + 5);
}