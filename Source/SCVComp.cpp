#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "MessageSystem.h"
#include "TcpClient.h"



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
        Building(msg);
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

    ax::Vec2* pos = (ax::Vec2*)msg.data;

    Actor* CC = SpawnCommandCenter(screen);
    CC->SetPosition(*pos);
}
