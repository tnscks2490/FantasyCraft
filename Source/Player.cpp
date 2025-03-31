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
    } break;

    case ButtonType::TCommand_Center:
    {
        // 건물 블루프린트 생성하기
        ActorMessage msg = {MsgType::BPCMC, nullptr, nullptr};
        SendActorMessage(cursor, msg);
    } break;


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
    PlayerActors.clear();
    if (mMainActor)
        mMainActor = nullptr;
}

void Player::Selected()
{
    for (auto aa : PrePlayerActors)
    {
        if (aa)
        {
            for (auto ac : PlayerActors)
            {
                if (ac == nullptr)
                {
                    ac                         = aa;
                    ac->mDrawComp->selected = true;
                    ac->mDrawComp->isSelected();
                    return;
                } 
            }
            aa->mDrawComp->selected = true;
            aa->mDrawComp->isSelected();
            PlayerActors.push_back(aa);
        }      
    }


    // 여기서 UI로 어떤 캐릭터가 선택됐는지 보내서 UI버튼 바꿔야함
    if (PlayerActors.size() == 1)
    {
        mMainActor = PlayerActors[0];
        SystemMessage smsg;
        smsg.Atype = mMainActor->mActorType;

        SendSystemMessage(ui, this, smsg);
    }
}

void Player::PreSelected(Actor* actor)
{
    for (auto ac : PrePlayerActors)
    {
        if (ac == nullptr)
        {
            ac = actor;
            return;
        }
    }
    PrePlayerActors.push_back(actor);
}

void Player::PreClear()
{
    for (auto ac : PrePlayerActors)
    {
        if (ac){ ac = nullptr;}
    }
    PlayerActors.clear();
}

bool Player::isSelected()
{
    if (PlayerActors.size() > 0)
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
    PrePlayerActors.clear();

    if (PlayerActors.size() == 0)
    {

    }
    else if (PlayerActors.size() > 0)
    {

    }
}

void Player::ButtonAction(ax::Object* sender)
{
    auto node        = (ax::MenuItemImage*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();
    printf("실행");
}
