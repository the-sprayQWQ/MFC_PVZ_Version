#include "pvzManager.h"

void pvzManager::SetSunlight(int value)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x2A9EC0));
		uintptr_t GameSunLightOffset = Read<uintptr_t>((ChineseVersionGameBaseAddress + 0x768));
		Write<int>((GameSunLightOffset + 0x5560), value);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t GameSunLightOffset = Read<uintptr_t>((SteamVersionGameBaseAddress + 0x868));
		Write<int>((GameSunLightOffset + 0x5578), value);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t GameSunLightOffset = Read<uintptr_t>((SeasonVersionGameBaseAddress + 0x868));
		Write<int>((GameSunLightOffset + 0x5578), value);
	}
}
