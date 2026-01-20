#pragma once
#include "../BaseManager/baseManager.h"
class plantManager :
    public baseManager
{
public:

    //静态成员RGB值
    static int s_Red;
    static int s_Green;
    static int s_Blue;
    //修改颜色HOOK返回的地址
    static uintptr_t s_PlantColorRetAddress;


    //豌豆子弹类型
    static int s_pType;
    //修改豌豆类型返回地址
    static uintptr_t s_ChangePeaRetAddress;
    static uintptr_t s_ChangePeaCall;
    //修改建国变窝瓜返回地址
    static uintptr_t s_ChangeNutRetAddress;


    //变更植物
    void ChangePlant(int plaidPos, int plantType);

    //种植物
    void SetPlant(int column, int row, int pType);

    //修改植物颜色HOOK
    void ChangePlantColor(int Red, int Green, int Blue);
    void restorePlantColor();

    //开启与关闭修改豌豆子弹
    void EnableChangePea(int pType);
    void DisableChangePea();
    //开启与关闭建国变窝瓜
    void EnableChangeNut();
    void DisableChangeNut();


    //开启与关闭豌豆帧伤
    void EnablePeaDamage();
    void DisablePeaDamage();

    //开启与关闭植物射速
    void EnablePlantSpeed();
    void DisablePlantSpeed();

    //全屏魅惑
    void AllEnchant();

    //开启与关闭大嘴花无咀嚼
    void EnableFlowerEat();
    void DisableFlowerEat();

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
    //开启与关闭火爆辣椒瞬间燃烧
    void EnableInstantBurn();
    void DisableInstantBurn();
    //开启与关闭火爆辣椒全屏秒杀
    void EnableAllBurn();
    void DisableAllBurn();
};

