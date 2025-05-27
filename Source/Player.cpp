#include "pch.h"
#include "Player.h"
#include "Actor.h"
#include "DrawComp.h"
#include "SelectManager.h"
#include "PlayerEventSystem.h"
#include "CursorComp.h"

Player::Player()
{
    mSM = new SelectManager(this);

    RegistePlayer(this);
}

Player::~Player() {}

void Player::MessageProc(SystemMessage smsg)
{
    auto msg = smsg;

    switch (msg.smsgType)
    {
    case SMsgType::None:
    {
        switch (smsg.Btype)
        {
        case ButtonType::TGather:
        {
            cursor->mCursorComp->mState = CursorState::Target;
        }
        break;
        case ButtonType::TAttack:
            cursor->mCursorComp->mState = CursorState::SetAttackTarget;
            break;

        case ButtonType::TMove:
            cursor->mCursorComp->mState = CursorState::Target;
            break;

        case ButtonType::TCancel:
        {
            cursor->mCursorComp->mState = CursorState::Idle;
            ActorMessage msg            = {MsgType::Cancel, mMainActor, nullptr, nullptr};
            SendActorMessage(mMainActor, msg);
        }
        break;

        case ButtonType::TCommand_Center:
        {
            // 건물 블루프린트 생성하기
            auto type        = ActorType::CommandCenter;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        } break;
        case ButtonType::TBarracks:
        {
            auto type        = ActorType::Barrack;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TAcademy:
        {
            auto type        = ActorType::Academy;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TArmory:
        {
            auto type        = ActorType::Armory;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TBunker:
        {
            auto type        = ActorType::Bunker;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TEngineering_Bay:
        {
            auto type        = ActorType::EngineeringBay;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TSupply_Depot:
        {
            auto type        = ActorType::SupplyDepot;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TFactory:
        {
            auto type        = ActorType::Factory;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TRefinery:
        {
            auto type        = ActorType::Refinery;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TScience_Facility:
        {
            auto type        = ActorType::ScienceFacility;
            ActorMessage msg = {MsgType::CreateBP, nullptr, nullptr, &type};
            SendActorMessage(cursor, msg);
        }
        break;
        case ButtonType::TSCV:
        {
            if (mMainActor && mMainActor->mActorType == ActorType::CommandCenter)
            {
                ActorMessage msg = {MsgType::Create_SCV, nullptr, nullptr};
                SendActorMessage(mMainActor, msg);

                SystemMessage smsg = {SMsgType::Create_Unit, ReceiverType::UI, ActorType::SCV, ButtonType::TSCV, nullptr};
                SendSystemMessage(ui, this, smsg);
               
            }
        } break;
        case ButtonType::TMarine:
        {
            if (mMainActor && mMainActor->mActorType == ActorType::Barrack)
            {
                ActorMessage msg = {MsgType::Create_Marine, nullptr, nullptr};
                SendActorMessage(mMainActor, msg);

                SystemMessage smsg = {SMsgType::Create_Unit, ReceiverType::UI, ActorType::Marine, ButtonType::TMarine, nullptr};
                SendSystemMessage(ui, this, smsg);
            }
        }

        default:
            break;
        }
    }
    break;
    case SMsgType::Upgrade:
    {
        switch (smsg.Btype)
        {
        case ButtonType::TBionic_AT:
        {
            if (mMainActor && mMainActor->mActorType == ActorType::EngineeringBay)
            {
                ActorMessage msg = {MsgType::Upgrade_Bionic_AT, nullptr, nullptr};
                SendActorMessage(mMainActor, msg);

                SystemMessage smsg = {SMsgType::Upgrade, ReceiverType::UI, ActorType::EngineeringBay, ButtonType::TBionic_AT, nullptr};
                SendSystemMessage(ui, this, smsg);
            }
        } break;
        case ButtonType::TBionic_DF:
        {
            if (mMainActor && mMainActor->mActorType == ActorType::EngineeringBay)
            {
                ActorMessage msg = {MsgType::Upgrade_Bionic_DF, nullptr, nullptr};
                SendActorMessage(mMainActor, msg);

                SystemMessage smsg = {SMsgType::Upgrade, ReceiverType::UI, ActorType::EngineeringBay, ButtonType::TBionic_DF, nullptr};
                SendSystemMessage(ui, this, smsg);
            }
        }
        default:
            break;
        }
    }
    case SMsgType::MSUI:
    {
    }
    break;
    case SMsgType::Cancel:
    {
        ActorMessage msg = {MsgType::Cancel, nullptr, nullptr};
        SendActorMessage(mMainActor, msg);

        SystemMessage smsg = {SMsgType::Cancel, ReceiverType::UI,
                              ActorType::None, ButtonType::None, mMainActor};
        SendSystemMessage(ui, this, smsg);
    }
    default:
        break;
    }

    

    printf("Player가 UI로부터 메세지를 수신받았습니다");
}

void Player::EvnetProc(PEvent evnet)
{
    auto e = evnet;
    switch (e.EType)
    {
    case EventType::GetResource:
    {
        GetResource(e.Mineral, e.Gas);
        SystemMessage smsg = {SMsgType::ChangeResource, ReceiverType::UI, ActorType::None, ButtonType::None, nullptr};
        SendSystemMessage(ui, this, smsg);
    }
    break;
    default:
        break;
    }
}

void Player::Clear()
{
    for (auto ac : PlayerActors)
    {
        if (ac && !ac->isDead )
        {
            ac->mDrawComp->selected = false;         
            ac->mDrawComp->isSelected();
            ac = nullptr;
        }
    }
    PlayerActorsClear();
    if (mMainActor)
        mMainActor = nullptr;
}

void Player::Selected()
{
    for (int i = 0; i < 12; i++)
    {
        if (PrePlayerActors[i] == nullptr)
            continue;
        else
        {
            PlayerActors[i] = PrePlayerActors[i];
            PlayerActors[i]->mDrawComp->selected = true;
            PlayerActors[i]->mDrawComp->isSelected();
        }
    }

}

void Player::ClassifySelected()
{
    // 조건 1 모두 확인후 건물이 있는지 없는지 판별한다.
    // 조건 2 건물이 있는경우 제외하고 유닛만 선별한다.
    // 조건 3 건물만 있는 경우 무조건 싱글 선택이다.
    // 
    // 조건 4 상대 유닛과 내 유닛이 같이 선택된 경우 상대 유닛은 무시한다(나중에 구현하기)

    bool isFriendUnit = false;
    bool isBuilding = false;
    bool isEnemyUnit  = false;


    for (auto ac : PrePlayerActors)
    {
        if (ac)
        {
            if (ac->mCategory == UnitCategory::Unit)
            {
                isFriendUnit = true;
            }
            else if (ac->mCategory == UnitCategory::Building)
            {
                isBuilding = true;
            }
        }
    }



    // 아군 유닛만 선택한 경우
    if (isFriendUnit == true && isBuilding == false)
    {
        // 건드릴게 없지만 확인용
    }
    // 아군 건물만 선택한 경우
    else if (isFriendUnit == false && isBuilding == true)
    {
        auto ac = PrePlayerActors[0];
        PrePlayerActorsClear();
        PrePlayerActors[0] = ac;
    }
    // 아군 유닛과 건물을 모두 선택한 경우
    else if (isFriendUnit == true && isBuilding == true)
    {
        for (int i = 0; i < 12; i++)
        {
            if (PrePlayerActors[i] == nullptr)
                break;
            if (PrePlayerActors[i]->mCategory == UnitCategory::Building)
            {
                PrePlayerActors[i] = nullptr;
            }
        }
        int idx = -1;

        for (int i = 0; i < 12; i++)
        {
            if (PrePlayerActors[i] == nullptr)
                idx = i;

            if (idx != -1)
            {
                PrePlayerActors[idx] = PrePlayerActors[i];
                PrePlayerActors[i]   = nullptr;
                idx                   = -1;
            }
        }

    }

    
}

void Player::PreSelected(Actor* actor)
{
    for (int i = 0; i < 12; i++)
    {
        if (PrePlayerActors[i] == nullptr)
        {
            PrePlayerActors[i] = actor;
            return;
        }
    }
}

void Player::PreClear()
{
    for (auto ac : PrePlayerActors)
    {
        if (ac){ ac = nullptr;}
    }
    PlayerActorsClear();
}

bool Player::isSelected()
{
    if (PlayerActorsNum() > 0)
        return true;
    else
        return false;
}

void Player::PrintSelectActors()
{
    int i = 0;
    for (auto ac : PlayerActors)
    {
        if (ac)
        {
            i++;
        }
    }

    printf("현재 선택된 엑터의 수 : %d \n", i);
}

void Player::ReSelected()
{
    Clear();
    ClassifySelected();
    Selected();
    PrePlayerActorsClear();

    if (PlayerActorsNum() == 1)
    {
        // 여기서 UI로 어떤 캐릭터가 선택됐는지 보내서 UI버튼 바꿔야함

        for (auto ac : PlayerActors)
        {
            if (ac)
            {
                mMainActor = ac;
                break;
            }
        }
        SystemMessage ssmsg = {SMsgType::SSUI, ReceiverType::UI,ActorType::None, ButtonType::None, mMainActor};
        SendSystemMessage(ui, this, ssmsg);
    }
    else if (PlayerActorsNum() > 1)
    {
        SystemMessage smsg = {SMsgType::MSUI, ReceiverType::UI,ActorType::None, ButtonType::None, PlayerActors};

        SendSystemMessage(ui, this, smsg);
    }
}

int Player::PlayerActorsNum()
{
    int num = 0;
    for (int i = 0; i < 12; i++)
    {
        if (PlayerActors[i] != nullptr)
            num++;
    }
    return num;
}

int Player::PrePlayerActorsNum()
{
    int num = 0;
    for (int i = 0; i < 12; i++)
    {
        if (PrePlayerActors[i] != nullptr)
            num++;
    }
    return num;
}

void Player::PlayerActorsClear()
{
    for (int i = 0; i < 12; i++)
    {
        PlayerActors[i] = nullptr;
    }
}

void Player::PrePlayerActorsClear()
{
    for (int i = 0; i < 12; i++)
    {
        PrePlayerActors[i] = nullptr;
    }
}

void Player::ButtonAction(ax::Object* sender)
{
    auto node        = (ax::MenuItemImage*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();
    printf("실행");
}

bool Player::UseResource(int m, int g)
{
    if ((mMineral - m) < 0 || mGas - g < 0)
        return false;

    return true;
}

