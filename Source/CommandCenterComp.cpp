#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

CommandCenterComp::~CommandCenterComp() {}

void CommandCenterComp::update(float delta) {}
