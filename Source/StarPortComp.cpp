#include "pch.h"
#include "Actor.h"
#include "StarPortComp.h"
#include "DrawComp.h"

StarPortComp::StarPortComp(Actor* actor) : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::StarPort);
    mUnitName = "Terran StarPort";
    for (int i = 0; i < 5; i++)
    {
        CreateUnitArray[i] = ActorType::None;
    }
    BuildAnimChangeTime = MaxBuildTime / 4.f;
}

StarPortComp::~StarPortComp() {}

void StarPortComp::MessageProc(ActorMessage& msg)
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
    case MsgType::Create_Wraith:  AddUnit(ActorType::Wraith);break;
    case MsgType::Create_Valkyrie:  AddUnit(ActorType::Valkyrie);  break;
    case MsgType::Create_DropShip:   AddUnit(ActorType::DropShip);      break;
    case MsgType::Create_ScienceVessel: AddUnit(ActorType::ScienceVessel); break;
    case MsgType::Create_BattleCruiser:  AddUnit(ActorType::BattleCruiser);  break;
    default:
        break;
    }
}

void StarPortComp::update(float delta)
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
                        mActor->mDrawComp->ChangeAnimByIndex(ECharName::StarPort, ECharAct::Building,
                                                             ECharDir::Face, drawidx);
                    }
                }

                printf("%f초 \n", BuildingTime);
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

void StarPortComp::AddUnit(ActorType type)
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

void StarPortComp::DeleteUnit()
{
    CreateUnitArray[0] = CreateUnitArray[1];
    CreateUnitArray[1] = CreateUnitArray[2];
    CreateUnitArray[2] = CreateUnitArray[3];
    CreateUnitArray[3] = CreateUnitArray[4];
    CreateUnitArray[4] = ActorType::None;
}

bool StarPortComp::IsUnitArrayEmpty()
{
    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] != ActorType::None)
            return false;
    }
    return true;
}

float StarPortComp::GetUnitBuildTime()
{
    auto bp = FindUnitBP(CreateUnitArray[0]);

    return bp.buildTime;
}
