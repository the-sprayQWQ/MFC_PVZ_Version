#pragma once
#include "../readwrite/memory.h"
#include "../../Global.h"
class pvzManager :
    public memory
{
public:
    void SetSunlight(int value);
};

