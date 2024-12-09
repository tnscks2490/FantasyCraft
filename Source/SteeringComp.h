#pragma once
#include "IActorComp.h"



class SteeringComp : public IActorComp
{
public:
    SteeringComp(Actor* actor);
    ~SteeringComp();

    virtual void update(float delta) override;

};

