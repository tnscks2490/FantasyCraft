#include "pch.h"
#include "UILayer.h"
#include "World.h"
#include "TcpClient.h"
#include "MessageSystem.h"
#include "ButtonInfo.h"
#include "Player.h"

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    

    SetUI(PlayerRace::Terran);
   /* mMenu->addChild(CreateButton(ButtonType::TMove));

    auto bt = CreateButton(ButtonType::TAttack);
    bt->setPosition(ax::Vec2(92, 0));
    auto stop = CreateButton(ButtonType::TStop);
    stop->setPosition(ax::Vec2(184, 0));

    auto tt = CreateButton(ButtonType::TArmory);
    tt->setPosition(ax::Vec2(0, -80));

    mMenu->addChild(tt, 1);
    mMenu->addChild(stop, 1);
    mMenu->addChild(bt,1);
    */
    

    return true;
}

void UILayer::MessageProc(SystemMessage smsg)
{
    printf("UI가 플레이어로부터 메세지를 수신받았습니다.");
    auto msg = smsg;
    SetButton(msg.Atype);
}



void UILayer::SetUI(PlayerRace race)
{
    mMenu = ax::Menu::create();
    mMenu->setPosition(ax::Vec2(408, -270));
    this->addChild(mMenu, 1);
    switch (race)
    {
    case PlayerRace::Terran:
    {
        mConsoleUI = ax::Sprite::create("TerranConsole.png"sv);
        addChild(mConsoleUI);

        mMineralIcon = ax::Sprite::create("MineralIcon.png"sv);
        mMineralIcon->setPosition(ax::Vec2(300 ,450));
        addChild(mMineralIcon);

        mGasIcon = ax::Sprite::create("TGasIcon.png"sv);
        mGasIcon->setPosition(ax::Vec2(400, 450));
        addChild(mGasIcon);

        mPopIcon = ax::Sprite::create("TPopIcon.png"sv);
        mPopIcon->setPosition(ax::Vec2(500, 450));
        addChild(mPopIcon);
    } break;

    case PlayerRace::Protoss:
    {
        mConsoleUI = ax::Sprite::create("ProtossConsole.png"sv);
        addChild(mConsoleUI);

        mMineralIcon = ax::Sprite::create("MineralIcon.png"sv);
        addChild(mMineralIcon);

        mGasIcon = ax::Sprite::create("PGasIcon.png"sv);
        addChild(mGasIcon);

        mPopIcon = ax::Sprite::create("PPopIcon.png"sv);
        addChild(mPopIcon);

    } break;

    case PlayerRace::Zerg:
    {
        mConsoleUI = ax::Sprite::create("ZergConsole.png"sv);
        addChild(mConsoleUI);

        mMineralIcon = ax::Sprite::create("MineralIcon.png"sv);
        addChild(mMineralIcon);

        mGasIcon = ax::Sprite::create("ZGasIcon.png"sv);
        addChild(mGasIcon);

        mPopIcon = ax::Sprite::create("ZPopIcon.png"sv);
        addChild(mPopIcon);
    } break;

    default:
        AXLOG("종족을 선택하지 않았습니다. 종족을 선택하여 주십시오.");
        break;
    }
    setPosition(ax::Vec2(640, 480));
}

void UILayer::SetBuildButton() {}


void UILayer::SetCancelButton()
{
    auto CB = CreateButton(ButtonType::TCancel);
    // 칸당 가로는 92 세로는 80픽셀이 엇비슷하게 맞음
    CB->setPosition(ax::Vec2(184, -160));

    mMenu->addChild(CB, 1);
}


void UILayer::ButtonMessage(ax::Object* sender)
{
    auto node        = (ax::Node*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();

    auto type = info->type;
    if (type == ButtonType::TCommon_Build || type == ButtonType::TAdvance_Build)
    {
        SetBuildButton();
    }
    else if (type == ButtonType::TCancel)
    {
        mMenu->removeAllChildren();
        ReturnButton();
    }
    else
    {
        SetCancelButton();
    }







    SystemMessage smsg;
    smsg.Btype = type;

    SendSystemMessage(this, mPlayer, smsg);

}

void UILayer::SetButton(ActorType type)
{
    switch (type)
    {
    case ActorType::SCV:
    {
        SetSCVButton();
    }
        break;
    case ActorType::Marine:
        break;
    default:
        break;
    }
}

void UILayer::ReturnButton()
{
    for (auto bt : buttons)
    {
        if (bt != ButtonType::None)
        {
            auto button = CreateButton(bt);

        }
    }
}

void UILayer::SetSCVButton()
{
    auto move = CreateButton(ButtonType::TMove);
    mMenu->addChild(move,1);
    buttons[0] = ButtonType::TMove;

    auto stop = CreateButton(ButtonType::TStop);
    mMenu->addChild(stop, 1);
    buttons[1] = ButtonType::TStop;

    auto attack = CreateButton(ButtonType::TAttack);
    mMenu->addChild(attack, 1);
    buttons[2] = ButtonType::TAttack;

    auto repair = CreateButton(ButtonType::TRepair);
    mMenu->addChild(repair, 1);
    buttons[3] = ButtonType::TRepair;

    auto gather = CreateButton(ButtonType::TGather);
    mMenu->addChild(gather, 1);
    buttons[4] = ButtonType::TGather;

    buttons[5] = ButtonType::None;

    auto cbuild = CreateButton(ButtonType::TCommon_Build);
    mMenu->addChild(cbuild, 1);
    buttons[6] = ButtonType::TCommon_Build;

    auto abuild = CreateButton(ButtonType::TAdvance_Build);
    mMenu->addChild(abuild, 1);
    buttons[7] = ButtonType::TAdvance_Build;

    buttons[8] = ButtonType::None;
}

ax::Vec2 UILayer::SetButtonPosition(int num)
{
    ax::Vec2 pos = ax::Vec2(0,0);
    switch (num)
    {
    case 1: pos = ax::Vec2(0, 0);     return pos;
    case 2: pos = ax::Vec2(92,0);     return pos;
    case 3: pos = ax::Vec2(184,0);    return pos;
    case 4: pos = ax::Vec2(0,-80);    return pos;
    case 5: pos = ax::Vec2(92,-80);   return pos;
    case 6: pos = ax::Vec2(184,-80);  return pos;
    case 7: pos = ax::Vec2(0,-160);   return pos;
    case 8: pos = ax::Vec2(92,-160);  return pos;
    case 9: pos = ax::Vec2(184,-160); return pos;
    default:
        printf("UI 오류입니다");
        break;
    }
    return pos;
}

ax::MenuItemImage* UILayer::CreateButton(ButtonType type)
{
    ButtonInfo* t = FindButtonInfo(type);

    auto bt = ax::MenuItemImage::create(t->normal_Image, t->selected_Image, AX_CALLBACK_1(UILayer::ButtonMessage, this));

    bt->setUserData(t);
    bt->setScale(2.f);
    bt->setPosition(SetButtonPosition(t->iconPos));

    return bt;
}
