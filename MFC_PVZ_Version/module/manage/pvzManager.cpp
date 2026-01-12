#include "pvzManager.h"

void pvzManager::SetSunlight(int value)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x2A9EC0);
		uintptr_t GameSunLightOffset = Read<uintptr_t>(ChineseVersionGameBaseAddress + 0x768);
		Write<int>((GameSunLightOffset + 0x5560), value);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x331C50);
		uintptr_t GameSunLightOffset = Read<uintptr_t>(SteamVersionGameBaseAddress + 0x868);
		Write<int>((GameSunLightOffset + 0x5578), value);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t GameSunLightOffset = Read<uintptr_t>((SeasonVersionGameBaseAddress + 0x868));
		Write<int>((GameSunLightOffset + 0x5578), value);
	}
}

void pvzManager::AddZombies(int row, int zType)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x2A9EC0));
		uintptr_t targetObj = Read<uintptr_t>((ChineseVersionGameBaseAddress + 0x768));
		__asm {
			pushad
			push row
			push zType
			mov eax, targetObj
			mov ebx, 0x0040DDC0
			call ebx
			popad
		}
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SteamVersionGameBaseAddress + 0x868));
		__asm {
			pushad
			push row
			push zType
			mov eax, targetObj
			mov ebx, 0x0040DDC0
			call ebx
			popad
		}
	}

}

void pvzManager::EnableNoCooldown()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x88E76), 0x01);
	}
	else if (VersionResult == 1) {}
}

void pvzManager::DisableNoCooldown()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x88E76), 0x00);
	}
	else if (VersionResult == 1) {}
}

void pvzManager::EnableAutoCollect()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x3158E), 0x01);
	}
}

void pvzManager::DisableAutoCollect()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x3158E), 0x00);
	}
}

void pvzManager::EnablePeaDamage()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6EB2E), 0x00);
	}
}

void pvzManager::DisablePeaDamage()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6EB2E), 0x01);
	}
}

void pvzManager::EnableNoPause()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x14EB87), 0xEB);
		WriteByte((GameModuleAddress + 0x14EB88), 0x09);
	}
}

void pvzManager::DisableNoPause()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x14EB87), 0x74);
		WriteByte((GameModuleAddress + 0x14EB88), 0x0D);
	}
}

