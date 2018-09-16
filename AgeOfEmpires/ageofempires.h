#pragma once

// win
#include <Windows.h>
#include <winternl.h>
#include <Xinput.h>
#include <comdef.h>
#include <minwindef.h>
#include <winbase.h>
#include <intrin.h>
#include <psapi.h>

// stl
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <sstream>

#include "memory.h"
//memory
#define PTR_MAX_VALUE ((PVOID)0xFFF00000)
_forceinline bool IsValidPtr(PVOID p) { return (p >= (PVOID)0x10000) && (p < PTR_MAX_VALUE); }

#define XOR_KEY 0xC0DACC // need to cast to ptr

#include "sdk\vector.h"
#include "sdk\player.h"
#include "sdk\unit.h"
#include "sdk\game.h"

#include "interfaces.h"
#include "hooks.h"