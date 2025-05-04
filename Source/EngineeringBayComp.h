#pragma once
#include "UnitComp.h"
#include "UpgradeBluePrint.h"


class EngineeringBayComp : public UnitComp
{
public:
    EngineeringBayComp(Actor* actor);
    ~EngineeringBayComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    virtual bool IsBuild() override { return isBuild; }

    virtual float GetCurLoadTime() override { return BuildingTime; }
    virtual float GetMaxLoadTime() override { return MaxBuildTime; }
    virtual float GetCurUpgradeTime() override { return CurUT; }
    virtual float GetMaxUpgradeTime() override { return MaxUT; }


     
public:
    float MaxBuildTime        = 38.f;
    float BuildingTime        = 0.f;
    float BuildAnimChangeTime = 0.f;
    bool isBuild              = false;

    bool isUpgrade = false;

    float MaxUT = 0;
    float CurUT= 0;

    int BionicAT = 0;
    int BionicDF = 0;
    UpgradeType mCurUpgrade = UpgradeType::None;





    float mTimer = 0.f;

    Actor* mBuilder    = nullptr;
    int drawidx        = 0;
    int changeImageIdx = 0;

    BuildingSize Bsize = BuildingSize::Big;
    
};
