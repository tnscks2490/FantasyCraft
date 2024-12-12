#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"



SCVComp::SCVComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

SCVComp::~SCVComp() {}

void SCVComp::update(float delta) {}

void SCVComp::Repair()
{

}

void SCVComp::Building()
{

}
