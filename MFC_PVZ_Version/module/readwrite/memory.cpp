#include "memory.h"

uintptr_t memory::GetModuleAddress(LPCSTR ModuleName)
{
	return (uintptr_t)GetModuleHandleA(ModuleName);
}
