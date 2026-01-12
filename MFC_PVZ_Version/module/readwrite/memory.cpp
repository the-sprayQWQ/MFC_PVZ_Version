#include "memory.h"

uintptr_t memory::GetModuleAddress(LPCSTR ModuleName)
{
	return (uintptr_t)GetModuleHandleA(ModuleName);
}

void memory::WriteByte(uintptr_t address, BYTE value)
{
	DWORD oldProtect;
	if (VirtualProtect((void*)address, 1, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		__try{
			*(BYTE*)address = value;
		}
		__except (1) {}
	}
	VirtualProtect((void*)address, 1, oldProtect, &oldProtect);
}
