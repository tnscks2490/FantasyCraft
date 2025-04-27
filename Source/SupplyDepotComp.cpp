#include "pch.h"
#include "Actor.h"
#include "SupplyDepotComp.h"
#include "DrawComp.h"

SupplyDepotComp::SupplyDepotComp(Actor* actor) : UnitComp(actor)
{
 
}

SupplyDepotComp::~SupplyDepotComp() {}

void SupplyDepotComp::MessageProc(ActorMessage& msg) {}

void SupplyDepotComp::update(float delta) {}
