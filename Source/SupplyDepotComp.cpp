#include "pch.h"
#include "Actor.h"
#include "SupplyDepotComp.h"
#include "DrawComp.h"

SupplyDepotComp::SupplyDepotComp(Actor* actor) : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::SupplyDepot);
}

SupplyDepotComp::~SupplyDepotComp() {}

void SupplyDepotComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
    }
    break;
    case MsgType::Build_Start:
    {
        if (mBuilder == nullptr && msg.sender->mActorType == ActorType::SCV)
        {
            if (msg.sender->mUnitComp->mCurAction == ActionState::Building)
            {
                mBuilder   = msg.sender;
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
            mBuilder   = msg.sender;
            mCurAction = ActionState::Building;
        }
    }
    break;

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
        if (!isBuild)
            mBuilder = nullptr;
    }
    break;
    default:
        break;
    }
}

void SupplyDepotComp::update(float delta)
{
    if (!isBuild && mBuilder)
    {
        if (mBuilder->mActorType == ActorType::SCV)
        {
            mTimer += delta;
            BuildingTime += delta;
            if (mTimer >= 1.0f)
            {
                mTimer = 0.f;
                mStatus.HP += MaxHP / MaxBuildTime;
                changeImageIdx = BuildingTime / 7.f;
                if (changeImageIdx != drawidx)
                {
                    drawidx = changeImageIdx;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::SupplyDepot, ECharAct::Building, ECharDir::Face,
                                                         drawidx);
                }

                printf("%f초 \n", BuildingTime);
                if (BuildingTime >= MaxBuildTime)
                {
                    //changeImageIdx++;
                    //drawidx = changeImageIdx;
                    //mActor->mDrawComp->ChangeAnim(ECharName::SupplyDepot, ECharAct::Idle, ECharDir::Face);
                    isBuild          = true;
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);
                    mCurAction = ActionState::Idle;
                    mBuilder   = nullptr;
                    mTimer     = 0.f;
                }
            }
        }
    }
}
