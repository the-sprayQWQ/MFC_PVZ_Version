#pragma once
#include "../readwrite/memory.h"
#include "../../Global.h"
#include "../../minhook/include/MinHook.h"
#include "../../GameOffset/GameOffset.h"
#include <stdio.h>
#include <chrono>
#ifdef _M_IX86
#pragma comment(lib, "minhook/lib/libMinHook.x86.lib") // 32位游戏必选这个！
#else
#pragma comment(lib, "minhook/lib/libMinHook.x64.lib")
#endif


class pvzManager :
    public memory
{
private:
    uintptr_t m_GameBase;
    GameOffset m_Offsets;
    uintptr_t m_ModuleAddress;
public:
    //构造函数
    pvzManager();

    //静态成员RGB值
    static int s_Red;
    static int s_Green;
    static int s_Blue;
    //修改颜色HOOK返回的地址
    static uintptr_t s_PlantColorRetAddress;

    //僵尸行数和种类
    static int s_zType;
    static int s_row;
    //更改僵尸种类和出现位置返回地址
    static uintptr_t s_boardAddress;
    static uintptr_t s_changeZombieCall;
    static uintptr_t s_ChangeZombieRetAddress;

    //豌豆子弹类型
    static int s_pType;
    //修改豌豆类型返回地址
    static uintptr_t s_ChangePeaRetAddress;
    static uintptr_t s_ChangePeaCall;
    //修改建国变窝瓜返回地址
    static uintptr_t s_ChangeNutRetAddress;


    //设置阳光
    void SetSunlight(int value);
    //变更植物
    void ChangePlant(int plaidPos,int plantType);
    //哪行召唤什么僵尸
    void AddZombies(int row, int zType);
    //刷道具
    void GetProps(int pType);
    //种植物
    void SetPlant(int column,int row,int pType);
    //种僵尸
    void SetZombies(int column,int row,int zType);
    //修改关卡
    void ChangeLevel(int Level);
    //全屏魅惑
    void AllEnchant();
    //出怪间隔
    void AllAttack();
    //全屏扣血秒杀
    void ReduceHealth();
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
    //开启与关闭修改僵尸出现行数和种类
    void EnableChangeZombie(int row,int zType);
    void DisableChangeZombie();
    //开启与关闭修改豌豆子弹
    void EnableChangePea(int pType);
    void DisableChangePea();
    //开启与关闭建国变窝瓜
    void EnableChangeNut();
    void DisableChangeNut();
    //开启与关闭毁灭菇不留弹坑
    void EnableNoCrater();
    void DisableNoCrater();
    //开启与关闭寒冰菇无限冻结
    void EnableInfinityFreeze();
    void DisableInfinityFreeze();
    //开启与关闭大嘴花全屏攻击
    void EnableFlowerAttck();
    void DisableFlowerAttck();
    //开启与关闭土豆雷出土时间
    void EnableMineeTime();
    void DisableMineeTime();
    //开启与关闭樱桃炸弹瞬间爆炸
    void EnableInstantExplosion();
    void DisableInstantExplosion();
    //开启与关闭灰烬植物全屏秒杀
    void EnableAshPlant();
    void DisableAshPlant();
    //开启与关闭蘑菇免唤醒
    void EnableMushroomAwakening();
    void DisableMushroomAwakening();
    //开启与关闭玉米投手只投黄油
    void EnableChangeButter();
    void DisableChangeButter();
    //开启与关闭无限刷怪
    void EnableInfinityZombies();
    void DisableInfinityZombies();
    //开启与关闭暂停出怪
    void EnablePauseSpawn();
    void DisablePauseSpawn();
    //开启与关闭火爆辣椒瞬间燃烧
    void EnableInstantBurn();
    void DisableInstantBurn();
    //开启与关闭火爆辣椒全屏秒杀
    void EnableAllBurn();
    void DisableAllBurn();

};

