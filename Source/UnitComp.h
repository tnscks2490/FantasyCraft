#pragma once
#include "IActorComp.h"
#include "Weapon/WeaponComp.h"

enum class ActionState
{
    Idle,
    Building,
    Attack,
    Move,
    Death,
    Create_Unit,
    Upgrade,

};

enum class BuildingSize
{
    Small,
    Middle,
    Big,
};


enum class UnitRace
{
    None,
    Terran,
    Protoss,
    Zerg,
};

enum class UnitArea
{
    None,
    Ground,
    Sky,
};

struct Status
{
    int MaxHP = 0;
    int HP = 0;

    int MaxMp = 0;
    int MP = 0;

    int SD = 0;
    int AT = 0;
    int DF = 0;
    int RA = 0;
    int SI = 0;
};

struct UnitQueueSlott
{
    ActorType UnitType = ActorType::None;
    int mineral        = 0;
    int gas            = 0;
    float pop          = 0.f;
};







class UnitComp : public IActorComp
{
public:
    UnitComp(Actor* actor);
    ~UnitComp();

    virtual void update(float delta) override;
    virtual void SetUnitStatus(ActorType Atype);
    virtual bool IsBuild() { return false; }
    virtual float GetCurLoadTime() { return 0; }
    virtual float GetMaxLoadTime() { return 0; }
    virtual float GetUnitTimer() { return 0; }
    virtual float GetCurUpgradeTime() { return 0; }
    virtual float GetMaxUpgradeTime() { return 0; }
    virtual Actor* GetTarget() { return mTarget; }
    virtual bool IsCmdLocked() { return cmdLocked; }


    virtual ActorType* GetCreateUnitList() { return nullptr; }

    std::string_view GetUnitName() { return mUnitName; }

    Status mStatus;
    ActionState mCurAction = ActionState::Idle;
    UnitArea mUnitArea     = UnitArea::None;


    bool cmdLocked = false;

    int killCount          = 0;
    std::string_view mUnitName = "";


    /// <summary>
    /// 나중에 센서로 옮길것
    /// </summary>
    Actor* mTarget = nullptr;
};

