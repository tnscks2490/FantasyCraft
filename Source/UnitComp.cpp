#include "pch.h"
#include "UnitComp.h"
#include "Actor.h"


UnitComp::UnitComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mUnitComp = this;
}

UnitComp::~UnitComp() {}

void UnitComp::update(float delta) {}

void UnitComp::SetUnitStatus(ActorType Atype)
{
   // 업그레이드때문에 추후에 할것
}
