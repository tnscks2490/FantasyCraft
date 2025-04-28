#pragma once
#include "UnitComp.h"



class SupplyDepotComp : public UnitComp
{
public:
    SupplyDepotComp(Actor* actor);
    ~SupplyDepotComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    virtual bool IsBuild() override { return isBuild; }

public:

    int MaxHP          = 500;
    float MaxBuildTime = 25.f;
    float BuildingTime = 0.f;
    bool isBuild       = false;

    float mTimer = 0.f;

    Actor* mBuilder    = nullptr;
    int drawidx        = 0;
    int changeImageIdx = 0;


    BuildingSize Bsize = BuildingSize::Small;
};
