#pragma once
#include "UnitComp.h"


class GasComp : public UnitComp
{
public:
    GasComp(Actor* actor);
    ~GasComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;

    
    float GatherTime = 3.36f;
    float mTimer  = 0.f;


    Actor* mGather = nullptr;
    bool isGathering = false;
    int mResource = 1500;
};
