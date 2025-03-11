#include "pch.h"
#include "Actor.h"
#include "SupplyDpotComp.h"
#include "DrawComp.h"

SupplyDpotComp::SupplyDpotComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
}

SupplyDpotComp::~SupplyDpotComp() {}

void SupplyDpotComp::MessageProc(ActorMessage& msg)
{

    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        if (mBuilder == nullptr && msg.sender->mActorType == ActorType::SCV)
            mBuilder = msg.sender;

    } break;
    default:
        break;
    }
}

void SupplyDpotComp::update(float delta)
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
                }
            }
        }

    }
}
