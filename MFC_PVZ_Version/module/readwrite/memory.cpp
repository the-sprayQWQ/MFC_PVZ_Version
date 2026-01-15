#include "memory.h"
#include <vector>
#include <cstring>

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

void memory::WriteBytes(uintptr_t address, const BYTE* data, size_t size)
{
	DWORD oldProtect;
	if (VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		__try {
			// 使用 memcpy 批量拷贝
			memcpy((void*)address, data, size);
		}
		__except (1) {}

		VirtualProtect((void*)address, size, oldProtect, &oldProtect);
	}
}

void memory::WriteBytes(uintptr_t address, const std::vector<BYTE>& bytes)
{
	WriteBytes(address, bytes.data(), bytes.size());
}
