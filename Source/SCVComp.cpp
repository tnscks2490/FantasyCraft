#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "MessageSystem.h"
#include "TcpClient.h"
#include "Goal/Base/GoalComp.h"



SCVComp::SCVComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    
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
        mBuilding = msg.sender;
    default:
        break;
    }
}

void SCVComp::update(float delta) {

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

void SCVComp::Building(ActorMessage& msg)
{
    auto screen = mActor->GetRoot()->getParent();

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
