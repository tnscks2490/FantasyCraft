#pragma once
#include "UnitComp.h"



class CommandCenterComp : public UnitComp
{
public:
    CommandCenterComp(Actor* actor);
    ~CommandCenterComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    virtual bool IsBuild() override {return isBuild;}

    
    virtual float GetCurLoadTime() override { return BuildingTime; }
    virtual float GetMaxLoadTime() override { return MaxBuildTime; }
    virtual ActorType* GetCreateUnitList() override { return CreateUnitArray; }
    
    void AddSCV();
    void DeleteSCV();
    bool IsUnitArrayEmpty();


public:

    int MaxHP = 1500;
    float MaxBuildTime = 75.f;
    float BuildingTime = 0.f;
    bool isBuild    = false;

    float mTimer = 0.f;
    float SCVCreateTime = 13.f;


    Actor* mBuilder = nullptr;
    int drawidx     = 0;
    int changeImageIdx      = 0;

    ActorType* CreateUnitArray;
    bool IsCreatingUnit = false;

    BuildingSize Bsize = BuildingSize::Big;
};
