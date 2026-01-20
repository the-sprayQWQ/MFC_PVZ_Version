#pragma once
#include "../BaseManager/baseManager.h"
class zombieManager :
    public baseManager
{
public:
    //僵尸行数和种类
    static int s_zType;
    static int s_row;
    //更改僵尸种类和出现位置返回地址
    static uintptr_t s_boardAddress;
    static uintptr_t s_changeZombieCall;
    static uintptr_t s_ChangeZombieRetAddress;

    //哪行召唤什么僵尸
    void AddZombies(int row, int zType);
    //种僵尸
    void SetZombies(int column, int row, int zType);


    //出怪间隔
    void AllAttack();


    //开启与关闭修改僵尸出现行数和种类
    void EnableChangeZombie(int row, int zType);
    void DisableChangeZombie();




    //开启与关闭无限刷怪
    void EnableInfinityZombies();
    void DisableInfinityZombies();
    //开启与关闭暂停出怪
    void EnablePauseSpawn();
    void DisablePauseSpawn();
};

