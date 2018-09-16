#include "ageofempires.h"

using fnGetObjectAtIndex = BuyableItem*(__thiscall*)(PlayerInfo* thisptr, int idx);
fnGetObjectAtIndex GetObjectAtIndex;

void Init()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	if (!ints.Init())
		MessageBoxA(NULL, "Interfaces: Failed to Init", NULL, NULL);

	if (!hooks.Init())
		MessageBoxA(NULL, "Hooks: Failed to Init", NULL, NULL);

	printf("Debug: 0x%p\n", ints.game_manager);

	GetObjectAtIndex = (fnGetObjectAtIndex)Memory::SigScan("8B 54 24 04 85 D2 0F 8C ? ? ? ? 3B 91 ? ? ? ?"); // 8B 54 24 04 85 D2 0F 8C ? ? ? ? 3B 91 ? ? ? ? 

	while (true) /* Instead of using our own thread, we can hook to a function at index 2 on the GameData vtable which constantly loops*/
	{
		if(IsValidPtr(ints.game_manager))
		{
			GameData* game_data = ints.game_manager->pData;
			if (IsValidPtr(game_data))
			{
				PlayerInfo* localent = game_data->pPlayerList->GetLocalPlayer();
				if (IsValidPtr(localent))
				{
					printf("Local: 0x%p\n", localent);
					for (int i = 0; i < 3; i++)
						localent->SetResource(i, 1000000.f); // Gimme the gold

					for (int k = 0; k < game_data->m_iCurrentNumberOfUnits; k++)
					{
						Unit* ent = game_data->pUnitList->GetUnit(k);
						if (!IsValidPtr(ent))
							continue;
						if (!IsValidPtr(ent->pOwner))
							continue;

						if (ent->pOwner == localent)
						{
							if (IsValidPtr(ent->pInfo))
							{
								if (IsValidPtr(ent->pInfo->pStats))
								{
									if (ent->pInfo->m_fSpeed > 0.1f)
										ent->pInfo->m_fSpeed = 25.f;
									ent->pInfo->m_fRangedResist = 1.f;
									for (int j = 0; j < ent->pInfo->pStats->m_iNumStats; j++)
									{
										Stat* stat = ent->pInfo->pStats->pBasicStats->GetStat(j);
										if (!IsValidPtr(stat))
											continue;
										if (IsValidPtr(stat->pFirstValue))
											stat->pFirstValue->m_fValue = 500.f;
										if (IsValidPtr(stat->pSecondValue))
											stat->pSecondValue->m_fValue = 500.f;
									}
								}
							}
						}

					}
					if (IsValidPtr(localent->pObjects))
					{
						for (int o = 0; o < 626; o++)
						{
							BuyableItem* item = localent->pObjects->GetObjectA(o);
							if (!IsValidPtr(item))
								continue;
							item->m_fBuildSpeed = 0.5f;
							item->m_fBuildXP = 1000.f;
							item->m_fKillXP = 0.f;
							item->m_iMax = 1000;
							item->m_iRequiredAge = 0;
						}
					}
				}
			}
		}
	}
}


DWORD __stdcall DllMain(HMODULE dll, DWORD callreason, void* reserved)
{
	if (callreason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL); // We can make a thread because we're hacking an old ass game lmao
		return 1;
	}
	return 0;
}