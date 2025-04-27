#pragma once
#include "UnitComp.h"



class StarPortComp : public UnitComp
{
public:
    StarPortComp(Actor* actor);
    ~StarPortComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;
    
};
