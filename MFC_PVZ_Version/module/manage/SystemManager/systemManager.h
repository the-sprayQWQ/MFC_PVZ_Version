#pragma once
#include "../BaseManager/baseManager.h"
class systemManager :
    public baseManager
{
public:
    //设置阳光
    void SetSunlight(int value);
    //开启与关闭自动收集物品
    void EnableAutoCollect();
    void DisableAutoCollect();
    //开启与关闭无冷却
    void EnableNoCooldown();
    void DisableNoCooldown();
    //修改关卡
    void ChangeLevel(int Level);
    //刷道具
    void GetProps(int pType);
    //开启与关闭后台运行
    void EnableNoPause();
    void DisableNoPause();
    //全屏扣血秒杀
    void ReduceHealth();
};

