#include <Windows.h>
#include <vector>

class memory
{
private:
public:
	static uintptr_t GetModuleAddress(LPCSTR ModuleName);

	template <typename T>
	T Read(uintptr_t address) {
		__try {
			return *(T*)address;
		}
		__except (1) {
			return 0;
		}
	}

	template <typename T>
	void Write(uintptr_t address,T value) {
		__try {
			*(uintptr_t*)address = value;
		}
		__except (1) {
		}
	}

	void WriteByte(uintptr_t address,BYTE value);
	void WriteBytes(uintptr_t address, const BYTE* data, size_t size);
	void WriteBytes(uintptr_t address, const std::vector<BYTE>& bytes);
};

