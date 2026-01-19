#include "pvzManager.h"

pvzManager::pvzManager()
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

void pvzManager::SetSunlight(int value)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	Write<int>((boardAddress + m_Offsets.SunOffset), value);
}

void pvzManager::ChangePlant(int plaidPos, int plantType)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t plaidFirstOffset = memory::Read<uintptr_t>(boardAddress + m_Offsets.plaidFirstOffset);
	Write<int>((plaidFirstOffset + 0x5C + (plaidPos - 1) * 0x50), plantType);
}

void pvzManager::AddZombies(int row, int zType)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t addZombies = m_ModuleAddress + m_Offsets.addZombiesOffset;
	__asm {
		pushad
		push row
		push zType
		mov eax, boardAddress
		mov ebx, addZombies
		call ebx
		popad
	}
}

void pvzManager::GetProps(int pType)
{
	typedef void(__thiscall* GetProps)(void* thisPtr, int pos, int FixValue, int type, int zero);
	GetProps getProps = (GetProps)(m_ModuleAddress + m_Offsets.getPropsOffset);
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	if (!pType) {
		pType = 4;
	}
	getProps((void*)boardAddress, 0, 0x3C, pType, 0);
}

void pvzManager::SetPlant(int column, int row, int pType)
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

void pvzManager::SetZombies(int column, int row, int zType)
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t mineZombiePtr = memory::Read<uintptr_t>(boardAddress + m_Offsets.mineZombieOffset);
	uintptr_t setZombies = m_ModuleAddress + m_Offsets.setZombieOffset;
	__asm {
		pushad
		push column
		push zType
		mov eax, row
		mov ecx, mineZombiePtr
		mov esi, setZombies
		call esi
		popad
	}
}

void pvzManager::ChangeLevel(int Level)
{
	uintptr_t levelAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.levelFirstOffset);
	Write<int>((levelAddress + m_Offsets.levelFinalOffset), Level);
}

void pvzManager::AllEnchant()
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);

	if (VersionResult == 0) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		uintptr_t ChineseVersionGameBaseAddress = Read<uintptr_t>((GameModuleAddress + 0x2A9EC0));
		uintptr_t GameBoardAddress = Read<uintptr_t>(ChineseVersionGameBaseAddress + 0x768);
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
					mov esi, ZombiesPtr
					mov eax, 0x005444E0
					call eax
					popad
				}
			}
		}
	}
}

void pvzManager::AllAttack()
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	int currentZombiesNum = memory::Read<int>(boardAddress + m_Offsets.currentZombiesNumOffset);
	if (currentZombiesNum < 900) {
		Write<int>((boardAddress + m_Offsets.allAttackOffset), 1);
	}
}

void pvzManager::ReduceHealth()
{
	if (VersionResult == 0) { return; }
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
	WriteByte((m_ModuleAddress + m_Offsets.coolDownOffset), 0x01);
}

void pvzManager::DisableNoCooldown()
{
	WriteByte((m_ModuleAddress + m_Offsets.coolDownOffset), 0x01);
}

void pvzManager::EnableAutoCollect()
{
	WriteByte((m_ModuleAddress + m_Offsets.autoCollectOffset), 0x01);
}

void pvzManager::DisableAutoCollect()
{
	WriteByte((m_ModuleAddress + m_Offsets.autoCollectOffset), 0x00);
}

void pvzManager::EnablePeaDamage()
{
	WriteByte((m_ModuleAddress + m_Offsets.peaDamageOffset), 0x00);
}

void pvzManager::DisablePeaDamage()
{
	WriteByte((m_ModuleAddress + m_Offsets.peaDamageOffset), 0x01);
}

void pvzManager::EnableNoPause()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noPauseOffset), m_Offsets.noPauseData);
}

void pvzManager::DisableNoPause()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noPauseOffset), m_Offsets.restorePauseData);
}

void pvzManager::EnablePlantSpeed()
{
	WriteByte((m_ModuleAddress + m_Offsets.plantSpeedOffset), 0x84);
}

void pvzManager::DisablePlantSpeed()
{
	WriteByte((m_ModuleAddress + m_Offsets.plantSpeedOffset), 0x84);
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
uintptr_t pvzManager::s_boardAddress = 0;
uintptr_t pvzManager::s_changeZombieCall = 0;
uintptr_t pvzManager::s_ChangeZombieRetAddress = 0;

void _declspec(naked) ChangeZombie() {
	__asm {
		pushad
		push[pvzManager::s_row]
		push[pvzManager::s_zType]
		mov eax, [pvzManager::s_boardAddress]
		mov ebx, [pvzManager::s_changeZombieCall]
		call ebx
		popad
		jmp[pvzManager::s_ChangeZombieRetAddress]
	}
}
void pvzManager::EnableChangeZombie(int row, int zType)
{
	s_row = row;
	s_zType = zType;
	s_boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeZombiesOffset;
	s_changeZombieCall = m_ModuleAddress + m_Offsets.changeZombiesCallOffset;
	s_ChangeZombieRetAddress = TargetAddress + 9;
	MH_Initialize();
	MH_CreateHook((LPVOID)TargetAddress, &ChangeZombie, NULL);
	MH_EnableHook((LPVOID)TargetAddress);
}

void pvzManager::DisableChangeZombie()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeZombiesOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

int pvzManager::s_pType = 0;
uintptr_t pvzManager::s_ChangePeaRetAddress = 0;
uintptr_t pvzManager::s_ChangePeaCall = 0;
void _declspec(naked) ChangePea() {
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
		mov ebx, [pvzManager::s_ChangePeaCall]
		call ebx
		mov[eax + 0x74], 01
		jmp[pvzManager::s_ChangePeaRetAddress]
	}
}
void pvzManager::EnableChangePea(int pType)
{

	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changePeaOffset;
	s_ChangePeaCall = m_ModuleAddress + m_Offsets.changePeaCallOffset;
	s_ChangePeaRetAddress = TargetAddress + 0x10;
	MH_Initialize();
	MH_CreateHook((LPVOID)TargetAddress, &ChangePea, NULL);
	MH_EnableHook((LPVOID)TargetAddress);

}

void pvzManager::DisableChangePea()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changePeaOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

uintptr_t pvzManager::s_ChangeNutRetAddress = 0;
void _declspec(naked) ChangeNut() {
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
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeNutOffset;
	MH_Initialize();
	MH_CreateHook((LPVOID)TargetAddress, &ChangeNut, NULL);
	MH_EnableHook((LPVOID)TargetAddress);
}

void pvzManager::DisableChangeNut()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeNutOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

void pvzManager::EnableNoCrater()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noCraterOffset), m_Offsets.noCraterData);
}

void pvzManager::DisableNoCrater()
{
	WriteBytes((m_ModuleAddress + m_Offsets.noCraterOffset), m_Offsets.restoreCraterData);
}

void pvzManager::EnableInfinityFreeze()
{
	WriteByte((m_ModuleAddress + m_Offsets.infinityFreezeOffset), 0x01);
}

void pvzManager::DisableInfinityFreeze()
{
	WriteByte((m_ModuleAddress + m_Offsets.infinityFreezeOffset), 0xFF);
}

void pvzManager::EnableFlowerAttck()
{
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset1), { 0x90,0x90,0x90,0x90,0x90,0x90 });
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset2), { 0x90,0x90,0x90,0x90,0x90,0x90 });
}

void pvzManager::DisableFlowerAttck()
{
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset1), { 0x0F,0x85,0xBC,0x01,0x00,0x00 });
	WriteBytes((m_ModuleAddress + m_Offsets.flowerAttackOffset2), { 0x0F,0x8C,0xA1,0x00,0x00,0x00 });
}

void pvzManager::EnableMineeTime()
{
	WriteBytes((m_ModuleAddress + m_Offsets.mineeTimeOffset), m_Offsets.mineeTimeData);
}

void pvzManager::DisableMineeTime()
{
	WriteBytes((m_ModuleAddress + m_Offsets.mineeTimeOffset), m_Offsets.restoremineeTimeData);
}

void pvzManager::EnableInstantExplosion()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantExplosionOffset), { 0x90,0x90 });
}

void pvzManager::DisableInstantExplosion()
{
	WriteBytes((m_ModuleAddress + m_Offsets.instantExplosionOffset), { 0x75,0x06 });
}

void pvzManager::EnableAshPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset1), { 0x90,0x90 });
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset2), { 0x90,0x90 });
}

void pvzManager::DisableAshPlant()
{
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset1), m_Offsets.restoreAshPlantData1);
	WriteBytes((m_ModuleAddress + m_Offsets.ashPlantOffset2), m_Offsets.restoreAshPlantData2);
}

void pvzManager::EnableMushroomAwakening()
{
	WriteByte((m_ModuleAddress + m_Offsets.mushroomAwakingOffset), 0xEB);
}

void pvzManager::DisableMushroomAwakening()
{
	WriteByte((m_ModuleAddress + m_Offsets.mushroomAwakingOffset), 0x74);
}

void pvzManager::EnableChangeButter()
{
	WriteBytes((m_ModuleAddress + m_Offsets.changeButterOffset), { 0x90,0x90 });
}

void pvzManager::DisableChangeButter()
{
	WriteBytes((m_ModuleAddress + m_Offsets.changeButterOffset), { 0x75,0x44 });
}

void pvzManager::EnableInfinityZombies()
{
	WriteBytes((m_ModuleAddress + m_Offsets.infinityZombieOffset), m_Offsets.infinityZombieData);
}

void pvzManager::DisableInfinityZombies()
{
	WriteBytes((m_ModuleAddress + m_Offsets.infinityZombieOffset), m_Offsets.restoreZombieData);
}

void pvzManager::EnablePauseSpawn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.pauseSpawnOffset), { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 });
}

void pvzManager::DisablePauseSpawn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.pauseSpawnOffset), m_Offsets.restoreSpawnData);
}

void pvzManager::EnableInstantBurn()
{
	if (VersionResult == 0) {
		return;
	}else if(VersionResult == 1){
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x69802), { 0x90,0x90 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69802), { 0x90,0x90 });
	}
}

void pvzManager::DisableInstantBurn()
{
	if (VersionResult == 0) {
		return;
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x69802), { 0x75,0x06 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x69802), { 0x75,0x06 });
	}
}

void pvzManager::EnableAllBurn()
{
	if(VersionResult == 0){
		return;
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x6C942), { 0x90,0x90 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x6C942), { 0x90,0x90 });
	}
}

void pvzManager::DisableAllBurn()
{
	if (VersionResult == 0) {
		return;
	}
	else if (VersionResult == 1) {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("popcapgame1.exe");
		WriteBytes((GameModuleAddress + 0x6C942), { 0x75,0x39 });
	}
	else {
		uintptr_t GameModuleAddress = memory::GetModuleAddress("PlantsVsZombies.exe");
		WriteBytes((GameModuleAddress + 0x6C942), { 0x75,0x39 });
	}
}





