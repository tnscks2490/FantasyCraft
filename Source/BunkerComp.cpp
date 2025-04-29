#include "pch.h"
#include "Actor.h"
#include "DrawComp.h"
#include "BunkerComp.h"

BunkerComp::BunkerComp(Actor* actor) : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Bunker);
    mUnitName = "Terran Bunker";

    BuildAnimChangeTime = MaxBuildTime / 4.f;
}

BunkerComp::~BunkerComp() {}

void BunkerComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::Contacted: { }break;
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

void BunkerComp::update(float delta)
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
                mStatus.HP += (int)(mStatus.MaxHP * 0.9f) / MaxBuildTime;
                if (BuildingTime >= MaxBuildTime)
                {
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);

                    isBuild    = true;
                    mCurAction = ActionState::Idle;
                    mBuilder   = nullptr;
                }
                else
                {
                    changeImageIdx = BuildingTime / BuildAnimChangeTime;
                    if (changeImageIdx != drawidx)
                    {
                        drawidx = changeImageIdx;
                        mActor->mDrawComp->ChangeAnimByIndex(ECharName::Bunker, ECharAct::Building,
                                                             ECharDir::Face, drawidx);
                    }
                }

                printf("%f초 \n", BuildingTime);
            }
        }
    }
}
