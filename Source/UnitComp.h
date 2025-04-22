#pragma once
#include "IActorComp.h"


enum class ActionState
{
    Idle,
    Building,
    Attack,
    Move,
    Death,
    Create_Unit,

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
    virtual ActorType* GetCreateUnitList() { return nullptr; }

    std::string_view GetUnitName() { return mUnitName; }

    Status mStatus;
    ActionState mCurAction = ActionState::Idle;
    UnitArea mUnitArea     = UnitArea::None;


    int killCount          = 0;
    ax::Sprite* mWireFrame = nullptr;

    std::string_view mUnitName = "";


};

