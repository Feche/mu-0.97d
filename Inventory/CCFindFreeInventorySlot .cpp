#include "CCFindFreeInventorySlot.h"

// Find free slot on player inventory matching
// The width and heigh of the item
// Uses ITEM structure
BYTE CCFindFreeInventorySlot(BYTE width, BYTE height)
{
	ITEM* Inventory = g_pMyInventory;

	for (int l = 0; l < MAX_INVENTORY; l++)
	{
		if (Inventory[l].Type == -1)
		{
			int  StartLine = l / 8;
			bool SlotFree  = true;

			for (int h = 0; h < height; h++)
			{
				for (int w = 0; w < width; w++)
				{
					int pos = (h * 8) + l + w;
					int line = pos / 8;

					if (line > StartLine + h)
					{
						SlotFree = false;

						break;
					}

					if (Inventory[pos].Type != -1)
					{
						SlotFree = false;

						break;
					}
				}

				if (!SlotFree)
				{
					break;
				}

				if (h == height - 1)
				{
					return l;
				}
			}
		}
	}

	return 254;
}
