#include "pch.h"
#include "ActorMessage.h"
#include "Actor.h"


void SendActorMessage(Actor* receiver, ActorMessage msg)
{
    switch (msg.msgType)
    {
    case ActorMessage::Build:
        if (receiver->mUnitComp) 
        break;
    default:
        break;
    }
}
