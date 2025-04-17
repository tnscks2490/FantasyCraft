#include "pch.h"
#include "UI/UILayer.h"
#include "World.h"
#include "TcpClient.h"
#include "MessageSystem.h"
#include "ButtonInfo.h"
#include "Player.h"
#include "UnitComp.h"

#include "UI/UnitInfoLayer.h"
#include "UI/ResourceLayer.h"
#include "UI/MiniMapLayer.h"
#include "UI/CommandLayer.h"


bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    BottomUI = ax::Node::create();
    BottomUI->setPosition(ax::Vec2(0, -380));
    addChild(BottomUI,2);

    auto drawrect = ax::DrawNode::create();
    drawrect->drawRect(ax::Vec2(-300, -80), ax::Vec2(300, 80), ax::Color4B::RED);
    BottomUI->addChild(drawrect,10);


    auto unitinfo = UnitInfoLayer::create();
    unitinfo->setName("UnitInfoLayer");
    unitinfo->setPosition(ax::Vec2(0, -380));
    unitinfo->setAnchorPoint(ax::Vec2(0.5f, 0.5f));
    addChild(unitinfo, 1);

    auto command = CommandLayer::create();
    command->setName("CommandLayer");
    command->setPosition(ax::Vec2(500, -350));
    addChild(command, 1);

    auto minimap = MiniMapLayer::create();
    minimap->setName("MiniMapLayer");
    addChild(minimap, 1);

    auto resource = ResourceLayer::create();
    resource->setName("ResourceLayer");
    resource->setPosition(ax::Vec2(400, 450));
    addChild(resource, 1);

    printf("현재 자식 노드 확인하는 줄");


    return true;
}

void UILayer::MessageProc(SystemMessage smsg)
{
    printf("UI가 플레이어로부터 메세지를 수신받았습니다.");
    auto msg = smsg;

    

    switch (msg.smsgType)
    {
    case SMsgType::None:
    {
        /*CommandLayer* command = (CommandLayer*)this->getChildByName("CommandLayer");
        command->SetButton(msg.Atype);*/
    } break;
    case SMsgType::MSUI:
    {
        UnitInfoLayer* UnitInfo = (UnitInfoLayer*)this->getChildByName("UnitInfoLayer");
        UnitInfo->MessageProc(msg);
    }
        break;
    case SMsgType::SSUI:
    {
        UnitInfoLayer* UnitInfo = (UnitInfoLayer*)this->getChildByName("UnitInfoLayer");
        UnitInfo->MessageProc(msg);

        CommandLayer* command = (CommandLayer*)this->getChildByName("CommandLayer");
        command->MessageProc(msg);

    } break;
    case SMsgType::Create_Unit:
    {
        UnitInfoLayer* UnitInfo = (UnitInfoLayer*)this->getChildByName("UnitInfoLayer");
        UnitInfo->MessageProc(msg);
    }
    break;
    default:
        break;
    } 
}

void UILayer::StartSettingWithPlayer(Player* player)
{
    mPlayer = player;
    SetUI();

    ResourceLayer* resource = (ResourceLayer*)this->getChildByName("ResourceLayer");
    resource->mPlayer       = player;
    resource->SetNumText();

}



void UILayer::SetUI()
{


    switch (mPlayer->mRace)
    {
    case PlayerRace::Terran:
    {
        mConsoleImage = ax::Sprite::create("TerranConsole.png"sv);
        addChild(mConsoleImage);
    } break;

    case PlayerRace::Protoss:
    {
        mConsoleImage = ax::Sprite::create("ProtossConsole.png"sv);
        addChild(mConsoleImage);
    } break;
    case PlayerRace::Zerg:
    {
        mConsoleImage = ax::Sprite::create("ZergConsole.png"sv);
        addChild(mConsoleImage);
    } break;

    default:
        AXLOG("종족을 선택하지 않았습니다. 종족을 선택하여 주십시오.");
        break;
    }
    setPosition(ax::Vec2(640, 480));
}
