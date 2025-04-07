#include "pch.h"
#include "UI/CommandLayer.h"
#include "ButtonInfo.h"

bool CommandLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    setName("CommandLayer");

    ax::DrawNode* draw = ax::DrawNode::create();
    draw->drawRect(ax::Vec2(-128, -128), ax::Vec2(128, 128), ax::Color4B::RED);
    addChild(draw, 1);

    ax::DrawNode* dot = ax::DrawNode::create();
    dot->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::BLUE);
    addChild(dot, 1);



    mMenu = ax::Menu::create();
    addChild(mMenu, 1);

    ax::DrawNode* dot2 = ax::DrawNode::create();
    dot2->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::BLUE);
    mMenu->addChild(dot2, 1);

    

    return true;
}

void CommandLayer::MessageProc(SystemMessage smsg)
{
    auto msg = smsg;

    if (msg.smsgType == SMsgType::None)
        SetButton(msg.Atype);
}

void CommandLayer::ButtonMessage(ax::Object* sender)
{
    auto node        = (ax::Node*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();

    auto type = info->type;

    switch (type)
    {
        // 이레귤러
    case ButtonType::TCancel:
    {
        // mMenu->removeAllChildren();
        ReturnButton();
    }
    break;
        // 버튼 UI가 변경되지 않는 버튼들
    case ButtonType::THold:
    case ButtonType::TStop:
        break;
        // 버튼 UI가 Cancel 하나로 변경되는 버튼들
    case ButtonType::TAttack:
    case ButtonType::TMove:
    case ButtonType::TSetRellyPoint:
    case ButtonType::TUnLoad:
    case ButtonType::TLoad:
    case ButtonType::TPatrol:
    case ButtonType::TReturn:
    case ButtonType::TGather:
    case ButtonType::TRepair:
    {
        // mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);
    }
    break;
        // 다른 버튼 UI로 변경되는 버튼들
    case ButtonType::TCommon_Build:
    {
        // mMenu->removeAllChildren();

        SetCBButton();
    }
    break;

    case ButtonType::TAdvance_Build:
    {
        // mMenu->removeAllChildren();
        SetABButton();
    }
    break;

    case ButtonType::TLift:
    case ButtonType::TLand:
        break;
    case ButtonType::TCommand_Center:
    {
        // mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);
        // 만약 캔슬을 누르면 SCV에게 명령이 가도록 해야함
    }
    default:
        break;
    }

    // 어떤 버튼을 선택했는지 플레이어에게 보내준다
    /*SystemMessage smsg;
    smsg.Btype = type;
    SendSystemMessage(this, mPlayer, smsg);*/
}

void CommandLayer::SetButton(ActorType type)
{
    mCurActorType = type;
    ClearSaveButtons();
    SetUnitControlButton(type);
}

void CommandLayer::ReturnButton()
{
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        CreateAddButton(mSavebuttons[i]);
    }
}

void CommandLayer::ClearSaveButtons()
{
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        mSavebuttons[i] = ButtonType::None;
    }
}

void CommandLayer::SetUnitControlButton(ActorType Atype)
{
    auto ctrButtons = FindUnitControlButton(Atype);
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        CreateAddButton(ctrButtons->buttons[i]);
        mSavebuttons[i] = ctrButtons->buttons[i];
    }
}

void CommandLayer::SetCBButton()
{
    CreateAddButton(ButtonType::TCommand_Center);
    CreateAddButton(ButtonType::TSupply_Depot);
    CreateAddButton(ButtonType::TRefinery);
    CreateAddButton(ButtonType::TBarracks);
    CreateAddButton(ButtonType::TEngineering_Bay);
    CreateAddButton(ButtonType::TMissile_Turret);
    CreateAddButton(ButtonType::TAcademy);
    CreateAddButton(ButtonType::TBunker);
    CreateAddButton(ButtonType::TCancel);
}

void CommandLayer::SetABButton()
{
    CreateAddButton(ButtonType::TFactory);
    CreateAddButton(ButtonType::TStarPort);
    CreateAddButton(ButtonType::TScience_Facility);
    CreateAddButton(ButtonType::TArmory);
    CreateAddButton(ButtonType::TCancel);
}

ax::Vec2 CommandLayer::SetButtonPosition(int num)
{
    ax::Vec2 pos = ax::Vec2(0, 0);
    switch (num)
    {
    case 1: pos = ax::Vec2(-92, 80);      return pos;
    case 2: pos = ax::Vec2(0, 80);     return pos;
    case 3: pos = ax::Vec2(92, 80);    return pos;
    case 4: pos = ax::Vec2(-92, 0);    return pos;
    case 5: pos = ax::Vec2(0, 0);   return pos;
    case 6: pos = ax::Vec2(92, 0);  return pos;
    case 7: pos = ax::Vec2(-92, -80);   return pos;
    case 8: pos = ax::Vec2(0, -80);  return pos;
    case 9: pos = ax::Vec2(92, -80); return pos;
    default:
        printf("UI 오류입니다");
        break;
    }
    return pos;
}

ax::MenuItemImage* CommandLayer::CreateAddButton(ButtonType type)
{
    ButtonInfo* t = FindButtonInfo(type);

    auto bt = ax::MenuItemImage::create(t->normal_Image, t->selected_Image, AX_CALLBACK_1(CommandLayer::ButtonMessage, this));

    bt->setUserData(t);
    bt->setScale(2.f);
    bt->setPosition(SetButtonPosition(t->iconPos));

    mMenu->addChild(bt, 1);

    return bt;
}

