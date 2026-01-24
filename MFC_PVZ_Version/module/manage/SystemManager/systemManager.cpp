#include "systemManager.h"

void systemManager::SetSunlight(int value)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	Write<int>((boardAddress + m_Offsets.SunOffset), value);
}

void systemManager::EnableAutoCollect()
{
	WriteByte((m_ModuleAddress + m_Offsets.autoCollectOffset), 0x01);
}

void systemManager::DisableAutoCollect()
{
	WriteByte((m_ModuleAddress + m_Offsets.autoCollectOffset), 0x00);
}

void systemManager::EnableNoCooldown()
{
	WriteByte((m_ModuleAddress + m_Offsets.coolDownOffset), 0x01);
}

void systemManager::DisableNoCooldown()
{
	WriteByte((m_ModuleAddress + m_Offsets.coolDownOffset), 0x01);
}

void systemManager::GetProps(int pType)
{
	typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
	GetProps getProps = (GetProps)(m_ModuleAddress + m_Offsets.getPropsOffset);
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	if (!pType) {
		pType = 4;
	}
	getProps((void*)boardAddress, 0, 0x3C, pType, 0);
}

void systemManager::ChangeLevel(int Level)
{
	uintptr_t levelAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.levelFirstOffset);
	Write<int>((levelAddress + m_Offsets.levelFinalOffset), Level);
}

void systemManager::EnableNoPause()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noPauseOffset), m_Offsets.noPauseData);
}

void systemManager::DisableNoPause()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noPauseOffset), m_Offsets.restorePauseData);
}

void systemManager::ReduceHealth()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x002A9EC0);
		uintptr_t GameMainAddress = Read<uintptr_t>(ChineseVersionGameBaseAddress + 0x768);
		uintptr_t ZombieBase = Read<uintptr_t>(GameMainAddress + 0x90);
		uintptr_t MaxZombiesNum = Read<uintptr_t>(GameMainAddress + 0x98);
		for (int i = 0; i < MaxZombiesNum; i++) {
			uintptr_t ZombiesPtr = ZombieBase + (i * 0x15C);
			int hp = Read<int>(ZombiesPtr + 0xC8);
			if (hp > 0) {
				__asm {
					pushad
					push 0
					push 0x2710
					push ZombiesPtr
					mov eax, 0x005312D0
					call eax
					popad
				}
			}
		}
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x331C50);
		uintptr_t GameMainAddress = Read<uintptr_t>(SteamVersionGameBaseAddress + 0x868);
		uintptr_t ZombieBase = Read<uintptr_t>(GameMainAddress + 0xA8);
		uintptr_t MaxZombiesNum = Read<uintptr_t>(GameMainAddress + 0xAC);
		for (int i = 0; i < MaxZombiesNum; i++) {
			uintptr_t ZombiesPtr = ZombieBase + (i * 0x168);
			int hp = Read<int>(ZombiesPtr + 0xC8);
			if (hp > 0) {
				__asm {
					pushad
					push 0x2710
					mov ecx, ZombiesPtr
					mov eax, 0x005462A0
					call eax
					popad
				}
			}
		}
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x331C50);
		uintptr_t GameMainAddress = Read<uintptr_t>(SeasonVersionGameBaseAddress + 0x868);
		uintptr_t ZombieBase = Read<uintptr_t>(GameMainAddress + 0xA8);
		uintptr_t MaxZombiesNum = Read<uintptr_t>(GameMainAddress + 0xAC);
		for (int i = 0; i < MaxZombiesNum; i++) {
			uintptr_t ZombiesPtr = ZombieBase + (i * 0x168);
			int hp = Read<int>(ZombiesPtr + 0xC8);
			if (hp > 0) {
				__asm {
					pushad
					push 0x2710
					mov ecx, ZombiesPtr
					mov eax, 0x005462A0
					call eax
					popad
				}
			}
		}
	}
}

void systemManager::EnableAllStatusKill()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allStatusKillOffset), { 0x90,0x90 });
}

void systemManager::DisableAllStatusKill()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allStatusKillOffset), { 0x75,0x0C });
}

void systemManager::EnableAllNoMove()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allNoMoveOffset), { 0x90,0x90 });
}

void systemManager::DisableAllNoMove()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allNoMoveOffset), { 0x75,0x1D });
}

void systemManager::EnableColumnPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.columnPlantOffset), { 0x90,0x90,0x90,0x90,0x90,0x90 });
}

void systemManager::DisableColumnPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.columnPlantOffset), m_Offsets.restorePlantData);
}

void systemManager::EnableInterCropping()
{
	WriteBytes((m_ModuleAddress + m_Offsets.interCroppingOffset), m_Offsets.interCroppingData);
}

void systemManager::DisableInterCropping()
{
	WriteBytes((m_ModuleAddress + m_Offsets.interCroppingOffset), m_Offsets.restoreCroppingData);
}

