#include "pch.h"
#include "MineralComp.h"

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
        isGathering = true;
        mGather     = msg.sender;


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
        }
    }
}
