#include "pch.h"
#include "Player.h"
#include "Actor.h"
#include "DrawComp.h"
#include "PlayerController.h"
#include "CursorComp.h"

Player::Player()
{
    mPC = new PlayerController(this);

    
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
        case ButtonType::TAttack:
            cursor->mCursorComp->mState = CursorState::Target;
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
        case ButtonType::TSCV:
        {
            if (mMainActor && mMainActor->mActorType == ActorType::CommandCenter)
            {
                ActorMessage msg = {MsgType::Create_SCV, nullptr, nullptr};
                SendActorMessage(mMainActor, msg);

                SystemMessage smsg = {SMsgType::Create_Unit, ActorType::SCV, ButtonType::TSCV, nullptr};
                SendSystemMessage(ui, this, smsg);
               
            }
        }

        default:
            break;
        }
    }
    break;
    case SMsgType::MSUI:
    {

    }
    default:
        break;
    }

    

    printf("Player가 UI로부터 메세지를 수신받았습니다");
}

void Player::Clear()
{
    for (auto ac : PlayerActors)
    {
        if (ac)
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
            break;
        else
        {
            PlayerActors[i] = PrePlayerActors[i];
            PlayerActors[i]->mDrawComp->selected = true;
            PlayerActors[i]->mDrawComp->isSelected();
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
    Selected();
    PrePlayerActorsClear();

    if (PlayerActorsNum() == 1)
    {
        // 여기서 UI로 어떤 캐릭터가 선택됐는지 보내서 UI버튼 바꿔야함
        mMainActor = PlayerActors[0];
        /*SystemMessage smsg;
        smsg.Atype = mMainActor->mActorType;
        SendSystemMessage(ui, this, smsg);*/
        ///// 단일 선택에 관한 와이어프레임 UI출력하는 함수 추가할것

        SystemMessage ssmsg = {SMsgType::SSUI, ActorType::None, ButtonType::None, mMainActor};
        SendSystemMessage(ui, this, ssmsg);
    }
    else if (PlayerActorsNum() > 1)
    {
        SystemMessage smsg = {SMsgType::MSUI, ActorType::None, ButtonType::None, PlayerActors};

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
