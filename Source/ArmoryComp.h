#pragma once
#include "UnitComp.h"



class ArmoryComp : public UnitComp
{
public:
    ArmoryComp(Actor* actor);
    ~ArmoryComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    virtual bool IsBuild() override { return isBuild; }

    virtual float GetCurLoadTime() override { return BuildingTime; }
    virtual float GetMaxLoadTime() override { return MaxBuildTime; }


public:
    float MaxBuildTime        = 50.f;
    float BuildingTime        = 0.f;
    float BuildAnimChangeTime = 0.f;
    bool isBuild              = false;

    float mTimer = 0.f;

    Actor* mBuilder    = nullptr;
    int drawidx        = 0;
    int changeImageIdx = 0;

    BuildingSize Bsize = BuildingSize::Middle;
   
};
