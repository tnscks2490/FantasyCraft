#pragma once
#include "UnitComp.h"



class SupplyDepotComp : public UnitComp
{
public:
    SupplyDepotComp(Actor* actor);
    ~SupplyDepotComp();
    virtual void MessageProc(ActorMessage& msg) override;


    virtual void update(float delta) override;

public:


};
