#pragma once
#include <cstdint>
#include <vector>

struct GameOffset
{
	uintptr_t BasePtrOffset;
	uintptr_t BoardOffset;
	uintptr_t SunOffset;
	uintptr_t plaidFirstOffset;
	uintptr_t addZombiesOffset;
	uintptr_t getPropsOffset;
	uintptr_t setPlantOffset;
	uintptr_t setZombieOffset;
	uintptr_t mineZombieOffset;
	uintptr_t levelFirstOffset;
	uintptr_t levelFinalOffset;
	uintptr_t currentZombiesNumOffset;
	uintptr_t allAttackOffset;
	uintptr_t coolDownOffset;
	uintptr_t autoCollectOffset;
	uintptr_t peaDamageOffset;
	uintptr_t noPauseOffset;
	uintptr_t plantSpeedOffset;
	uintptr_t changeZombiesOffset;
	uintptr_t changeZombiesCallOffset;
	uintptr_t changePeaOffset;
	uintptr_t changePeaCallOffset;
	uintptr_t changeNutOffset;
	uintptr_t noCraterOffset;
	uintptr_t infinityFreezeOffset;
	uintptr_t flowerAttackOffset1;
	uintptr_t flowerAttackOffset2;
	uintptr_t mineeTimeOffset;
	uintptr_t instantExplosionOffset;
	uintptr_t ashPlantOffset1;
	uintptr_t ashPlantOffset2;
	uintptr_t mushroomAwakingOffset;
	uintptr_t changeButterOffset;
	uintptr_t infinityZombieOffset;
	uintptr_t pauseSpawnOffset;
	uintptr_t allEnchantOffset;
	uintptr_t zombieBaseOffset;
	uintptr_t zombieNextOffset;
	uintptr_t zombieMaxNumOffset;
	uintptr_t instantBurnOffset;
	uintptr_t allBurnOffset;
	std::vector<unsigned char>restoreSpawnData;
	std::vector<unsigned char>infinityZombieData;
	std::vector<unsigned char>restoreZombieData;
	std::vector<unsigned char>restoreAshPlantData1;
	std::vector<unsigned char>restoreAshPlantData2;
	std::vector<unsigned char>mineeTimeData;
	std::vector<unsigned char>restoremineeTimeData;
	std::vector<unsigned char>noCraterData;
	std::vector<unsigned char>restoreCraterData;
	std::vector<unsigned char> noPauseData;
	std::vector<unsigned char> restorePauseData;

	static GameOffset GetSteamVersion();
	static GameOffset GetChineseVersion();
};