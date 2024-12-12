#include "pch.h"
#include "Actor.h"
#include "MarineComp.h"

MarineComp::MarineComp(Actor* actor):UnitComp(actor)
{
    actor->mUnitComp = this;
}

MarineComp::~MarineComp() {}

void MarineComp::update(float delta) {}
