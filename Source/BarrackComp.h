#pragma once
#include "UnitComp.h"



class BarrackComp : public UnitComp
{
public:
    BarrackComp(Actor* actor);
    ~BarrackComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    virtual bool IsBuild() override { return isBuild; }

    virtual float GetCurLoadTime() override { return BuildingTime; }
    virtual float GetMaxLoadTime() override { return MaxBuildTime; }
    virtual float GetUnitTimer() override { return unitTimer; }
    virtual ActorType* GetCreateUnitList() override { return CreateUnitArray; }


    void AddMarine();
    void AddMedic();
    void AddGhost();
    void AddFireBat();
    void AddUnit(ActorType type);

    void DeleteMarine();
    void DeleteMedic();
    void DeleteGhost();
    void DeleteFireBat();
    bool IsUnitArrayEmpty();

public:
    int MaxHP          = 1000;
    float MaxBuildTime = 50.f;
    float BuildingTime = 0.f;
    bool isBuild       = false;

    float mTimer = 0.f;

    float unitTimer     = 0.f;
    float SCVCreateTime = 13.f;

    Actor* mBuilder    = nullptr;
    int drawidx        = 0;
    int changeImageIdx = 0;

    ActorType CreateUnitArray[5];
    bool IsCreatingUnit = false;

    BuildingSize Bsize = BuildingSize::Big;
};
