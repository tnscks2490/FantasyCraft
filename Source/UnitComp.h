#pragma once
#include "IActorComp.h"


enum class ActionState
{
    Idle,
    Building,
    Attack,
    Move,
    Death,

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
    int HP = 0;
    int MP = 0;
    int SD = 0;
    int AT = 0;
    int DF = 0;
    int RA = 0;
    int SI = 0;
};



class UnitComp : public IActorComp
{
public:
    UnitComp(Actor* actor);
    ~UnitComp();

    virtual void update(float delta) override;
    virtual void SetUnitStatus(ActorType Atype);


    Status mStatus;
    ActionState mCurAction = ActionState::Idle;
    UnitArea mUnitArea     = UnitArea::None;

    ax::Sprite* mWireFrame = nullptr;

};

