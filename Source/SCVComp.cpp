#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"



SCVComp::SCVComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

SCVComp::~SCVComp() {}

void SCVComp::update(float delta)
{
    mTimer += delta;
    if (mTimer >= 5)
    {

        Building();

        mTimer = -300;
    }
}

void SCVComp::Repair()
{

}

void SCVComp::Building(ax::Vec2 pos)
{
    PK_Data data;
    data.ClientID = mActor->mID;
    data.input    = 0;

    Actor* CC = SpawnCommandCenter(mActor->GetRoot()->getParent(),data);
    CC->SetPosition(ax::Vec2(200,200));
}
