#include "pch.h"
#include "Actor.h"
#include "DrawComp.h"
#include "RefineryComp.h"

RefineryComp::RefineryComp(Actor* actor) : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Refinery);
    mUnitName = "Terran Refinery";
    BuildAnimChangeTime = MaxBuildTime / 4.f;
}

RefineryComp::~RefineryComp() {}

void RefineryComp::MessageProc(ActorMessage& msg)
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
    case MsgType::Gathering:
    {
        isGathering = true;
        mGather     = msg.sender;
        mGather->GetRoot()->setVisible(false);
    }
    break;
    default:
        break;
    }
}

void RefineryComp::update(float delta)
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
                        mActor->mDrawComp->ChangeAnimByIndex(ECharName::Refinery, ECharAct::Building,
                                                             ECharDir::Face, drawidx);
                    }
                }

                printf("%f초 \n", BuildingTime);
            }
        }
    }

    if (isGathering)
    {
        mTimer += delta;
        if (mTimer >= GatherTime)
        {
            mTimer      = 0.f;
            isGathering = false;
            // 메세지 보내기 넣으면될듯?
            mResource -= 8;
            ActorMessage msg = {MsgType::GatherGas, mActor, nullptr, nullptr};
            SendActorMessage(mGather, msg);
        }
    }

}
