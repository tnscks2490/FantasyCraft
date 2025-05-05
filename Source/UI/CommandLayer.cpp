#include "pch.h"
#include "UI/CommandLayer.h"
#include "UI/UILayer.h"
#include "UI/UnitInfoLayer.h"
#include "ButtonInfo.h"
#include "Player.h"

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
    mMenu->setPosition(ax::Vec2::ZERO);
    addChild(mMenu, 1);

    scheduleUpdate();

    return true;
}

void CommandLayer::update(float delta)
{
    if (mActor)
    {
        if (mActor->mUnitComp->IsCmdLocked())
        {
            if (mCurState == CommandState::Idle)
            {
                ChangeCmdState(CommandState::CmdLock);
            }
        }
        else
        {
            if (mCurState == CommandState::CmdLock)
            {
                ChangeCmdState(CommandState::Idle);
            }
        }
    }
}

void CommandLayer::MessageProc(SystemMessage smsg)
{
    auto msg = smsg;
    switch (msg.smsgType)
    {
    case SMsgType::SSUI:
    {
        SingleSelected(msg);
    }
    break;
    case SMsgType::MSUI:
    {
        MultiSelected(msg);
    }
    break;
    case SMsgType::Cancel:
    {
        mActor = (Actor*)msg.data;
        SetButton(mActor);
    }
    break;
    case SMsgType::BPCancel:
    {
        SetButton(mActor);
    }
    default:
        break;
    }

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

        UILayer* ui        = (UILayer*)this->getParent();
        SystemMessage smsg = {SMsgType::Cancel, ReceiverType::Player, ActorType::None, type, nullptr};
        SendSystemMessage(ui, ui->mPlayer, smsg);
        return;
    } break;
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
        ChangeCmdState(CommandState::CmdLock);
    }
    break;
        // 다른 버튼 UI로 변경되는 버튼들
    case ButtonType::TCommon_Build:
    {
        mMenu->removeAllChildren();
        SetCBButton();
    }
    break;

    case ButtonType::TAdvance_Build:
    {
        mMenu->removeAllChildren();
        SetABButton();
    }
    break;

    case ButtonType::TLift:
    case ButtonType::TLand:
        break;
    case ButtonType::TAcademy:
    case ButtonType::TArmory:
    case ButtonType::TBarracks:
    case ButtonType::TBunker:
    case ButtonType::TCommand_Center:
    case ButtonType::TComsat_Station:
    case ButtonType::TControl_Tower:
    case ButtonType::TCovert_Ops:
    case ButtonType::TEngineering_Bay:
    case ButtonType::TFactory:
    case ButtonType::TMachine_Shop:
    case ButtonType::TMissile_Turret:
    case ButtonType::TNuclear_Silo:
    case ButtonType::TRefinery:
    case ButtonType::TPhysics_Lab:
    case ButtonType::TSupply_Depot:
    case ButtonType::TScience_Facility:
    {
        mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);

        UILayer* ui        = (UILayer*)this->getParent();
        SystemMessage smsg = {SMsgType::None, ReceiverType::Player, ActorType::None, type, nullptr};
        SendSystemMessage(ui, ui->mPlayer, smsg);
        return;
    }
    //여기 부터는 업그레이드를 누르면 커멘드레이어의 반영되는 부분들
    case ButtonType::TBionic_AT:
    case ButtonType::TBionic_DF:
    {
        mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);

        UILayer* ui        = (UILayer*)this->getParent();
        SystemMessage smsg = {SMsgType::Upgrade, ReceiverType::Player, ActorType::None, type, nullptr};
        SendSystemMessage(ui, ui->mPlayer, smsg);
        return;
        // 만약 캔슬을 누르면 현재 선택된 액터에게 명령이 가도록 해야함
    } break;
    case ButtonType::TMarine:
    case ButtonType::TSCV:
    {
        UILayer* ui        = (UILayer*)this->getParent();
        SystemMessage smsg = {SMsgType::Create_Unit, ReceiverType::Player, ActorType::CommandCenter, type, nullptr};
        SendSystemMessage(ui, ui->mPlayer, smsg);
    }
    default:
        break;
    }

    // 어떤 버튼을 선택했는지 플레이어에게 보내준다

    UILayer* ui        = (UILayer*)this->getParent();
    SystemMessage smsg = {SMsgType::None, ReceiverType::Player, ActorType::None, type, nullptr};
    SendSystemMessage(ui, ui->mPlayer, smsg);
}

void CommandLayer::SetButton(Actor* actor)
{
    mCurActorType = actor->mActorType;
    mMenu->removeAllChildren();
    ClearSaveButtons();
    SetUnitControlButton(actor);
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

void CommandLayer::SetUnitControlButton(Actor* actor)
{
    auto ctrButtons = FindUnitControlButton(actor);
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

    if (t == nullptr) return nullptr;
 
    auto bt = ax::MenuItemImage::create(t->normal_Image, t->selected_Image, AX_CALLBACK_1(CommandLayer::ButtonMessage, this));

    bt->setUserData(t);
    bt->setScale(2.f);
    bt->setPosition(SetButtonPosition(t->iconPos));
    mMenu->addChild(bt, 1);

    return bt;
}

void CommandLayer::SingleSelected(SystemMessage smsg)
{
    if (mActor == (Actor*)smsg.data)
        return;

    mActor = (Actor*)smsg.data;
    
    if (mActor->mUnitComp->IsCmdLocked())
    {
        ChangeCmdState(CommandState::CmdLock);
    }
    else
    {
        ChangeCmdState(CommandState::Idle);
    }

}

void CommandLayer::MultiSelected(SystemMessage smsg) {}

void CommandLayer::ChangeCmdState(CommandState state)
{
    mCurState = state;
    switch (state)
    {
    case CommandState::None:
        break;
    case CommandState::Idle:
    {
        SetButton(mActor);
    }
        break;
    case CommandState::CmdLock:
    {
        mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);
    }
        break;
    default:
        break;
    }
}

