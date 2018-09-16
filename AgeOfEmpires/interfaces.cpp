#include "ageofempires.h"

bool Interfaces::Init()
{
	// We can just use static offsets this game hasn't updated in a decade lol

	game_manager = **(GameManager***)(Memory::SigScan("A1 ? ? ? ? 8B 88 ? ? ? ? 56 8B B1 ? ? ? ? C7 44 24 ? ? ? ? ?") + 1); // A1 ? ? ? ? 8B 88 ? ? ? ? 56 8B B1 ? ? ? ? C7 44 24 ? ? ? ? ?  + 1
	if (!game_manager)
		return false;

	return true;
}

Interfaces ints;