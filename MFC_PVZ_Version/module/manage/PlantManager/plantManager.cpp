#include "plantManager.h"

void plantManager::ChangePlant(int plaidPos, int plantType)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t plaidFirstOffset = memory::Read<uintptr_t>(boardAddress + m_Offsets.plaidFirstOffset);
	Write<int>((plaidFirstOffset + 0x5C + (plaidPos - 1) * 0x50), plantType);
}

void plantManager::SetPlant(int column, int row, int pType)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t setPlant = m_ModuleAddress + m_Offsets.setPlantOffset;
	__asm {
		pushad
		push 0xFFFFFFFF
		push pType
		mov eax, row
		push column
		push boardAddress
		mov ebx, setPlant
		call ebx
		popad
	}
}


int plantManager::s_Red = 255;
int plantManager::s_Green = 255;
int plantManager::s_Blue = 64;
uintptr_t plantManager::s_PlantColorRetAddress = 0;


void _declspec(naked) PlantColorHOOK() {
	__asm {
		push[plantManager::s_Blue]
		mov edx, [plantManager::s_Green]
		mov ecx, [plantManager::s_Red]
		jmp[plantManager::s_PlantColorRetAddress]
	}
}

void plantManager::ChangePlantColor(int Red, int Green, int Blue)
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

void plantManager::restorePlantColor()
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

int plantManager::s_pType = 0;
uintptr_t plantManager::s_ChangePeaRetAddress = 0;
uintptr_t plantManager::s_ChangePeaCall = 0;
void _declspec(naked) ChangePea() {
	__asm {
		pushad
		call rand
		mov ecx, 13
		xor edx, edx
		div ecx
		mov plantManager::s_pType, edx
		popad
		push[plantManager::s_pType]
		mov eax, [ebp + 4]
		push ebx
		sub ecx, 01
		push ecx
		push esi
		push edi
		mov ebx, [plantManager::s_ChangePeaCall]
		call ebx
		mov[eax + 0x74], 01
		jmp[plantManager::s_ChangePeaRetAddress]
	}
}
void plantManager::EnableChangePea(int pType)
{

	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changePeaOffset;
	s_ChangePeaCall = m_ModuleAddress + m_Offsets.changePeaCallOffset;
	s_ChangePeaRetAddress = TargetAddress + 0x10;
	MH_Initialize();
	MH_CreateHook((LPVOID)TargetAddress, &ChangePea, NULL);
	MH_EnableHook((LPVOID)TargetAddress);

}

void plantManager::DisableChangePea()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changePeaOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

uintptr_t plantManager::s_ChangeNutRetAddress = 0;
void _declspec(naked) ChangeNut() {
	__asm {
		cmp dword ptr[esi + 0x40], 0x32
		jg originalCode
		mov[esi + 0x24], 0x11
		originalCode:
		add dword ptr[esi + 0x40], -04
			mov ecx, [esi + 0x40]
			jmp[plantManager::s_ChangeNutRetAddress]
	}
}

void plantManager::EnableChangeNut()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeNutOffset;
	MH_Initialize();
	MH_CreateHook((LPVOID)TargetAddress, &ChangeNut, NULL);
	MH_EnableHook((LPVOID)TargetAddress);
}

void plantManager::DisableChangeNut()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeNutOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

void plantManager::EnablePeaDamage()
{
	WriteByte((m_ModuleAddress + m_Offsets.peaDamageOffset), 0x00);
}

void plantManager::DisablePeaDamage()
{
	WriteByte((m_ModuleAddress + m_Offsets.peaDamageOffset), 0x01);
}

void plantManager::EnablePlantSpeed()
{
	WriteByte((m_ModuleAddress + m_Offsets.plantSpeedOffset), 0x84);
}

void plantManager::DisablePlantSpeed()
{
	WriteByte((m_ModuleAddress + m_Offsets.plantSpeedOffset), 0x84);
}

void plantManager::EnableFlowerEat()
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

void plantManager::DisableFlowerEat()
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

void plantManager::AllEnchant()
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t ZombieBase = Read<uintptr_t>(boardAddress + m_Offsets.zombieBaseOffset);
	uintptr_t MaxZombiesNum = Read<uintptr_t>(boardAddress + m_Offsets.zombieMaxNumOffset);
	uintptr_t AllEnchant = m_ModuleAddress + m_Offsets.allEnchantOffset;
	for (int i = 0; i < MaxZombiesNum; i++) {
		uintptr_t ZombiesPtr = ZombieBase + (i * m_Offsets.zombieNextOffset);
		int hp = Read<int>(ZombiesPtr + 0xC8);
		if (hp > 0) {
			__asm {
				pushad
				mov esi, ZombiesPtr
				mov eax, AllEnchant
				call eax
				popad
			}
		}
	}
}

void plantManager::EnableNoCrater()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noCraterOffset), m_Offsets.noCraterData);
}

void plantManager::DisableNoCrater()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noCraterOffset), m_Offsets.restoreCraterData);
}

void plantManager::EnableInfinityFreeze()
{
	WriteByte((m_ModuleAddress + m_Offsets.infinityFreezeOffset), 0x01);
}

void plantManager::DisableInfinityFreeze()
{
	WriteByte((m_ModuleAddress + m_Offsets.infinityFreezeOffset), 0xFF);
}

void plantManager::EnableFlowerAttck()
{
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset1), { 0x90,0x90,0x90,0x90,0x90,0x90 });
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset2), { 0x90,0x90,0x90,0x90,0x90,0x90 });
}

void plantManager::DisableFlowerAttck()
{
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset1), { 0x0F,0x85,0xBC,0x01,0x00,0x00 });
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset2), { 0x0F,0x8C,0xA1,0x00,0x00,0x00 });
}

void plantManager::EnableMineeTime()
{
	WriteBytes((m_ModuleAddress + m_Offsets.mineeTimeOffset), m_Offsets.mineeTimeData);
}

void plantManager::DisableMineeTime()
{
	WriteBytes((m_ModuleAddress + m_Offsets.mineeTimeOffset), m_Offsets.restoremineeTimeData);
}

void plantManager::EnableInstantExplosion()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantExplosionOffset), { 0x90,0x90 });
}

void plantManager::DisableInstantExplosion()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantExplosionOffset), { 0x75,0x06 });
}

void plantManager::EnableAshPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset1), { 0x90,0x90 });
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset2), { 0x90,0x90 });
}

void plantManager::DisableAshPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset1), m_Offsets.restoreAshPlantData1);
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset2), m_Offsets.restoreAshPlantData2);
}

void plantManager::EnableMushroomAwakening()
{
	WriteByte((m_ModuleAddress + m_Offsets.mushroomAwakingOffset), 0xEB);
}

void plantManager::DisableMushroomAwakening()
{
	WriteByte((m_ModuleAddress + m_Offsets.mushroomAwakingOffset), 0x74);
}

void plantManager::EnableChangeButter()
{
	WriteBytes((m_ModuleAddress + m_Offsets.changeButterOffset), { 0x90,0x90 });
}

void plantManager::DisableChangeButter()
{
	WriteBytes((m_ModuleAddress + m_Offsets.changeButterOffset), { 0x75,0x44 });
}

void plantManager::EnableInstantBurn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantBurnOffset), { 0x90,0x90 });
}

void plantManager::DisableInstantBurn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantBurnOffset), { 0x75,0x06 });
}

void plantManager::EnableAllBurn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allBurnOffset), { 0x90,0x90 });
}

void plantManager::DisableAllBurn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.allBurnOffset), { 0x75,0x39 });
}