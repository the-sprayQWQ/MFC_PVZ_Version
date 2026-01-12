#pragma once
#include "../readwrite/memory.h"
#include "../../Global.h"
#include <stdio.h>
class pvzManager :
    public memory
{
public:
    //设置阳光
    void SetSunlight(int value);
    //哪行召唤什么僵尸
    void AddZombies(int row, int type);
    //开启与关闭无冷却
    void EnableNoCooldown();
    void DisableNoCooldown();
    //开启与关闭自动收集物品
    void EnableAutoCollect();
    void DisableAutoCollect();
    //开启与关闭豌豆帧伤
    void EnablePeaDamage();
    void DisablePeaDamage();
    //开启与关闭后台运行
    void EnableNoPause();
    void DisableNoPause();
};

