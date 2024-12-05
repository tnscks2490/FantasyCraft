#include "GatheringComp.h"

GatheringComp::GatheringComp(Actor* actor)
    : UnitComp(actor)
{
    mArea = UnitArea::Ground;
    mType = UnitType::GatheringUnit;
}

GatheringComp::~GatheringComp() {}

void GatheringComp::CreateSCV()
{
    printf("SCV 생성\n");
}

void GatheringComp::CreateProbe()
{
    printf("프로브 생성\n");
}

void GatheringComp::CreateDrone()
{
    printf("드론 생성\n");
}

void GatheringComp::update(float delta) {}

void GatheringComp::Repair() {}
