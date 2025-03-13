#include "pch.h"
#include "MessageSystem.h"
#include "Actor.h"
#include "UILayer.h"
#include "UnitComp.h"
#include "CursorComp.h"
#include "BPComp.h"
#include "DrawComp.h"
#include "Player.h"


void SendActorMessage(Actor* receiver, ActorMessage msg)
{
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        if (receiver->mCursorComp)  receiver->mCursorComp->MessageProc(msg);
        if (receiver->mUnitComp)    receiver->mUnitComp->MessageProc(msg);
        if (receiver->mBPComp)      receiver->mBPComp->MessageProc(msg);
        if (receiver->mDrawComp)    receiver->mDrawComp->MessageProc(msg);
    }
    case MsgType::Separate:
    {
        if (receiver->mCursorComp)  receiver->mCursorComp->MessageProc(msg);
        if (receiver->mUnitComp)    receiver->mUnitComp->MessageProc(msg);
        if (receiver->mBPComp)      receiver->mBPComp->MessageProc(msg);
        if (receiver->mDrawComp)    receiver->mDrawComp->MessageProc(msg);
    }
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
    }break;

    case MsgType::BPCMC:
    {
        if (receiver->mCursorComp)
            receiver->mCursorComp->MessageProc(msg);
    }break;

    case MsgType::SendInfo:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    }break;

    case MsgType::Build_Complete:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    }break;

    case MsgType::IsBuild_Complete:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    }break;

    case MsgType::Cancel:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    } break;

    case MsgType::Build_Cancel:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    }break;

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



