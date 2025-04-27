#include "pch.h"
#include "Actor.h"
#include "BarrackComp.h"
#include "DrawComp.h"

BarrackComp::BarrackComp(Actor* actor) :UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Barrack);
    for (int i = 0; i < 5; i++)
    {
        CreateUnitArray[i] = ActorType::None;
    }
}

BarrackComp::~BarrackComp() {}

void BarrackComp::MessageProc(ActorMessage& msg) {}

void BarrackComp::update(float delta) {}

void BarrackComp::AddMarine() {}

void BarrackComp::AddMedic() {}

void BarrackComp::AddGhost() {}

void BarrackComp::AddFireBat() {}

void BarrackComp::AddUnit(ActorType type)
{
    if (!IsCreatingUnit)
        IsCreatingUnit = true;

    mCurAction = ActionState::Create_Unit;

    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] == ActorType::None)
        {
            CreateUnitArray[i] = type;
            return;
        }
    }
}

void BarrackComp::DeleteMarine() {}

void BarrackComp::DeleteMedic() {}

void BarrackComp::DeleteGhost() {}

void BarrackComp::DeleteFireBat() {}

bool BarrackComp::IsUnitArrayEmpty()
{
    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] != ActorType::None)
            return false;
    }
    return true;
}
