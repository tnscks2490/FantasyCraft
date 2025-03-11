#pragma once
#include "UnitComp.h"



class SupplyDpotComp : public UnitComp
{
public:
    SupplyDpotComp(Actor* actor);
    ~SupplyDpotComp();
    virtual void MessageProc(ActorMessage& msg) override;


    virtual void update(float delta) override;

public:

    int MaxHP = 1500;
    float MaxBuildTime = 75.f;
    float BuildingTime = 0.f;
    bool IsBuild    = false;

    float mTimer = 0.f;

    Actor* mBuilder = nullptr;
    int drawidx     = 0;
    float test      = 0.f;

};
