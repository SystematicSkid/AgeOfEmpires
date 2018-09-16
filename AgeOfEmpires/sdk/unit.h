#pragma once

class StatValue
{
public:
	char pad_0000[8]; //0x0000
	float m_fValue; //0x0008
}; //Size: 0x0044


class SecondaryStatValue
{
public:
	float m_fValue; //0x0004
}; //Size: 0x0044


class Stat
{
public:
	char pad_0000[24]; //0x0000
	class StatValue* pFirstValue; //0x0018
	char pad_001C[8]; //0x001C
	class SecondaryStatValue* pSecondValue; //0x0024
}; //Size: 0x0084


class StatContainer
{
public:
	Stat* GetStat(int idx)
	{
		return *(Stat**)(this + 0x4 * idx);
	}
};

class UnitStats
{
public:
	char pad[0x1C];
	StatContainer* pBasicStats;
	int m_iNumStats;
}; //Size: 0x004C


class UnitInfo
{
public:
	char pad_0000[16]; //0x0000
	char* m_szName; //0x0010
	char pad_0014[48]; //0x0014
	class UnitStats* pStats; //0x0044
	char pad_0048[56]; //0x0048
	float m_fSpeed; //0x0080
	char pad_0084[20]; //0x0084
	float m_fMaxHealth; //0x0098
	char pad_009C[40]; //0x009C
	float m_fRangedResist; //0x00C4
}; //Size: 0x00E8

class Unit
{
public:
	char pad_0000[20]; //0x0000
	Vector m_vOrigin; //0x0014
	char pad_0020[36]; //0x0020
	class PlayerInfo* pOwner; //0x0044
	char pad_0048[20]; //0x0048
	class UnitInfo* pInfo; //0x005C
	char pad_0060[4]; //0x0060
	float m_fHealth; //0x0064
}; //Size: 0x0440
