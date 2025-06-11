#include "pch.h"
#include "MineralComp.h"
#include "DrawComp.h"

MineralComp::MineralComp(Actor* actor): UnitComp(actor)
{
    actor->mUnitComp = this;
    mUnitName        = "Mineral";
   
}

MineralComp::~MineralComp() {}

void MineralComp::MessageProc(ActorMessage& msg)
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

void MineralComp::update(float delta)
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
            mGather = nullptr;
        }
    }
}
