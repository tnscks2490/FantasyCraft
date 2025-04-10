#include "pch.h"
#include "UI/UnitInfoLayer.h"
#include "UI/UILayer.h"
#include "Player.h"


bool UnitInfoLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    ax::DrawNode* draw = ax::DrawNode::create();
    draw->drawRect(ax::Vec2(-320, -80), ax::Vec2(320, 80), ax::Color4B::BLUE);
    addChild(draw);

    ax::DrawNode* dot = ax::DrawNode::create();
    dot->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::ORANGE);
    addChild(dot, 1);



    mMultiSelect = ax::Node::create();
    mMultiSelect->setName("MultiSelect");
    addChild(mMultiSelect, 1);

    mSingleSelect = ax::Node::create();
    mSingleSelect->setName("SingleSelect");
    addChild(mSingleSelect, 1);







    scheduleUpdate();

    return true;
}

void UnitInfoLayer::MessageProc(SystemMessage smsg)
{
    auto msg = smsg;
    {
        if (msg.smsgType == SMsgType::MSUI)
        {
            SwitchSelectUI(true);
            MultiSelected(msg);

        }
        else if (msg.smsgType == SMsgType::SSUI)
        {
            SwitchSelectUI(false);
            SingleSelected(msg);
        }
    }
}

void UnitInfoLayer::SwitchSelectUI(bool isMulti)
{
    if (isMulti)
    {
        mMultiSelect->setVisible(true);
        mSingleSelect->setVisible(false);
    }
    else
    {
        mMultiSelect->setVisible(false);
        mSingleSelect->setVisible(true);
    }
}

void UnitInfoLayer::MultiSelected(SystemMessage smsg)
{
    mMultiSelect->removeAllChildren();
    Actor** mActors = (Actor**)smsg.data;

    Actor* test[12] = {nullptr};

    // 고민해 볼것 깊은복사 그거
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

            mMultiSelect->addChild(bg, 2);
            mMultiSelect->addChild(wire, 2);
        }
    }
}

void UnitInfoLayer::SingleSelected(SystemMessage smsg)
{
    mSingleSelect->removeAllChildren();
    {
        Actor* sActor = (Actor*)smsg.data;
        showUnitInfoUI(sActor);
    }
}

void UnitInfoLayer::showUnitInfoUI(Actor* actor)
{
    showUnitWire(actor);
    showName(actor);
    showStatus(actor);
    showUpgrade(actor);
}

void UnitInfoLayer::showUnitWire(Actor* actor)
{
    ax::Sprite* wire = nullptr;

    switch (actor->mActorType)
    {
    case ActorType::SCV:
        wire = ax::Sprite::create("Big_SCV.png"sv);
        break;
    case ActorType::Marine:
        wire = ax::Sprite::create("Big_Marine.png"sv);
        break;
    case ActorType::CommandCenter:
        wire = ax::Sprite::create("CommandCenter.png"sv);
        break;
    default:
        break;
    }
    
    wire->setPosition(ax::Vec2(-250, 15));
    wire->setScale(2.f);
    mSingleSelect->addChild(wire, 2);
}

void UnitInfoLayer::showStatus(Actor* actor)
{
    auto status = actor->mUnitComp->mStatus;

    auto hp     = NumSlashNumToString(status.HP, status.MaxHP);
    auto hptext = ax::Label::createWithTTF(hp, "fonts/00TT.TTF", 16);
    hptext->setPosition(ax::Vec2(-250, -60));
    hptext->setTextColor(ax::Color4B::GREEN);
    mSingleSelect->addChild(hptext, 2);
}

void UnitInfoLayer::showUpgrade(Actor* actor)
{

    switch (actor->mActorType)
    {
    case ActorType::SCV:
    {
        auto atUpgrade = ax::Sprite::create("SCVAT.png"sv);
        atUpgrade->setScale(2.f);
        atUpgrade->setPosition(ax::Vec2(-20, -55));
        mSingleSelect->addChild(atUpgrade, 2);

        auto dfUpgrade = ax::Sprite::create("BionicDF.png"sv);
        dfUpgrade->setScale(2.f);
        dfUpgrade->setPosition(ax::Vec2(-100, -55));
        mSingleSelect->addChild(dfUpgrade, 2);
    } break;

    case ActorType::Marine:
    {
        auto atUpgrade = ax::Sprite::create("BionicAT.png"sv);
        atUpgrade->setScale(2.f);
        atUpgrade->setPosition(ax::Vec2(-20, -55));
        mSingleSelect->addChild(atUpgrade, 2);

        auto dfUpgrade = ax::Sprite::create("BionicDF.png"sv);
        dfUpgrade->setScale(2.f);
        dfUpgrade->setPosition(ax::Vec2(-100, -55));
        mSingleSelect->addChild(dfUpgrade, 2);
    }         
        break;
    default:
        break;
    }
   
    
}

void UnitInfoLayer::showName(Actor* actor)
{
    auto name = ax::Label::createWithTTF(actor->mUnitComp->GetUnitName(), "fonts/00TT.TTF", 20);
    name->setPosition(ax::Vec2(0, 70));
    mSingleSelect->addChild(name, 2);

    std::string str = "Kills : " + std::to_string(actor->mUnitComp->killCount);
    auto killCount  = ax::Label::createWithTTF(str, "fonts/00TT.TTF", 20);
    killCount->setPosition(ax::Vec2(0, 10));
    mSingleSelect->addChild(killCount, 2);
}


void UnitInfoLayer::showBuildingConstructionUI()
{}

void UnitInfoLayer::showProductionQueueUI()
{}


void UnitInfoLayer::update(float delta) {}
