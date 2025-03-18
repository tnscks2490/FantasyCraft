#pragma once
#include "preDefines.h"

enum class WeaponType
{
    None,
    Sword,
    Pick,
    Axe,
    WateringCan,
    Bow,
    Torch,

};


class Weapon
{
public:

    Weapon(Actor* actor) : mActor(actor) {}
    virtual ~Weapon() {}

    virtual void update(float delta) {}
    virtual bool AimAt(ax::Vec2 target) { return true; }
    virtual void ShootAt(ax::Vec2 pos) {}
    virtual double GetDesirability(double DistToTarget) { return true; }
    virtual void Use() {}

    void SetCoolTime(float coolTime) { mCoolTime = coolTime; }


    void CoolTime(float cooltime,float delta);

public:

    WeaponType mType;
    Actor* mActor = nullptr;

    bool IsUsing = false;
    float mCoolTime = 0.f;
};


