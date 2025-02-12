#include "pch.h"
#include "UILayer.h"
#include "World.h"
#include "TcpClient.h"
#include "ActorMessage.h"
#include "ButtonInfo.h"
#include "Player.h"

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }


    CreateButton();
    return true;
}

void UILayer::SetUI(PlayerRace race)
{

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

void UILayer::build()
{
    /*ActorMessage msg = {MsgType::BPCMC, nullptr, nullptr};
    SendActorMessage(mCursor, msg);*/



}

void UILayer::ButtonMessage(ax::Object* sender)
{
    auto node = (ax::Node*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();

    if (mPlayer)
    {
        mPlayer->ButtonAction(info);
    }

}

void UILayer::CreateButton()
{
    ButtonInfo* t = FindButtonInfo(ButtonType::TMove);
    auto bt1 = ax::MenuItemImage::create(t->normal_Image, t->selected_Image, AX_CALLBACK_1(UILayer::ButtonMessage, this));
    bt1->setUserData(t);
    bt1->setScale(2.f);
    bt1->setPosition(ax::Vec2(0, 0));

    auto menu = ax::Menu::create(bt1, NULL);
    menu->setPosition(ax::Vec2::ZERO);
    this->addChild(menu, 1);
}
