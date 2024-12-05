#include "WorkerComp.h"

WorkerComp::WorkerComp(Actor* actor)
    : UnitComp(actor)
{
    mArea = UnitArea::Ground;
    mType = UnitType::GatheringUnit;
}

WorkerComp::~WorkerComp() {}

void WorkerComp::update(float delta) {}
