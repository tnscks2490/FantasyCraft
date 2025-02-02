#include "pch.h"
#include "ActorMessage.h"
#include "Actor.h"
#include "UnitComp.h"
#include "CursorComp.h"


void SendActorMessage(Actor* receiver, ActorMessage msg)
{
    switch (msg.msgType)
    {
    case MsgType::Build:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    } break;
    case MsgType::BPCMC:
    {
        if (receiver->mCursorComp)
            receiver->mCursorComp->MessageProc(msg);
    }
    default:
        break;
    }
}
