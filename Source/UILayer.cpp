#include "pch.h"
#include "UILayer.h"
#include "World.h"
#include "TcpClient.h"
#include "ActorMessage.h"

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }



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


        auto before = ax::Sprite::create("Attack_Release.png"sv);
        auto after  = ax::Sprite::create("Attack_Down.png"sv);

        auto item = ax::MenuItemImage::create("Attack_Release.png", "Attack_Down.png", AX_CALLBACK_0(UILayer::build, this));

        item->setScale(2.0f);
        item->setPosition(ax::Vec2(410,-270));

        auto menu = ax::Menu::create(item, NULL);
        menu->setPosition(ax::Vec2::ZERO);
        this->addChild(menu, 1);



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
    ActorMessage msg;
    msg.msgType = MsgType::Build;
    msg.data = nullptr;
    msg.sender  = nullptr;

    /*PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = 10;
    data.pos      = ax::Vec2::ZERO;
    TcpClient::get()->SendMessageToServer(data);*/
}
