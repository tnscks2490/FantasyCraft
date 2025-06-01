#include "pch.h"
#include "Actor.h"
#include "CommandCenterComp.h"
#include "PlayerEventSystem.h"
#include "DrawComp.h"
#include "PathFind.h"
#include "Player.h"

CommandCenterComp::CommandCenterComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::CommandCenter);
    mUnitName = "Terran CommandCenter";
    for (int i = 0; i < 5; i++)
    {
        CreateUnitArray[i] = ActorType::None;
    }

    BuildAnimChangeTime = MaxBuildTime / 4.f;
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
                mActor->mDrawComp->CreateDemageNode(ActorType::SCV);
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
    case MsgType::Cancel:
    {
        if (!IsBuild())
        {
            mCurAction = ActionState::Death;
            ActorMessage msg = {MsgType::Build_Cancel, mActor, nullptr, nullptr};
            SendActorMessage(mBuilder, msg);
            mBuilder = nullptr;
        }
    }
    break;
    case MsgType::Create_SCV:
    {
        AddSCV();
    }
    break;
    case MsgType::GiveResource:
    {
        PEvent event = {EventType::GetResource,8,0};
        SendEvent(event);
    } break;


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
                mStatus.HP += (int)(mStatus.MaxHP * 0.9f) / MaxBuildTime;
                if (BuildingTime >= MaxBuildTime)
                {
                    ActorMessage msg = {MsgType::Build_Complete, mActor, nullptr, nullptr};
                    SendActorMessage(mBuilder, msg);

                    isBuild          = true;
                    mCurAction = ActionState::Idle;
                    mBuilder   = nullptr;

                }
                else
                {
                    changeImageIdx = BuildingTime / BuildAnimChangeTime;
                    if (changeImageIdx != drawidx)
                    {
                        drawidx = changeImageIdx;
                        mActor->mDrawComp->ChangeAnimByIndex(ECharName::CommandCenter, ECharAct::Building,
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
            if (unitTimer >= SCVCreateTime)
            {
                unitTimer = 0.f;
                SendPK_Data(GetCreateCommand(CreateUnitArray[0]), mActor->GetPosition() + ax::Vec2(0, -100));
                DeleteSCV();

                if (IsUnitArrayEmpty())
                {
                    IsCreatingUnit = false;

                    PK_Data data;
                    data.ClientID = TcpClient::get()->GetID();
                    data.input    = 12;
                    data.pos      = ax::Vec2(mActor->idx, 0);
                    TcpClient::get()->SendMessageToServer(data);
                    
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

    PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = 11;
    data.pos      = ax::Vec2(mActor->idx, 0);
    TcpClient::get()->SendMessageToServer(data);

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

void CommandCenterComp::MakeComplete()
{
    isBuild = true;
    mStatus.HP = mStatus.MaxHP;

}
