#pragma once

class PlayerTable
{
public:
	PlayerInfo* GetPlayer(int idx)
	{
		return *(PlayerInfo**)(this + 0x4 * idx);
	}

	PlayerInfo* GetLocalPlayer()
	{
		for (int i = 0; i < 8; i++)
		{
			PlayerInfo* player = GetPlayer(i);
			if(player->m_iIndex != 1)
				continue;
			return player;
		}
		return nullptr;
	}
};

class UnitTable
{
public:
	Unit* GetUnit(int idx)
	{
		return *(Unit**)(this + 0x4 * idx);
	}
};

class GameData
{
public:
	char pad_0000[12]; //0x0000
	UnitTable* pUnitList; //0x000C
	int32_t m_iCurrentNumberOfUnits; //0x0010
	char pad_0014[68]; //0x0014
	PlayerTable* pPlayerList; //0x0058
	int32_t m_iNumberOfPlayers; //0x005C
	int32_t m_iMaxNumberOfPlayers; //0x0060
	char pad_0064[4]; //0x0064
	wchar_t* m_szMap; //0x0068
	char pad_006C[688]; //0x006C
	int32_t m_iMaxPopulation; //0x031C
	char pad_0320[548]; //0x0320
}; //Size: 0x0544

class World
{
public:
	char pad[0x50];
	ObjectTable* pAllObjects;
};

class GameManager
{
public:
	char pad_0000[316]; //0x0000
	class GameData* pData; //0x013C
	class World* pWorld;
}; //Size: 0x0444
