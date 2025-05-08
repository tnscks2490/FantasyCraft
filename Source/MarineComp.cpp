#include "pch.h"
#include "Actor.h"
#include "MarineComp.h"
#include "DrawComp.h"

MarineComp::MarineComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Marine);
    mUnitName = "Terran Marine";
}

MarineComp::~MarineComp()
{
}

void MarineComp::update(float delta)
{
}

void MarineComp::MessageProc(ActorMessage& msg)
{
    
    switch (msg.msgType)
    {
    case MsgType::SetTarget:
    {
        //TODO: 여기 해결할것
        
        auto mTarget = msg.sender;

        if (mTarget == mActor)
            return;

        if (mActor->mWeaponComp->DoAttack(mTarget))
        {
            auto pos = mTarget->GetPosition() - mActor->GetPosition();
            mActor->mDrawComp->ChangeCurDir(pos);
        } 
    }
    break;
    default:
        break;
    }
}
