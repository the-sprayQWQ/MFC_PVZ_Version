#include "baseManager.h"

baseManager::baseManager()
{
	m_GameBase = 0;
	if (VersionResult == 0) {
		m_Offsets = GameOffset::GetChineseVersion();
		m_ModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		m_GameBase = memory::Read<uintptr_t>(m_ModuleAddress + m_Offsets.BasePtrOffset);

	}
	else if (VersionResult == 1) {
		m_Offsets = GameOffset::GetSteamVersion();
		m_ModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		m_GameBase = memory::Read<uintptr_t>(m_ModuleAddress + m_Offsets.BasePtrOffset);
	}
	else {
		m_Offsets = GameOffset::GetSteamVersion();
		m_ModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		m_GameBase = memory::Read<uintptr_t>(m_ModuleAddress + m_Offsets.BasePtrOffset);
	}
}
