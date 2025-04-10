#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"
#include "DrawComp.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;

    BuildUnitList = new ActorType[1];
    BuildUnitList[0] = ActorType::SCV;


}

CommandCenterComp::~CommandCenterComp() {}

void CommandCenterComp::MessageProc(ActorMessage& msg)
{

    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        
    } break;
    case MsgType::Build_Start:
    {
        if (mBuilder == nullptr && msg.sender->mActorType == ActorType::SCV)
        {
            if (msg.sender->mUnitComp->mCurAction == ActionState::Building)
            {
                mBuilder = msg.sender;
                mCurAction = ActionState::Building;
            }
        }

        ActorMessage Msg = {MsgType::SendInfo, mActor, nullptr, nullptr};
        SendActorMessage(msg.sender, Msg);
    }
    break;
    case MsgType::Build_GetBuilder:
    {
        if (mBuilder == nullptr)
        {
            mBuilder = msg.sender;
            mCurAction = ActionState::Building;
        }
    } break;

    case MsgType::Build_Continue:
    {
        if (mBuilder == nullptr)
        {
            mBuilder = msg.sender;
        }
    }
    break;


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
                        ECharAct::Building, ECharDir::Face, drawidx);
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
                    mCurAction = ActionState::Idle;
                    mBuilder = nullptr; 
                }
            }
        }

    }
}
