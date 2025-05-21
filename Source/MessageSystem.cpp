#include "pch.h"
#include "MessageSystem.h"
#include "Actor.h"
#include "UI/UILayer.h"
#include "UnitComp.h"
#include "SensorComp.h"
#include "CursorComp.h"
#include "BPComp.h"
#include "DrawComp.h"
#include "Player.h"


void SendActorMessage(Actor* receiver, ActorMessage msg)
{
    if (receiver == nullptr)
        return;
    if (receiver->isDead)
        return;
    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        if (receiver->mCursorComp)  receiver->mCursorComp->MessageProc(msg);
        if (receiver->mSensorComp)  receiver->mSensorComp->MessageProc(msg);
        if (receiver->mUnitComp)    receiver->mUnitComp->MessageProc(msg);
        if (receiver->mBPComp)      receiver->mBPComp->MessageProc(msg);
        if (receiver->mDrawComp)    receiver->mDrawComp->MessageProc(msg);
    } break;
    case MsgType::Separate:
    {
        if (receiver->mCursorComp)  receiver->mCursorComp->MessageProc(msg);
        if (receiver->mSensorComp)  receiver->mSensorComp->MessageProc(msg);
        if (receiver->mUnitComp)    receiver->mUnitComp->MessageProc(msg);
        if (receiver->mBPComp)      receiver->mBPComp->MessageProc(msg);
        if (receiver->mDrawComp)    receiver->mDrawComp->MessageProc(msg);
    } break;
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

    case MsgType::CreateBP:
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

    case MsgType::Build_GetBuilder:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    } break;

    case MsgType::Build_Continue:
    {
        if (receiver->mUnitComp)
        {
            receiver->mUnitComp->MessageProc(msg);
        }
    } break;

    case MsgType::Build_Start:
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

    case MsgType::Attack:
    {
        if (receiver->mUnitComp) receiver->mUnitComp->MessageProc(msg);
        
    } break;

    case MsgType::SetTarget:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    break;

    case MsgType::Create_SCV:
    case MsgType::Create_Marine:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    } break;
    case MsgType::Upgrade_Bionic_AT:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    } break;
    case MsgType::Upgrade_Bionic_DF:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    } break;
    case MsgType::Gathering:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    break;

    case MsgType::GatherMineral:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    break;

    case MsgType::GatherGas:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }break;

    case MsgType::GiveMineral:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    } break;
    case MsgType::ReturnCargo:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    break;
    case MsgType::SetAttackTarget:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    break;
    case MsgType::AttackTarget:
    {
        if (receiver->mUnitComp)
            receiver->mUnitComp->MessageProc(msg);
    }
    default:
        break;
    }
}

void SendSystemMessage(UILayer* ui, Player* player, SystemMessage smsg)
{

    switch (smsg.smsgType)
    {
    case SMsgType::None:
    {
        if (smsg.recvType == ReceiverType::Player)
        {
            // UI -> Player
            if (player)
                player->MessageProc(smsg);
        }
        else if (smsg.recvType == ReceiverType::UI)
        {
            // Player->UI
            if (ui)
                ui->MessageProc(smsg);
        }
    }
    break;
    case SMsgType::Cancel:
    {
        if (smsg.recvType == ReceiverType::Player)
        {
            // UI -> Player
            if (player)
                player->MessageProc(smsg);
        }
        else if (smsg.recvType == ReceiverType::UI)
        {
            // Player->UI
            if (ui)
                ui->MessageProc(smsg);
        }
    }
    break;
    case SMsgType::BPCancel:
    {
        if (smsg.recvType == ReceiverType::Player)
        {
            // UI -> Player
            if (player)
                player->MessageProc(smsg);
        }
        else if (smsg.recvType == ReceiverType::UI)
        {
            // Player->UI
            if (ui)
                ui->MessageProc(smsg);
        }
    }
    case SMsgType::MSUI:
    {
        if (ui) ui->MessageProc(smsg);
    }
        break;
    case SMsgType::SSUI:
    {
        if (ui) ui->MessageProc(smsg);
    } break;
    case SMsgType::Create_Unit:
    {
        if (player)
            player->MessageProc(smsg);
        if (ui)
            ui->MessageProc(smsg);
    } break;
    case SMsgType::Upgrade:  
        if (smsg.recvType == ReceiverType::Player)
        {
            // UI -> Player
            if (player)
                player->MessageProc(smsg);
        }
        else if (smsg.recvType == ReceiverType::UI)
        {
            // Player->UI
            if (ui)
                ui->MessageProc(smsg);
        }
    default:
        break;
    }
    
}





