#include "pch.h"
#include "MessageSystem.h"
#include "Actor.h"
#include "UILayer.h"
#include "UnitComp.h"
#include "CursorComp.h"
#include "Player.h"


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
    case MsgType::Do_Build:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    }
    case MsgType::BPCMC:
    {
        if (receiver->mCursorComp)
            receiver->mCursorComp->MessageProc(msg);
    }
    default:
        break;
    }
}

void SendSystemMessage(UILayer* ui, Player* player, SystemMessage smsg)
{
    if (smsg.Atype == ActorType::None && smsg.Btype != ButtonType::None)
    {
        // UI -> Player
        if (player)
            player->MessageProc(smsg);
    }
    else if (smsg.Btype == ButtonType::None && smsg.Atype != ActorType::None)
    {
        // Player ->UI
        if (ui)
            ui->MessageProc(smsg);
    }
}



