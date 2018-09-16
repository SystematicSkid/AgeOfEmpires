#pragma once

class PlayerInfo;

class BuyableItem
{
public:
		char pad_0000[8]; //0x0000
		int32_t m_iPurchaseFlag; //0x0008
		char pad_000C[4]; //0x000C
		char* m_szName; //0x0010
		int32_t m_iImageFlag; //0x0014
		char pad_0018[84]; //0x0018
		float m_fBuildSpeed; //0x006C
		char pad_0070[104]; //0x0070
		int32_t m_iPopulationCost; //0x00D8
		char pad_00DC[44]; //0x00DC
		int32_t m_iMax; //0x0108
		char pad_010C[92]; //0x010C
		float m_fKillXP; //0x0168
		float m_fBuildXP; //0x016C
		char pad_0170[80]; //0x0170
		int32_t m_iRequiredAge; //0x01C0

}; //Size: 0x0044

class ObjectTable
{
public:
	BuyableItem* GetObject(int idx)
	{
		return *(BuyableItem**)(this + idx * 0x4);
	}

	void SetObject(int idx, PlayerInfo* local)
	{
		using fnGetObjectAtIndex = int(__thiscall*)(PlayerInfo* thisptr, int idx);
		fnGetObjectAtIndex GetObjectAtIndex;
		GetObjectAtIndex = (fnGetObjectAtIndex)0x4317B8;
		*(int*)(this + idx * 0x4) = GetObjectAtIndex(local, idx);
	}
};

class PlayerInfo
{
public:
	int32_t m_iIndex; //0x0000
	wchar_t* m_szName; //0x0004
	char pad_008[132];
	wchar_t* m_szHomeCity;
	char pad_0090[48]; //0x0090
	class ObjectTable* pObjects; //0x00C0
	char pad_00C4[332]; //0x00C4
	int* pResources;
/*
	char pad_0008[56]; //0x0008
	int32_t m_iAge; //0x0040
	char pad_0044[72]; //0x0044
	wchar_t* m_szHomeCity; //0x008C
	char pad_0090[48]; //0x0090
	class ObjectTable* pObjects; //0x00C0
	char pad_00C4[332]; //0x00C4
	int* pResources; //0x0210*/


	float GetResource(int type)
	{
		if (this->pResources)
		{
			int val = this->pResources[type] ^ ((DWORD*)XOR_KEY)[type];
		}
	}

	// We apply the same logic as above with the xor key to set the resource :)

	void SetResource(int type, float f)
	{
		if (this->pResources)
		{
			this->pResources[type] = *(int*)&f ^ ((DWORD*)XOR_KEY)[type];
		}
	}

}; //Size: 0x0440
