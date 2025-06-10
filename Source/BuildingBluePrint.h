#pragma once

#include "Actor.h"




struct BuildingBluePrint
{
    ActorType type = ActorType::None;
    int buildTime   = 0;
    int mineralCost = 0;
    int gasCost     = 0;
};



BuildingBluePrint& FindBuildingBP(ActorType type);
