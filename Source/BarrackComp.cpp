#include "pch.h"
#include "Actor.h"
#include "BarrackComp.h"
#include "DrawComp.h"

BarrackComp::BarrackComp(Actor* actor) :UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Barrack);
    for (int i = 0; i < 5; i++)
    {
        CreateUnitArray[i] = ActorType::None;
    }
}

BarrackComp::~BarrackComp() {}

void BarrackComp::MessageProc(ActorMessage& msg)
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

    case MsgType::Create_Marine:  AddUnit(ActorType::Marine);  break;
    case MsgType::Create_Medic:   AddUnit(ActorType::Medic);   break;
    case MsgType::Create_FireBat: AddUnit(ActorType::FireBat); break;
    case MsgType::Create_Ghost:   AddUnit(ActorType::Ghost);   break;
    default:
        break;
    }
}

void BarrackComp::update(float delta)
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
                changeImageIdx = BuildingTime / 15.f;
                if (changeImageIdx != drawidx)
                {
                    drawidx = changeImageIdx;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::Barrack, ECharAct::Building, ECharDir::Face,
                                                         drawidx);
                }

                printf("%f초 \n", BuildingTime);
                if (BuildingTime >= MaxBuildTime)
                {
                    changeImageIdx++;
                    drawidx = changeImageIdx;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::Barrack, ECharAct::Idle, ECharDir::Face,
                                                         drawidx);
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

    if (isBuild)
    {
        if (IsCreatingUnit)
        {
            unitTimer += delta;
            if (unitTimer >= GetUnitBuildTime())
            {
                unitTimer = 0.f;
                SendPK_Data(GetCreateCommand(CreateUnitArray[0]), mActor->GetPosition() + ax::Vec2(0, -100));
                DeleteUnit();

                if (IsUnitArrayEmpty())
                {
                    IsCreatingUnit = false;
                    mCurAction     = ActionState::Idle;
                }
                else
                {
                    printf("안비었음!");
                }
            }
        }
    }
}


void BarrackComp::AddUnit(ActorType type)
{
    if (!IsCreatingUnit)
        IsCreatingUnit = true;

    mCurAction = ActionState::Create_Unit;

    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] == ActorType::None)
        {
            CreateUnitArray[i] = type;
            return;
        }
    }
}

void BarrackComp::DeleteUnit()
{
    CreateUnitArray[0] = CreateUnitArray[1];
    CreateUnitArray[1] = CreateUnitArray[2];
    CreateUnitArray[2] = CreateUnitArray[3];
    CreateUnitArray[3] = CreateUnitArray[4];
    CreateUnitArray[4] = ActorType::None;
}

bool BarrackComp::IsUnitArrayEmpty()
{
    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] != ActorType::None)
            return false;
    }
    return true;
}

float BarrackComp::GetUnitBuildTime()
{
    auto bp = FindUnitBP(CreateUnitArray[0]);

    return bp.buildTime;
}
