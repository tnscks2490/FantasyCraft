#pragma once
#include "UnitComp.h"



class BarrackComp : public UnitComp
{
public:
    BarrackComp(Actor* actor);
    ~BarrackComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    
};
