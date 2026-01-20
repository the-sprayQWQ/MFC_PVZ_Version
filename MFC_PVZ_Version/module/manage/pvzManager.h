#pragma once
#include "../readwrite/memory.h"
#include "../../Global.h"
#include "../../GameOffset/GameOffset.h"
#include "./BaseManager/baseManager.h"
#include "./SystemManager/systemManager.h"
#include "./ZombieManager/zombieManager.h"
#include "./PlantManager/plantManager.h"
#include <stdio.h>
#include <chrono>

class pvzManager
{
public:
    systemManager system;
    plantManager plant;
    zombieManager zombies;
};

