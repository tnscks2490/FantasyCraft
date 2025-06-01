#include "pch.h"
#include "GasComp.h"
#include "DrawComp.h"

GasComp::GasComp(Actor* actor) : UnitComp(actor)
{
    actor->mUnitComp = this;
    mUnitName        = "Gas";
   
}

GasComp::~GasComp() {}

void GasComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::Gathering:
    {
        if (!isGathering)
        {
            isGathering = true;
            mGather     = msg.sender;
            mActor->mDrawComp->CreateGatheringNode(ActorType::SCV);
        }
    }break;
    default:
        break;
    }
}

void GasComp::update(float delta)
{
    if (isGathering)
    {
        mTimer += delta;
        if (mTimer >= GatherTime)
        {
            mTimer = 0.f;
            isGathering = false;
            //메세지 보내기 넣으면될듯?
            mResource -= 8;
            ActorMessage msg = {MsgType::GatherMineral, mActor, nullptr, nullptr};
            SendActorMessage(mGather, msg);
            mActor->mDrawComp->RemoveGatherAnim();
        }
    }
}
