#pragma once

#include "Actor.h"




struct UnitBluePrint
{
    ActorType type = ActorType::None;
    int buildTime   = 0;
    int mineralCost = 0;
    int gasCost     = 0;
    float supplyCost = 0.f;
};


UnitBluePrint& FindUnitBP(ActorType type);
