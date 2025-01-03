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
    if (msg.sender->mActorType == ActorType::SCV)
        mBuilder = msg.sender;
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
                    IsBuild = true;
                }
            }
        }

    }
}
