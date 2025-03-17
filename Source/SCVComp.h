#pragma once
#include "UnitComp.h"


class SCVComp : public UnitComp
{
public:
    SCVComp(Actor* actor);
    ~SCVComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;

    virtual void Building(ActorMessage& msg) override;
    void Repair();


    void Build_Continue(ActorMessage& msg);

    


public:
    float mTimer    = 0;
    bool IsWorking = false;
    short mPop      = 1;

    Actor* mBuilding = nullptr;
    
};
