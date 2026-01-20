#pragma once
#include "../../readwrite/memory.h"
#include "../../../GameOffset/GameOffset.h"
#include "../../../Global.h"
#include "../../../minhook/include/MinHook.h"
#ifdef _M_IX86
#pragma comment(lib, "minhook/lib/libMinHook.x86.lib") // 32位游戏必选这个！
#else
#pragma comment(lib, "minhook/lib/libMinHook.x64.lib")
#endif
class baseManager :
	public memory
{
protected:
	uintptr_t m_GameBase;
	GameOffset m_Offsets;
	uintptr_t m_ModuleAddress;
public:
	baseManager();
};

