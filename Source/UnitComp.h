#pragma once
#include "IActorComp.h"

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
};



class UnitComp : public IActorComp
{
public:
    UnitComp(Actor* actor);
    ~UnitComp();

    virtual void update(float delta) override;
    virtual void SetUnitStatus(int hp,int mp, int sd, int at, int df);


    Status mStatus;

};

