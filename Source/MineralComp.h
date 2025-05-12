#pragma once
#include "UnitComp.h"


class MineralComp : public UnitComp
{
public:
    MineralComp(Actor* actor);
    ~MineralComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;

    
    float GatherTime = 1.99f;
    float mTimer  = 0.f;


    Actor* mGather = nullptr;


    bool isGathering = false;
    int mResource = 12000;
};
