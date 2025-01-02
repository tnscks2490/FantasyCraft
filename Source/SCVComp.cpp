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


    switch (msg.msgType)
    {
    case MsgType::Build:
        printf("설치");
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
    PK_Data data;
    data.ClientID = mActor->mID;
    data.input    = 10;
    data.pos      = pos;
    TcpClient::get()->SendMessageToServer(data);
}
