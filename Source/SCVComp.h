#pragma once
#include "UnitComp.h"


class SCVComp : public UnitComp
{
public:
    SCVComp(Actor* actor);
    ~SCVComp();

    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;

    virtual void Building(ax::Vec2 pos) override;
    void Repair();



public:
    float mTimer    = 0;
    bool IsWorking = false;
    short mPop      = 1;
};
