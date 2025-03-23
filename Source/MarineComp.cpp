#include "pch.h"
#include "Actor.h"
#include "MarineComp.h"
#include "DrawComp.h"

MarineComp::MarineComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

MarineComp::~MarineComp() {}

void MarineComp::update(float delta) {}

void MarineComp::MessageProc(ActorMessage& msg)
{
    
    switch (msg.msgType)
    {
    case MsgType::SetTarget:
    {
        mTarget = msg.sender;

        ActorMessage msg = {MsgType::Attack, mActor, nullptr, nullptr};
        SendActorMessage(mTarget, msg);

        mCurAction = ActionState::Attack;


    }
    break;
    default:
        break;
    }
}
