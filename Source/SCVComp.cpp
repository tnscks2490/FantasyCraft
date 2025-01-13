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


    PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = 77;
    data.pos      = screen->getPosition();


    Actor* CC = SpawnCommandCenter(screen, data);
    ax::Vec2 Pos;
    Pos = data.pos - screen->getPosition();
    CC->SetPosition(Pos);

}
