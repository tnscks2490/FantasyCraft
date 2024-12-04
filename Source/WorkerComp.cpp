#include "WorkerComp.h"

WorkerComp::WorkerComp(Actor* actor)
    : UnitComp(actor)
{
    mUUpDown = UnitUpDown::Ground;
}

WorkerComp::~WorkerComp() {}

void WorkerComp::update(float delta) {}
