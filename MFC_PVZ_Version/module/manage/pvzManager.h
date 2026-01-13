#pragma once
#include "../readwrite/memory.h"
#include "../../Global.h"
#include "../../minhook/include/MinHook.h"
#include <stdio.h>
#ifdef _M_IX86
#pragma comment(lib, "minhook/lib/libMinHook.x86.lib") // 32位游戏必选这个！
#else
#pragma comment(lib, "minhook/lib/libMinHook.x64.lib")
#endif


class pvzManager :
    public memory
{
public:
    //静态成员RGB值
    static int s_Red;
    static int s_Green;
    static int s_Blue;
    //修改颜色HOOK返回的地址
    static uintptr_t s_PlantColorRetAddress;

    //设置阳光
    void SetSunlight(int value);
    //哪行召唤什么僵尸
    void AddZombies(int row, int zType);
    //刷道具
    void GetProps(int pType);
    //种植物
    void SetPlant(int column,int row,int pType);
    //修改植物颜色HOOK
    void ChangePlantColor(int Red,int Green,int Blue);
    void restorePlantColor();
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
    //开启与关闭植物射速
    void EnablePlantSpeed();
    void DisablePlantSpeed();
    //开启与关闭大嘴花无咀嚼
    void EnableFlowerEat();
    void DisableFlowerEat();
    
};

