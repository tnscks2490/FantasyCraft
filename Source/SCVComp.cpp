#include "pch.h"
#include "Actor.h"
#include "SCVComp.h"
#include "World.h"
#include "ActorMessage.h"
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
