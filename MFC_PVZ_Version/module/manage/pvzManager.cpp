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

void pvzManager::ChangePlant(int plaidPos, int plantType)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x2A9EC0);
		uintptr_t GameMainOffset = Read<uintptr_t>(ChineseVersionGameBaseAddress + 0x768);
		uintptr_t plaidFirstOffset = Read<uintptr_t>(GameMainOffset + 0x144);
		Write<int>((plaidFirstOffset + 0x5C + (plaidPos - 1) * 0x50), plantType);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x331C50);
		uintptr_t GameMainOffset = Read<uintptr_t>(SteamVersionGameBaseAddress + 0x868);
		uintptr_t plaidFirstOffset = Read<uintptr_t>(GameMainOffset + 0x15C);
		Write<int>((plaidFirstOffset + 0x5C + (plaidPos - 1) * 0x50), plantType);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>(GameModuleAddress + 0x331C50);
		uintptr_t GameMainOffset = Read<uintptr_t>(SeasonVersionGameBaseAddress + 0x868);
		uintptr_t plaidFirstOffset = Read<uintptr_t>(GameMainOffset + 0x15C);
		Write<int>((plaidFirstOffset + 0x5C + (plaidPos - 1) * 0x70), plantType);
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
		if (!pType) {
			pType = 4;
		}
		getProps((void*)targetObj, 0, 0x3C, pType, 0);
	}
	else if (VersionResult == 1) {
		typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
		GetProps getProps = (GetProps)0x0040FF90;
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t SteamVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SteamVersionGameBaseAddress + 0x868));
		if (!pType) {
			pType = 4;
		}
		getProps((void*)targetObj, 0, 0x3C, pType, 0);
	}
	else {
		typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
		GetProps getProps = (GetProps)0x0040FF90;
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t SeasonVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x331C50));
		uintptr_t targetObj = Read<uintptr_t>((SeasonVersionGameBaseAddress + 0x868));
		if (!pType) {
			pType = 4;
		}
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
			mov eax, row
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

void pvzManager::SetZombies(int column, int row, int zType)
{
	if (VersionResult == 0) {
		__asm {
			pushad
			push column
			push zType
			mov eax, row
			mov ebx, dword ptr ds : [0x006A9EC0]
			mov ebx, dword ptr ds : [ebx + 0x768]
			mov ebx, dword ptr ds : [ebx + 0x160]
			mov ecx, ebx
			mov esi,0x0042A0F0
			call esi
			popad
		}
	}
}

void pvzManager::ChangeLevel(int Level)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x2A9EC0));
		uintptr_t LevelOffset = Read<uintptr_t>((ChineseVersionGameBaseAddress + 0x82C));
		Write<int>((LevelOffset + 0x24),Level);

	}
}

int pvzManager::s_Red = 255;
int pvzManager::s_Green = 255;
int pvzManager::s_Blue = 64;
uintptr_t pvzManager::s_PlantColorRetAddress = 0;


void _declspec(naked) PlantColorHOOK() {
	__asm {
		push[pvzManager::s_Blue]
		mov edx, [pvzManager::s_Green]
		mov ecx, [pvzManager::s_Red]
		jmp[pvzManager::s_PlantColorRetAddress]
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
		MH_CreateHook((LPVOID)TargetAddress, &PlantColorHOOK, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x69AF6), Red);
		WriteByte((GameModuleAddress + 0x69AF1), Green);
		WriteByte((GameModuleAddress + 0x69AEC), Blue);
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
		WriteByte((GameModuleAddress + 0x64A97), 0x84);
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
		WriteBytes((GameModuleAddress + 0x69648), { 0x83,0x67 });
		WriteBytes((GameModuleAddress + 0x6964A), { 0x54,0x00 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69648), { 0x83,0x67 });
		WriteBytes((GameModuleAddress + 0x6964A), { 0x54,0x00 });
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
		WriteBytes((GameModuleAddress + 0x69648), { 0x48,0x89 });
		WriteBytes((GameModuleAddress + 0x6964A), { 0x47,0x54 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69648), { 0x48,0x89 });
		WriteBytes((GameModuleAddress + 0x6964A), { 0x47,0x54 });
	}
}

int pvzManager::s_row = 0;
int pvzManager::s_zType = 0;
uintptr_t pvzManager::s_ChangeZombieRetAddress = 0;

void _declspec(naked) ChineseVersionChangeZombie() {
	__asm {
		pushad
		push[pvzManager::s_row]
		push[pvzManager::s_zType]
		mov eax, dword ptr ds : [0x006A9EC0]
		mov eax, dword ptr ds : [eax + 0x768]
		mov eax, eax
		mov ebx, 0x0040DDC0
		call ebx
		popad
		jmp[pvzManager::s_ChangeZombieRetAddress]
	}
}
void _declspec(naked) SteamVersionChangeZombie() {
	__asm {
		pushad
		push[pvzManager::s_row]
		push[pvzManager::s_zType]
		mov eax, dword ptr ds : [0x00731C50]
		mov eax, dword ptr ds : [eax + 0x868]
		mov eax, eax
		mov ebx, 0x00411290
		call ebx
		popad
		jmp[pvzManager::s_ChangeZombieRetAddress]
	}
}
void _declspec(naked) SeasonVersionChangeZombie() {
	__asm {
		pushad
		push[pvzManager::s_row]
		push[pvzManager::s_zType]
		mov eax, dword ptr ds : [0x00731C50]
		mov eax, dword ptr ds : [eax + 0x868]
		mov eax, eax
		mov ebx, 0x00411290
		call ebx
		popad
		jmp[pvzManager::s_ChangeZombieRetAddress]
	}
}

void pvzManager::EnableChangeZombie(int row, int zType)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		s_row = row;
		s_zType = zType;
		uintptr_t TargetAddress = GameModuleAddress + 0x13055;
		s_ChangeZombieRetAddress = TargetAddress + 9;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &ChineseVersionChangeZombie, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		s_row = row;
		s_zType = zType;
		uintptr_t TargetAddress = GameModuleAddress + 0x16568;
		s_ChangeZombieRetAddress = TargetAddress + 9;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SteamVersionChangeZombie, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		s_row = row;
		s_zType = zType;
		uintptr_t TargetAddress = GameModuleAddress + 0x16568;
		s_ChangeZombieRetAddress = TargetAddress + 9;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SeasonVersionChangeZombie, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}

}

void pvzManager::DisableChangeZombie()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x13055;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x16568;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x16568;
		MH_DisableHook((LPVOID)TargetAddress);
	}
}

int pvzManager::s_pType = 0;
uintptr_t pvzManager::s_ChangePeaRetAddress = 0;
void _declspec(naked) ChineseVersionChangePea() {
	__asm {
		pushad
		call rand
		mov ecx, 13
		xor edx, edx
		div ecx
		mov pvzManager::s_pType, edx
		popad
		push[pvzManager::s_pType]
		mov eax, [ebp + 4]
		push ebx
		sub ecx, 01
		push ecx
		push esi
		push edi
		mov ebx, 0x0040D620
		call ebx
		mov[eax + 0x74], 01
		jmp[pvzManager::s_ChangePeaRetAddress]
	}
}
void _declspec(naked) SteamVersionChangePea() {
	__asm {
		pushad
		call rand
		mov ecx, 13
		xor edx, edx
		div ecx
		mov pvzManager::s_pType, edx
		popad
		push[pvzManager::s_pType]
		mov eax, [ebp + 4]
		push ebx
		sub ecx, 01
		push ecx
		push esi
		push edi
		mov ebx, 0x00410BA0
		call ebx
		mov[eax + 0x74], 01
		jmp[pvzManager::s_ChangePeaRetAddress]
	}
}
void _declspec(naked) SeasonVersionChangePea() {
	__asm {
		pushad
		call rand
		mov ecx, 13
		xor edx, edx
		div ecx
		mov pvzManager::s_pType, edx
		popad
		push[pvzManager::s_pType]
		mov eax, [ebp + 4]
		push ebx
		sub ecx, 01
		push ecx
		push esi
		push edi
		mov ebx, 0x00410BA0
		call ebx
		mov[eax + 0x74], 01
		jmp[pvzManager::s_ChangePeaRetAddress]
	}
}

void pvzManager::EnableChangePea(int pType)
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x672A5;
		s_ChangePeaRetAddress = TargetAddress + 0x10;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &ChineseVersionChangePea, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x6D745;
		s_ChangePeaRetAddress = TargetAddress + 0x10;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SteamVersionChangePea, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x6D745;
		s_ChangePeaRetAddress = TargetAddress + 0x10;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SeasonVersionChangePea, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}

}

void pvzManager::DisableChangePea()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x672A5;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x6D745;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x6D745;
		MH_DisableHook((LPVOID)TargetAddress);
	}
}

uintptr_t pvzManager::s_ChangeNutRetAddress = 0;
void _declspec(naked) ChineseVersionChangeNut() {
	__asm {
		cmp dword ptr[esi + 0x40], 0x32
		jg originalCode
		mov[esi + 0x24], 0x11
		originalCode:
		add dword ptr[esi + 0x40], -04
			mov ecx, [esi + 0x40]
			jmp[pvzManager::s_ChangeNutRetAddress]
	}
}

void _declspec(naked) SteamVersionChangeNut() {
	__asm {
		cmp dword ptr[esi + 0x40], 0x32
		jg originalCode
		mov[esi + 0x24], 0x11
		originalCode:
		add dword ptr[esi + 0x40], -04
			mov ecx, [esi + 0x40]
			jmp[pvzManager::s_ChangeNutRetAddress]
	}
}

void _declspec(naked) SeasonVersionChangeNut() {
	__asm {
		cmp dword ptr[esi + 0x40], 0x32
		jg originalCode
		mov[esi + 0x24], 0x11
		originalCode:
		add dword ptr[esi + 0x40], -04
			mov ecx, [esi + 0x40]
			jmp[pvzManager::s_ChangeNutRetAddress]
	}
}

void pvzManager::EnableChangeNut()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x12FCF0;
		s_ChangeNutRetAddress = TargetAddress + 7;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &ChineseVersionChangeNut, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x1447A0;
		s_ChangeNutRetAddress = TargetAddress + 7;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SteamVersionChangeNut, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x1447A0;
		s_ChangeNutRetAddress = TargetAddress + 7;
		MH_Initialize();
		MH_CreateHook((LPVOID)TargetAddress, &SeasonVersionChangeNut, NULL);
		MH_EnableHook((LPVOID)TargetAddress);
	}
}

void pvzManager::DisableChangeNut()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x12FCF0;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x1447A0;
		MH_DisableHook((LPVOID)TargetAddress);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t TargetAddress = GameModuleAddress + 0x1447A0;
		MH_DisableHook((LPVOID)TargetAddress);
	}
}

void pvzManager::EnableNoCrater()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x1D796), { 0xC7,0x46,0x18,0x00,0x00,0x00,0x00,0x90 });
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x2136D), 0x74);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x2136D), 0x74);
	}
}

void pvzManager::DisableNoCrater()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x1D796), { 0x83,0x46,0x18,0xFF,0x83,0x7E,0x18,0x00 });
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x2136D), 0x75);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x2136D), 0x75);
	}
}

void pvzManager::EnableInfinityFreeze()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x12B421), 0x01);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x13FE06), 0x01);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x13FE06), 0x01);
	}
}

void pvzManager::DisableInfinityFreeze()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x12B421), 0xFF);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x13FE06), 0xFF);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x13FE06), 0xFF);
	}
}

void pvzManager::EnableFlowerAttck()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x676C2), { 0x90,0x90,0x90,0x90,0x90,0x90 });
		WriteBytes((GameModuleAddress + 0x677DA), { 0x90,0x90,0x90,0x90,0x90,0x90 });
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x6DB62), { 0x90,0x90,0x90,0x90,0x90,0x90 });
		WriteBytes((GameModuleAddress + 0x6DC7A), { 0x90,0x90,0x90,0x90,0x90,0x90 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x6DB62), { 0x90,0x90,0x90,0x90,0x90,0x90 });
		WriteBytes((GameModuleAddress + 0x6DC7A), { 0x90,0x90,0x90,0x90,0x90,0x90 });
	}

}

void pvzManager::DisableFlowerAttck()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x676C2), { 0x0F,0x85,0xBC,0x01,0x00,0x00 });
		WriteBytes((GameModuleAddress + 0x677DA), { 0x0F,0x8C,0xA1,0x00,0x00,0x00 });
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x6DB62), { 0x0F,0x85,0xBC,0x01,0x00,0x00 });
		WriteBytes((GameModuleAddress + 0x6DC7A), { 0x0F,0x8C,0xA1,0x00,0x00,0x00 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x6DB62), { 0x0F,0x85,0xBC,0x01,0x00,0x00 });
		WriteBytes((GameModuleAddress + 0x6DC7A), { 0x0F,0x8C,0xA1,0x00,0x00,0x00 });
	}
}

void pvzManager::EnableMineeTime()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x5FE54), 0x84);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress+0x69646),{0x31,0xC0,0x90});
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69646), { 0x31,0xC0,0x90 });
	}
}

void pvzManager::DisableMineeTime()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x5FE54), 0x85);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x69646), { 0x7E,0x04,0x48 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69646), { 0x7E,0x04,0x48 });
	}
}

void pvzManager::EnableInstantExplosion()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x63408), { 0x90,0x90 });
	}
}

void pvzManager::DisableInstantExplosion()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x63408), { 0x75,0x06 });
	}
}

void pvzManager::EnableAshPlant()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x1D905), { 0x90,0x90 });
		WriteBytes((GameModuleAddress + 0x1D91F), { 0x90,0x90 });
	}
}

void pvzManager::DisableAshPlant()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x1D905), { 0x7C,0x38 });
		WriteBytes((GameModuleAddress + 0x1D91F), { 0x74,0x1E });
	}

}

void pvzManager::EnableMushroomAwakening()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x5DE83), 0xEB);
	}
	else if(VersionResult == 1){
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x64197), 0xEB);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x64197), 0xEB);
	}
}

void pvzManager::DisableMushroomAwakening()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x5DE83), 0x74);
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteByte((GameModuleAddress + 0x64197), 0x74);
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteByte((GameModuleAddress + 0x64197), 0x74);
	}
}

void pvzManager::EnableChangeButter()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x64BD6), { 0x90,0x90 });
	}
}

void pvzManager::DisableChangeButter()
{
	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x64BD6), { 0x75,0x44 });
	}
}





