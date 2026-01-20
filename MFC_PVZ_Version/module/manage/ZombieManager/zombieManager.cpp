#include "zombieManager.h"

void zombieManager::AddZombies(int row, int zType)
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

void zombieManager::SetZombies(int column, int row, int zType)
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

void zombieManager::AllAttack()
{
	uintptr_t boardAddress = memory::Read<uintptr_t>(m_GameBase + m_Offsets.BoardOffset);
	int currentZombiesNum = memory::Read<int>(boardAddress + m_Offsets.currentZombiesNumOffset);
	if (currentZombiesNum < 900) {
		Write<int>((boardAddress + m_Offsets.allAttackOffset), 1);
	}
}

int zombieManager::s_row = 0;
int zombieManager::s_zType = 0;
uintptr_t zombieManager::s_boardAddress = 0;
uintptr_t zombieManager::s_changeZombieCall = 0;
uintptr_t zombieManager::s_ChangeZombieRetAddress = 0;

void _declspec(naked) ChangeZombie() {
	__asm {
		pushad
		push[zombieManager::s_row]
		push[zombieManager::s_zType]
		mov eax, [zombieManager::s_boardAddress]
		mov ebx, [zombieManager::s_changeZombieCall]
		call ebx
		popad
		jmp[zombieManager::s_ChangeZombieRetAddress]
	}
}
void zombieManager::EnableChangeZombie(int row, int zType)
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

void zombieManager::DisableChangeZombie()
{
	uintptr_t TargetAddress = m_ModuleAddress + m_Offsets.changeZombiesOffset;
	MH_DisableHook((LPVOID)TargetAddress);
}

void zombieManager::EnableInfinityZombies()
{
	WriteBytes((m_ModuleAddress + m_Offsets.infinityZombieOffset), m_Offsets.infinityZombieData);
}

void zombieManager::DisableInfinityZombies()
{
	WriteBytes((m_ModuleAddress + m_Offsets.infinityZombieOffset), m_Offsets.restoreZombieData);
}

void zombieManager::EnablePauseSpawn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.pauseSpawnOffset), { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 });
}

void zombieManager::DisablePauseSpawn()
{
	WriteBytes((m_ModuleAddress + m_Offsets.pauseSpawnOffset), m_Offsets.restoreSpawnData);
}
