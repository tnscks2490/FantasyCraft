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
    ax::Vec2* pos = (ax::Vec2*)msg.data;


    switch (msg.msgType)
    {
    case MsgType::Build:
        AddGoal_MoveAndBuild(mActor, *pos, ActorType::CommandCenter);
        break;
    case MsgType::Do_Build:
        Building(msg);
        break;
    default:
        break;
    }
}

void SCVComp::update(float delta) {

    mTimer += delta;

    if (mTimer > 5.f)
    {
        auto t =  mActor->GetRoot()->getChildByName("EffectNode");
        printf("자식확인하기");
        mTimer = 0.f;
    }
}

void SCVComp::Repair()
{

}

void SCVComp::Building(ActorMessage& msg)
{
    auto screen = mActor->GetRoot()->getParent();

    PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = 102;
    data.pos      = mActor->GetPosition();
    TcpClient::get()->SendMessageToServer(data);

    /*ActorMessage rmsg;
    rmsg.sender = mActor;
    rmsg.data   = nullptr;
    rmsg.msgType = MsgType::Build;
    SendActorMessage(CC, rmsg);*/

    mCurAction = ActionState::Building;
}
