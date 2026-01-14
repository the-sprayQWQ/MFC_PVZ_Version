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
			mov ebx, 0x00411290
			call ebx
			popad
		}
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SeasonVersionGameBaseAddress + 0x868));
		__asm {
			pushad
			push row
			push zType
			mov eax, targetObj
			mov ebx, 0x00411290
			call ebx
			popad
		}
	}

}

void pvzManager::GetProps(int pType)
{
	if (VersionResult == 0) {
		typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
		GetProps getProps = (GetProps)0x0040CB10;
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x2A9EC0));
		uintptr_t targetObj = Read<uintptr_t>((ChineseVersionGameBaseAddress + 0x768));
		getProps((void*)targetObj, 0, 0x3C, pType, 0);
	}
	else if (VersionResult == 1) {
		typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
		GetProps getProps = (GetProps)0x0040FF90;
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SteamVersionGameBaseAddress + 0x868));
		getProps((void*)targetObj, 0, 0x3C, pType, 0);
	}
	else {
		typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
		GetProps getProps = (GetProps)0x0040FF90;
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SeasonVersionGameBaseAddress + 0x868));
		getProps((void*)targetObj, 0, 0x3C, pType, 0);
	}


}

void pvzManager::SetPlant(int column, int row, int pType)
{
	if (VersionResult == 0) {
		__asm {
			pushad
			push 0xFFFFFFFF
			push pType
			mov eax,row
			push column
			mov edi, dword ptr ds : [0x006A9EC0]
			mov edi, dword ptr ds : [edi + 0x768]
			push edi
			mov ebx, 0x0040D120
			call ebx
			popad
		}
	}
	else if (VersionResult == 1) {
		__asm {
			pushad
			push 0xFFFFFFFF
			push pType
			mov eax, row
			push column
			mov edi, dword ptr ds : [0x00731C50]
			mov edi, dword ptr ds : [edi + 0x868]
			push edi
			mov ebx, 0x004105A0
			call ebx
			popad
		}
	}
	else {
		__asm {
			pushad
			push 0xFFFFFFFF
			push pType
			mov eax, row
			push column
			mov edi, dword ptr ds : [0x00731C50]
			mov edi, dword ptr ds : [edi + 0x868]
			push edi
			mov ebx, 0x004105A0
			call ebx
			popad
		}
	}
}

int pvzManager::s_Red = 255;
int pvzManager::s_Green = 255;
int pvzManager::s_Blue = 64;
uintptr_t pvzManager::s_PlantColorRetAddress = 0;


void _declspec(naked) PlantColorHOOK() {
	__asm{
		push[pvzManager::s_Blue]
		mov edx,[pvzManager::s_Green]
		mov ecx,[pvzManager::s_Red]
		jmp [pvzManager::s_PlantColorRetAddress]
	}
}

void pvzManager::ChangePlantColor(int Red, int Green, int Blue)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x636E4), 0x74);
		s_Red = Red;
		s_Green = Green;
		s_Blue = Blue;
		uintptr_t TargetAddress = GameModuleAddress + 0x636E6;
		s_PlantColorRetAddress = TargetAddress + 7;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress,&PlantColorHOOK,NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else if(VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x69AF6), Red);
		WriteByte((GameModuleAddress + 0x69AF1), Green);
		WriteByte((GameModuleAddress+0x69AEC),Blue);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x69AF6), Red);
		WriteByte((GameModuleAddress + 0x69AF1), Green);
		WriteByte((GameModuleAddress + 0x69AEC), Blue);
	}
}

void pvzManager::restorePlantColor()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x636E4), 0x75);
		uintptr_t TargetAddress = GameModuleAddress + 0x636E6;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x69AF6), 0xFF);
		WriteByte((GameModuleAddress + 0x69AF1), 0xFF);
		WriteByte((GameModuleAddress + 0x69AEC), 0xFF);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x69AF6), 0xFF);
		WriteByte((GameModuleAddress + 0x69AF1), 0xFF);
		WriteByte((GameModuleAddress + 0x69AEC), 0xFF);
	}
}

void pvzManager::EnableNoCooldown()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x88E76), 0x01);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x97516), 0x01);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x97516), 0x01);
	}
}

void pvzManager::DisableNoCooldown()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x88E76), 0x00);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x97516), 0x00);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x97516), 0x00);
	}
}

void pvzManager::EnableAutoCollect()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x3158E), 0x01);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x352F1), 0x01);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x352F1), 0x01);
	}
}

void pvzManager::DisableAutoCollect()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x3158E), 0x00);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x352F1), 0x00);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x352F1), 0x00);
	}
}

void pvzManager::EnablePeaDamage()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6EB2E), 0x00);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x76B7B), 0x00);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x76B7B), 0x00);
	}
}

void pvzManager::DisablePeaDamage()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6EB2E), 0x01);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x76B7B), 0x01);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x76B7B), 0x01);
	}
}

void pvzManager::EnableNoPause()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x14EB87), 0xEB);
		WriteByte((GameModuleAddress + 0x14EB88), 0x09);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x540D9), 0x01);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x540D9), 0x01);
	}
}

void pvzManager::DisableNoPause()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x14EB87), 0x74);
		WriteByte((GameModuleAddress + 0x14EB88), 0x0D);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x540D9), 0x00);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x540D9), 0x00);
	}
}

void pvzManager::EnablePlantSpeed()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x64A97),0x84);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x6AEC5), 0x84);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6AEC5), 0x84);
	}
}

void pvzManager::DisablePlantSpeed()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x64A97), 0x85);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x6AEC5), 0x85);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6AEC5), 0x85);
	}
}

void pvzManager::EnableFlowerEat()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6324C), 0x31);
		WriteByte((GameModuleAddress + 0x6324E), 0x90);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x69648), 0x83);
		WriteByte((GameModuleAddress + 0x69649), 0x67);
		WriteByte((GameModuleAddress + 0x6964A), 0x54);
		WriteByte((GameModuleAddress + 0x6964B), 0x00);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x69648), 0x83);
		WriteByte((GameModuleAddress + 0x69649), 0x67);
		WriteByte((GameModuleAddress + 0x6964A), 0x54);
		WriteByte((GameModuleAddress + 0x6964B), 0x00);
	}
}

void pvzManager::DisableFlowerEat()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x6324C), 0x83);
		WriteByte((GameModuleAddress + 0x6324E), 0xFF);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x69648), 0x48);
		WriteByte((GameModuleAddress + 0x69649), 0x89);
		WriteByte((GameModuleAddress + 0x6964A), 0x47);
		WriteByte((GameModuleAddress + 0x6964B), 0x54);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x69648), 0x48);
		WriteByte((GameModuleAddress + 0x69649), 0x89);
		WriteByte((GameModuleAddress + 0x6964A), 0x47);
		WriteByte((GameModuleAddress + 0x6964B), 0x54);
	}
}

