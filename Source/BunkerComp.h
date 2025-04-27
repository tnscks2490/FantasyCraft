#pragma once
#include "UnitComp.h"



class BunkerComp : public UnitComp
{
public:
    BunkerComp(Actor* actor);
    ~BunkerComp();
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void update(float delta) override;

};
