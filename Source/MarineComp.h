#pragma once
#include "UnitComp.h"


class MarineComp : public UnitComp
{
public:
    MarineComp(Actor* actor);
    ~MarineComp();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;

public:

    short mPop      = 1;
};
