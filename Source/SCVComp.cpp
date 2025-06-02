#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "MessageSystem.h"
#include "TcpClient.h"
#include "BPComp.h"
#include "PathFind.h"
#include "MoveComp.h"
#include "Goal/Base/GoalComp.h"
#include "DrawComp.h"



SCVComp::SCVComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::SCV);
    mUnitName  = "Terran SCV";

}

SCVComp::~SCVComp()
{
    mBuilding = nullptr;
    if (mActor)
        mActor->mUnitComp = nullptr;
}

void SCVComp::MessageProc(ActorMessage& msg)
{
   
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        
    }break;
    case MsgType::Build:
    {
        ax::Vec2* pos = (ax::Vec2*)msg.data;

        int command = 0;
        switch (msg.sender->mBPComp->mBPType)
        {
        case ActorType::CommandCenter: command = 120;break;
        case ActorType::SupplyDepot: command = 121;break;
        case ActorType::Barrack: command = 122; break;
        case ActorType::EngineeringBay: command = 123; break;
        case ActorType::Academy: command = 124; break;
        case ActorType::Refinery: command = 125; break;
        case ActorType::Factory: command = 126; break;
        case ActorType::StarPort: command = 127; break;
        case ActorType::Armory: command = 128; break;
        case ActorType::ScienceFacility: command = 129; break;
        default:
            break;
        }


        PK_Data data;
        data.ClientID = mActor->idx;
        data.input    = command;
        data.pos      = *pos;
        TcpClient::get()->SendMessageToServer(data);
    }
        break;
    case MsgType::Do_Build:
        Building(msg);
        break;
    case MsgType::SendInfo:
    {
        mBuilding = msg.sender;
        AddGoal_DoingBuild(mActor, mBuilding);
    }
        break;
    case MsgType::Build_Complete:
        mBuilding = nullptr;
        cmdLocked = false;
        break;
    case MsgType::IsBuild_Complete:
    {
        if (mBuilding)
            AddGoal_DoingBuild(mActor, mBuilding);
    }break;

    case MsgType::Build_Continue:
    {
        Build_Continue(msg);
        cmdLocked = true;
    }break;

    case MsgType::Build_Cancel:
    {
        AddGoal_AllCancel(mActor);
        mBuilding = nullptr;
        cmdLocked = false;
    }
    break;

    case MsgType::Cancel:
    {
        if (mBuilding)
        {
            AddGoal_AllCancel(mActor);
            ActorMessage msg = {MsgType::Build_Cancel, mActor, nullptr, nullptr};
            SendActorMessage(mBuilding, msg);
            mBuilding = nullptr;
            cmdLocked = false;
        }
        AddGoal_AllCancel(mActor);
    }
    break;

    case MsgType::Attack:
    {
        if (msg.sender == nullptr || msg.sender->mUnitComp == nullptr)
        {
            printf("⚠️ 메시지 발신자(sender)가 유효하지 않음. 공격 무시\n");
            break;
        }
        int damage = msg.sender->mUnitComp->mStatus.AT - mStatus.DF;
        if (damage  <= 0 ) damage = 1;

        mStatus.HP -= damage;
        printf("남은 체력 : %d\n" ,mStatus.HP);

        SCVHpChange();
        mActor->mDrawComp->CreateDemageNode(msg.sender->mActorType);





        if (mActor->mUnitComp->mStatus.HP <= 0)
        {
            mCurAction = ActionState::Death;
            // 소멸자에 대한 정보를 넣는다.

            //SendPK_Data(117, mActor->GetPosition());
            //World::get()->Actor_PushBackDelete(mActor);
        }
    } 
    break;
    case MsgType::SetTarget:
    {
        if (msg.sender->mActorType == ActorType::Mineral)
        {
            if (mGatherResource == nullptr)
            {
                auto mMineral = msg.sender;
                //AddGoal_MoveAndGathering(mActor, mMineral);

                PK_Data data;
                data.ClientID = mActor->idx;
                data.input    = 130;
                data.pos      = ax::Vec2(mMineral->idx, 0);
                TcpClient::get()->SendMessageToServer(data);

            }
        }
        else if (msg.sender->mActorType == ActorType::Refinery)
        {
            auto refinery = msg.sender;
            AddGoal_MoveAndGathering(mActor, refinery);
        }
    }
    break;
    case MsgType::Gathering:
    {
        if (msg.sender->mActorType == ActorType::Mineral)
        {
            auto mineral = msg.sender;
            Gathering(mineral);
        }
        else if (msg.sender->mActorType == ActorType::Refinery)
        {
            auto gas = msg.sender;
            Gathering(gas);
        }
    } break;
    case MsgType::GatherMineral:
    {
        cmdLocked  = false;
        mCurAction = ActionState::Idle;
        mActor->mDrawComp->CreateCarryMineral();
        mItem = GetItem::Mineral;
        //미네랄 아이콘 생성하기

    }break;
    case MsgType::GatherGas:
    {
        mCurAction = ActionState::Idle;
        mActor->mDrawComp->CreateCarryGas();
        mItem = GetItem::Gas;
        mActor->GetRoot()->setVisible(true);
    } break;

    case MsgType::ReturnCargo:
    {
        mCurAction = ActionState::Idle;
        if (mCargo)
        {
            auto pos = World::get()->mPath->FindEmptyTileNearActor(mActor->GetPosition(), mCargo->GetPosition());
            AddGoal_ReturnCargo(mActor, mCargo);
        }
        else
        {
            if (SearchNearCargo())
            {
                auto pos = World::get()->mPath->FindEmptyTileNearActor(mActor->GetPosition(), mCargo->GetPosition());
                AddGoal_ReturnCargo(mActor, mCargo);
            }
            
        }

    }
    break;
    case MsgType::SearchCargo:
    {
        SearchNearCargo();
    }
    break;
    case MsgType::GiveResource:
    {
        if (msg.sender->mActorType == ActorType::CommandCenter)
        {
            if (mGatherResource)
            {
                GiveMineral();
                PushGoal_MoveAndGathering(mActor, mGatherResource);
            }
        }
    }
    default:
        break;
    }
}

void SCVComp::update(float delta) {

    if (mStatus.HP == 0)
    {
        printf("해당유닛 사망");
    }

    mTimer += delta;

    if (mTimer > 5.f)
    {
        auto t =  mActor->GetRoot()->getChildByName("EffectNode");
        mTimer = 0.f;
    }

    if (mTimer > 1.f)
    {
        mTimer = 0.f;
        if (mCurAction == ActionState::Building)
            printf("건설중입니다~~~~~~~~~~~~~~~~~~~~~~");
    }
}


void SCVComp::Repair()
{

}

void SCVComp::Gathering(Actor* resource)
{
    mGatherResource = resource;
    if (mGatherResource->mActorType == ActorType::Mineral)
        mCurAction = ActionState::Gathering;
    else if (mGatherResource->mActorType == ActorType::Refinery)
        mCurAction = ActionState::Idle;
    cmdLocked        = true;
    ActorMessage msg = {MsgType::Gathering,mActor,nullptr,nullptr};
    SendActorMessage(mGatherResource, msg);

    //이미지 바뀌는거까지 넣어야지
}

void SCVComp::GiveMineral()
{
    //mGatherResource = nullptr;
    mCurAction = ActionState::Idle;

    mActor->mDrawComp->RemoveCarryItem();
    if (mActor->mID == TcpClient::get()->GetID())
    {
        ActorMessage msg = {MsgType::GiveResource, mActor, nullptr, nullptr};
        SendActorMessage(mCargo, msg);

    }
    
    
}

void SCVComp::SCVHpChange()
{
    int hp = mStatus.HP;

    int t = 6 - (hp / 9);

    mActor->mDrawComp->ChangeHpBarByIndex(ECharName::SCV, t);
}

void SCVComp::Build_Continue(ActorMessage& msg)
{
    if (mBuilding == nullptr)
    {
        mBuilding = msg.sender;
        AddGoal_MoveAndContinueBuild(mActor, msg.sender);
    }
}

bool SCVComp::SearchNearCargo()
{
    Actor* nearCargo = nullptr;
    float len     = 10000000;
    for (auto ac : World::get()->w_ActorList)
    {
        if (ac->mID == mActor->mID && ac->mActorType == ActorType::CommandCenter)
        {
            if (length(mActor->GetPosition(), ac->GetPosition()) < len)
            {
                len = length(mActor->GetPosition(), ac->GetPosition());
                nearCargo = ac;
            }
        }
    }
    if (nearCargo)
    {
        mCargo = nearCargo;
        return true;
    }

    return false;
}

void SCVComp::Building(ActorMessage& msg)
{
    int command = 0;
    ActorType* buildingType = (ActorType*)msg.data;
    
    switch (*buildingType)
    {
    case ActorType::CommandCenter: command = 102; break;
    case ActorType::SupplyDepot:  command = 103;  break;
    case ActorType::Barrack:      command = 104;  break;
    case ActorType::EngineeringBay: command = 105; break;
    case ActorType::Refinery:       command = 106; break;
    case ActorType::Academy:        command = 107; break;
    case ActorType::Armory:        command = 108;  break;
    case ActorType::Bunker:       command = 109;   break;
    case ActorType::StarPort:     command = 110;   break;
    case ActorType::ScienceFacility: command = 111;break;
    case ActorType::Factory:      command = 112;   break;
    default:
        break;
    }

    PK_Data data;
    data.ClientID = mActor->mID;
    data.input    = command;
    data.pos      = ax::Vec2(mActor->idx,0);
    TcpClient::get()->SendMessageToServer(data);
    mCurAction = ActionState::Building;
}
