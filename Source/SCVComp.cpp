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
    ActorMessage Msg = msg;

    mBuilding = Msg.sender;

    ActorMessage tmsg;
    tmsg.data   = nullptr;
    tmsg.msgType = MsgType::Build;
    tmsg.sender  = mActor;
    SendActorMessage(mBuilding, tmsg);

    switch (msg.msgType)
    {
    case MsgType::Build:
       
    default:
        break;
    }
}

void SCVComp::update(float delta) {

}

void SCVComp::Repair()
{

}

void SCVComp::Building(ax::Vec2 pos)
{
    

}
