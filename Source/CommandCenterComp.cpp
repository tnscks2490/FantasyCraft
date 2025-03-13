#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"
#include "DrawComp.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

CommandCenterComp::~CommandCenterComp() {}

void CommandCenterComp::MessageProc(ActorMessage& msg)
{

    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        if (mBuilder == nullptr && msg.sender->mActorType == ActorType::SCV)
        {
            if (msg.sender->mUnitComp->mCurAction == ActionState::Building)
                mBuilder = msg.sender;
        }

        ActorMessage Msg = {MsgType::SendInfo, mActor, nullptr, nullptr};
        SendActorMessage(msg.sender, Msg);
    } break;

    case MsgType::Build_Cancel:
    {
        if (!IsBuild)
            mBuilder = nullptr;
    }break;
    default:
        break;
    }
}

void CommandCenterComp::update(float delta)
{
    if (!IsBuild && mBuilder)
    {
        if (mBuilder->mActorType == ActorType::SCV)
        {
            mTimer += delta;
            BuildingTime += delta;
            if (mTimer > 1.0f)
            {
                mTimer = 0.f;
                mStatus.HP += MaxHP / MaxBuildTime;
                test = BuildingTime / 20.f;
                if (test != drawidx)
                {
                    drawidx = test;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::CommandCenter,
                        ECharAct::Idle, ECharDir::Face, drawidx);
                }
                

                printf("%f초 \n", BuildingTime);
                if (BuildingTime >= MaxBuildTime)
                {
                    test++;
                    drawidx = test;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::CommandCenter,
                        ECharAct::Idle, ECharDir::Face, drawidx);
                    IsBuild = true;
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);
                    mBuilder = nullptr; 
                }
            }
        }

    }
}
