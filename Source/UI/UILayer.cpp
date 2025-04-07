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
    addChild(resource, 1);

    printf("현재 자식 노드 확인하는 줄");


    return true;
}

void UILayer::MessageProc(SystemMessage smsg)
{
    printf("UI가 플레이어로부터 메세지를 수신받았습니다.");
    auto msg = smsg;

    CommandLayer* command = (CommandLayer*)this->getChildByName("CommandLayer");
    //auto command = this->getChildByName("CommandLayer");

    switch (msg.smsgType)
    {
    case SMsgType::None:
    {
        command->SetButton(msg.Atype);
        //SetButton(msg.Atype);
    } break;
    case SMsgType::MSUI:
    {
        BottomUI->removeAllChildren();
        Actor** mActors = (Actor**)msg.data;

        Actor* test[12] = {nullptr};

        //고민해 볼것 깊은복사 그거
        for (int i = 0; i < 12; i++)
        {
            if (mActors[i] != nullptr)
            {
                test[i] = mActors[i];

                ax::Sprite* wire = nullptr;
                switch (test[i]->mActorType)
                {
                case ActorType::Marine:
                    wire = ax::Sprite::create("Marine.png"sv);
                    break;
                case ActorType::SCV:
                    wire = ax::Sprite::create("SCV.png"sv);
                    break;
                case ActorType::CommandCenter:
                    wire = ax::Sprite::create("CommandCenter.png"sv);
                    break;
                default:
                    break;
                }

                auto bg = ax::Sprite::create("selectRect.png"sv);
                bg->setScale(2.f);
                wire->setScale(2.f);

                if (i % 2 == 0)
                {
                    bg->setPosition(ax::Vec2(i * 35 - 260, 40));
                    wire->setPosition(ax::Vec2(i * 35 - 260, 40));
                }
                else
                {
                    bg->setPosition(ax::Vec2((i * 35 - 35) - 260, -40));
                    wire->setPosition(ax::Vec2((i * 35 - 35) - 260, -40));
                }

                BottomUI->addChild(bg, 2);
                BottomUI->addChild(wire, 2);
            }
        }
        printf("체크");
    }
        break;
    case SMsgType::SSUI:
    {
        BottomUI->removeAllChildren();
        Actor* sActor = (Actor*)msg.data;

        ax::Sprite* wire = nullptr;
        // 추가로 쉴드 업글이나 등등 넣어줄것(이것도 바꿔야함)임시방편임
        ax::Sprite* atUpgrade = nullptr;
        ax::Sprite* dfUpgrade = nullptr;
        switch (sActor->mActorType)
        {
        case ActorType::Marine:
            wire = ax::Sprite::create("Big_Marine.png"sv);
            atUpgrade = ax::Sprite::create("BionicAT.png"sv);
            dfUpgrade = ax::Sprite::create("BionicDF.png"sv);
            break;
        case ActorType::SCV:
            wire = ax::Sprite::create("Big_SCV.png"sv);
            atUpgrade = ax::Sprite::create("SCVAT.png"sv);
            dfUpgrade = ax::Sprite::create("BionicDF.png"sv);
            break;
        case ActorType::CommandCenter:
            wire = ax::Sprite::create("CommandCenter.png"sv);
            break;
        default:
            break;
        }
        wire->setPosition(ax::Vec2(-250, 15));
        wire->setScale(2.f);
        BottomUI->addChild(wire, 2);

        auto status = sActor->mUnitComp->mStatus;

        auto hp = NumSlashNumToString(status.HP, status.MaxHP);
        auto hptext = ax::Label::createWithTTF(hp, "fonts/00TT.TTF", 16);
        hptext->setPosition(ax::Vec2(-250, -60));
        hptext->setTextColor(ax::Color4B::GREEN);
        BottomUI->addChild(hptext, 2);

        auto name = ax::Label::createWithTTF(sActor->mUnitComp->GetUnitName(), "fonts/00TT.TTF",20);
        name->setPosition(ax::Vec2(0, 70));
        BottomUI->addChild(name, 2);


        std::string str = "Kills : " + std::to_string(sActor->mUnitComp->killCount);
        auto killCount        = ax::Label::createWithTTF(str, "fonts/00TT.TTF", 20);
        killCount->setPosition(ax::Vec2(0, 10));
        BottomUI->addChild(killCount, 2);



        
        if (dfUpgrade)
        {
            dfUpgrade->setScale(2.f);
            dfUpgrade->setPosition(ax::Vec2(-100, -55));
            BottomUI->addChild(dfUpgrade, 2);
        }
        
        if (atUpgrade)
        {
            atUpgrade->setScale(2.f);
            atUpgrade->setPosition(ax::Vec2(-20, -55));
            BottomUI->addChild(atUpgrade, 2);
        }
        




    }
        break;
    default:
        break;
    }


    
}



void UILayer::SetUI(PlayerRace race)
{
    switch (race)
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

void UILayer::ButtonMessage(ax::Object* sender)
{
    auto node        = (ax::Node*)sender;
    ButtonInfo* info = (ButtonInfo*)node->getUserData();

    auto type = info->type;


    switch (type)
    {
        //이레귤러
    case ButtonType::TCancel:
    {
        //mMenu->removeAllChildren();
        ReturnButton();
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
        //mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);
    } break;
        // 다른 버튼 UI로 변경되는 버튼들
    case ButtonType::TCommon_Build:
    {
        //mMenu->removeAllChildren();

        SetCBButton();
    } break;

    case ButtonType::TAdvance_Build:
    {
        //mMenu->removeAllChildren();
        SetABButton();
    } break;

    case ButtonType::TLift:
    case ButtonType::TLand:
        break;
    case ButtonType::TCommand_Center:
    {
        //mMenu->removeAllChildren();
        CreateAddButton(ButtonType::TCancel);
        // 만약 캔슬을 누르면 SCV에게 명령이 가도록 해야함
    }
    default:
        break;
    }


    // 어떤 버튼을 선택했는지 플레이어에게 보내준다
    SystemMessage smsg;
    smsg.Btype = type;
    SendSystemMessage(this, mPlayer, smsg);

}

void UILayer::SetButton(ActorType type)
{
    mCurActorType = type;
    ClearSaveButtons();
    SetUnitControlButton(type);
}

void UILayer::SetCBButton()
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
void UILayer::SetABButton()
{
    CreateAddButton(ButtonType::TFactory);
    CreateAddButton(ButtonType::TStarPort);
    CreateAddButton(ButtonType::TScience_Facility);
    CreateAddButton(ButtonType::TArmory);
    CreateAddButton(ButtonType::TCancel);
}
void UILayer::ReturnButton()
{
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        CreateAddButton(mSavebuttons[i]);
    }
}


void UILayer::ClearSaveButtons()
{
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        mSavebuttons[i] = ButtonType::None;
    }
}

void UILayer::SetUnitControlButton(ActorType Atype)
{
    auto ctrButtons = FindUnitControlButton(Atype);
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        CreateAddButton(ctrButtons->buttons[i]);
        mSavebuttons[i] = ctrButtons->buttons[i];
    }
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
ax::MenuItemImage* UILayer::CreateAddButton(ButtonType type)
{
    ButtonInfo* t = FindButtonInfo(type);
     
    auto bt = ax::MenuItemImage::create(t->normal_Image, t->selected_Image, AX_CALLBACK_1(UILayer::ButtonMessage, this));

    bt->setUserData(t);
    bt->setScale(2.f);
    bt->setPosition(SetButtonPosition(t->iconPos));
    return bt;
}
