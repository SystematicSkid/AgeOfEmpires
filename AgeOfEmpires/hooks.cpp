#include "ageofempires.h"
#include "PolyHook.hpp"

PLH::X86Detour* PopulationLimitHook; // No anti-cheat :D

using fnGetPopulationLimit = int(__thiscall*)(void* thisptr); // Don't need this since we're never returning the original function, but it's nice to see still :)

int __fastcall hkGetPopulationLimit(void* thisptr, void*)
{
	return 1000;
}

bool Hooks::Init()
{
	PopulationLimitHook = new PLH::X86Detour();
	PopulationLimitHook->SetupHook((BYTE*)0x4363D0, (BYTE*)hkGetPopulationLimit);
	if (!PopulationLimitHook->Hook())
		return false;

	return true;
}

Hooks hooks;