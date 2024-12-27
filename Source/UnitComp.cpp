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

void UnitComp::SetUnitStatus(int hp, int mp,int sd, int at, int df)
{
    mStatus.HP = hp;
    mStatus.MP = mp;
    mStatus.SD = sd;
    mStatus.AT = at;
    mStatus.DF = df;
}
