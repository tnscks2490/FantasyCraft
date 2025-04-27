#pragma once
#include "UnitComp.h"



class EngineeringBayComp : public UnitComp
{
public:
    EngineeringBayComp(Actor* actor);
    ~EngineeringBayComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    
};
