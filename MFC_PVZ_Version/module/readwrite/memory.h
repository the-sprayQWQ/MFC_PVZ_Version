#include <Windows.h>

class memory
{
private:
public:
	static uintptr_t GetModuleAddress(LPCSTR ModuleName);

	template <typename T>
	T Read(uintptr_t address) {
		__try {
		}
		__except (1) {
			return 0;
		}
	}

	template <typename T>
	void Write(uintptr_t address,T value) {
		__try {
		}
		__except (1) {
		}
	}

	void WriteByte(uintptr_t address,BYTE value);
};

