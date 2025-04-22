#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"
#include "DrawComp.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::CommandCenter);
    for (int i = 0; i < 5; i++)
    {
        CreateUnitArray[i] = ActorType::None;
    }


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
        if (!isBuild)
            mBuilder = nullptr;
    }break;


    case MsgType::Create_SCV:
    {
        AddSCV();
    }
    break;
    default:
        break;
    }

}

void CommandCenterComp::update(float delta)
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
                changeImageIdx = BuildingTime / 20.f;
                if (changeImageIdx != drawidx)
                {
                    drawidx = changeImageIdx;
                     mActor->mDrawComp->ChangeAnimByIndex(ECharName::CommandCenter,
                        ECharAct::Building, ECharDir::Face, drawidx);
                }
                

                printf("%f초 \n", BuildingTime);
                if (BuildingTime >= MaxBuildTime)
                {
                    changeImageIdx++;
                    drawidx = changeImageIdx;
                    mActor->mDrawComp->ChangeAnimByIndex(ECharName::CommandCenter,
                        ECharAct::Idle, ECharDir::Face, drawidx);
                    isBuild          = true;
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);
                    mCurAction = ActionState::Idle;
                    mBuilder = nullptr;
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
            if (unitTimer >= SCVCreateTime)
            {
                unitTimer = 0.f;
                DeleteSCV();

                PK_Data data;
                data.ClientID = TcpClient::get()->GetID();
                data.pos      = mActor->GetPosition() + ax::Vec2(0, -100);
                data.input    = 100;
                TcpClient::get()->SendMessageToServer(data);


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


void CommandCenterComp::AddSCV()
{
    if (!IsCreatingUnit)
        IsCreatingUnit = true;

    mCurAction = ActionState::Create_Unit;

    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] == ActorType::None)
        {
            CreateUnitArray[i] = ActorType::SCV;
            return;
        }
    }
}

void CommandCenterComp::DeleteSCV()
{
    CreateUnitArray[0] = CreateUnitArray[1];
    CreateUnitArray[1] = CreateUnitArray[2];
    CreateUnitArray[2] = CreateUnitArray[3];
    CreateUnitArray[3] = CreateUnitArray[4];
    CreateUnitArray[4] = ActorType::None;
}

bool CommandCenterComp::IsUnitArrayEmpty()
{
    for (int i = 0; i < 5; i++)
    {
        if (CreateUnitArray[i] == ActorType::SCV)
            return false;
    }
    return true;
}
