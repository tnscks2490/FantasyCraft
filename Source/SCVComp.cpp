#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "MessageSystem.h"
#include "TcpClient.h"
#include "Goal/Base/GoalComp.h"
#include "DrawComp.h"



SCVComp::SCVComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::SCV);
    mWireFrame = ax::Sprite::create("SCV.png"sv);
    mUnitName  = "Terran SCV";

}

SCVComp::~SCVComp() {}

void SCVComp::MessageProc(ActorMessage& msg)
{
   
    switch (msg.msgType)
    {
    case MsgType::Build:
    {
        ax::Vec2* pos = (ax::Vec2*)msg.data;
        AddGoal_MoveAndBuild(mActor, *pos, ActorType::CommandCenter);
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
        break;
    case MsgType::IsBuild_Complete:
    {
        if (mBuilding)
            AddGoal_DoingBuild(mActor, mBuilding);
    }break;

    case MsgType::Build_Continue:
    {
        Build_Continue(msg);
    }break;

    case MsgType::Cancel:
    {
        if (mBuilding)
        {
            AddGoal_AllCancel(mActor);
            ActorMessage msg = {MsgType::Build_Cancel, mActor, nullptr, nullptr};
            SendActorMessage(mBuilding, msg);
            mBuilding = nullptr;
        }
    }
    break;

    case MsgType::Attack:
    {
        int damage = msg.sender->mUnitComp->mStatus.AT - mStatus.DF;
        if (damage  <= 0 ) damage = 1;

        mStatus.HP -= damage;
        printf("남은 체력 : %d\n" ,mStatus.HP);

        SCVHpChange();
        mActor->mDrawComp->CreateDemageNode(msg.sender->mActorType);





        if (mActor->mUnitComp->mStatus.HP <= 0)
        {
            mCurAction = ActionState::Death;

        }
    }
    break;
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

}

void SCVComp::Repair()
{

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
    case ActorType::SupplyDpot:  command = 103;  break;
    default:
        break;
    }
    SendPK_Data(command, mActor->GetPosition());
    mCurAction = ActionState::Building;
}
