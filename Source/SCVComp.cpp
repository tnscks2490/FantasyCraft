#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "MessageSystem.h"
#include "TcpClient.h"
#include "BPComp.h"
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
    case MsgType::Build:
    {
        ax::Vec2* pos = (ax::Vec2*)msg.data;
        AddGoal_MoveAndBuild(mActor, *pos, msg.sender->mBPComp->mBPType);
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
            auto mMineral = msg.sender;
            AddGoal_MoveAndGathering(mMineral);
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
    } break;
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

void SCVComp::Gathering(Actor* mineral)
{
    mMineral = mineral;
    //mCurAction = ActionState::Gathering;
    //cmdLocked        = true;
    ActorMessage msg = {MsgType::Gathering,mActor,nullptr,nullptr};
    SendActorMessage(mMineral, msg);

    //이미지 바뀌는거까지 넣어야지
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

        break;
    default:
        break;
    }
    SendPK_Data(command, mActor->GetPosition());
    mCurAction = ActionState::Building;
}
