#pragma once
#include "UnitComp.h"



class CommandCenterComp : public UnitComp
{
public:
    CommandCenterComp(Actor* actor);
    ~CommandCenterComp();
    virtual void MessageProc(ActorMessage& msg) override;


    virtual void update(float delta) override;

    void AddSCV();
    void DeleteSCV();
    bool IsUnitArrayEmpty();


public:

    int MaxHP = 1500;
    float MaxBuildTime = 75.f;
    float BuildingTime = 0.f;
    bool IsBuild    = false;

    float mTimer = 0.f;
    float SCVCreateTime = 13.f;


    Actor* mBuilder = nullptr;
    int drawidx     = 0;
    int test      = 0;

    ActorType* CreateUnitArray;
    bool IsCreatingUnit = false;

    BuildingSize Bsize = BuildingSize::Big;
};
