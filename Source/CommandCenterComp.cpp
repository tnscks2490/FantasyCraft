#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{

}

CommandCenterComp::~CommandCenterComp() {}

void CommandCenterComp::update(float delta) {}
