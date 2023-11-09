#include <windows.h>

#define MAX_ID_SIZE		10
#define MAX_SKILLS		64
#define MAX_EQUIPMENT	12

#define GCClientMsgStringSend ((void(*)(const char * szSender, const char * szText, BYTE Color))(0x0047E3C0))

// Size 18 bytes
struct MONSTER_ATTRIBUTE
{
	WORD Life;
	WORD MoveSpeed;
	WORD AttackSpeed;
	WORD AttackDamageMin;
	WORD AttackDamageMax;
	WORD Defense;
	WORD MagicDefense;
	WORD AttackRating;
	WORD SuccessfulBlocking;
};

// Size is 28 bytes
struct MONSTER
{
	short             Type;
	BYTE              Level;
	int               Experince;
	MONSTER_ATTRIBUTE Attribute;
};

// Size 68 bytes - OK
struct ITEM
{
	short Type;
	int   Level;
	BYTE  Part;
	BYTE  Class;
	bool  TwoHand;
	WORD  DamageMin;
	WORD  DamageMax;
	BYTE  SuccessfulBlocking;
	WORD  Defense;
	WORD  MagicDefense;
	BYTE  WeaponSpeed;
	BYTE  MagicPower;
	WORD  WalkSpeed;
	BYTE  Durability;
	BYTE  Option1;
	WORD  RequireStrength;
	WORD  RequireDexterity;
	WORD  RequireEnergy;
	WORD  RequireLevel;
	BYTE  SpecialNum;
	BYTE  Special[MAX_ITEM_SPECIAL];
	BYTE  SpecialValue[MAX_ITEM_SPECIAL];
	DWORD Number;
	BYTE  Unk1;
	BYTE  Unk2;
	BYTE  pX;
	BYTE  pY;
	BYTE  CanEquip;
};

struct CHARACTER_ATTRIBUTE
{
	char  Name[MAX_ID_SIZE + 1]; // 0

	BYTE  Class;				// 11	
	BYTE  Skin;					// 12
	WORD  Level;				// 14
	DWORD Experience;			// 16
	WORD  Strength;				// 20
	WORD  Dexterity;			// 22
	WORD  Vitality;				// 24
	WORD  Energy;				// 26
	WORD  Life;					// 28
	WORD  Mana;					// 30
	WORD  MaxLife;				// 32
	WORD  MaxMana;				// 34
	WORD  BP;					// 36
	WORD  MaxBP;				// 38
	BYTE  Ability;				// 40
	WORD  AbilityTime[2];		// 42
	WORD  AddPoint;				// 46
	WORD  MaxAddPoint;			// 48
	DWORD NextExp;				// 52
	WORD  AttackSpeed;			// 56
	WORD  AttackRating;			// 58
	WORD  AttackDamageMinRight; // 60
	WORD  AttackDamageMaxRight; // 62
	WORD  AttackDamageMinLeft;	// 64
	WORD  AttackDamageMaxLeft;	// 66
	WORD  MagicSpeed;			// 68
	WORD  MagicDamageMin;		// 70
	WORD  MagicDamageMax;		// 72
	WORD  CriticalDamage;		// 74
	WORD  SuccessfulBlocking;	// 76
	WORD  Defense;				// 78
	WORD  MagicDefense;		    // 80
	WORD  WalkSpeed;			// 82
	WORD  LevelUpPoint;			// 84
	BYTE  SkillNumber;			// 86
	BYTE  Skill[MAX_SKILLS];    // Skill that player has
	BYTE  SkillLevel[MAX_SKILLS];
	BYTE  HotKey[5][MAX_SKILLS]; // Corresponding key for the skill
};

struct CHARACTER_MACHINE
{
	CHARACTER_ATTRIBUTE Character;
	ITEM			    Equipment[MAX_EQUIPMENT]; // 536  - size is 816 bytes (68 * 12)
	int					Gold;					  // 1352 - OK
	int                 StorageGold;			  // 1356 - OK
	MONSTER				Enemy;
	WORD				AttackDamageRight;
	WORD				AttackDamageLeft;
	int					CriticalDamage;
	WORD				FinalAttackDamageRight;
	WORD				FinalAttackDamageLeft;
	WORD				FinalHitPoint;
	WORD				FinalAttackRating;
	WORD				FinalDefenseRating;
	bool				FinalSuccessAttack;
	bool				FinalSuccessDefense;
	BYTE				PacketSerial;
};