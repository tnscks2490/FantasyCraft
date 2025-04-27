#pragma once
#include "UnitComp.h"



class ArmoryComp : public UnitComp
{
public:
    ArmoryComp(Actor* actor);
    ~ArmoryComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
   
};
