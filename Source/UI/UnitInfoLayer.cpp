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





    mLoadBar = CreateLoadNode(ECharName::LoadBar, ECharAct::Empty, ECharDir::Face);
    this->addChild(mLoadBar,1.f);
    mLoadBar->setVisible(false);
    mLoadBar->setScale(2.f);

    scheduleUpdate();

    return true;
}

void UnitInfoLayer::MessageProc(SystemMessage smsg)
{
    auto msg = smsg;
    switch (msg.smsgType)
    {
    case SMsgType::MSUI:
    {
        SwitchSelectUI(true);
        MultiSelected(msg);
    } break;
    case SMsgType::SSUI:
    {
        SwitchSelectUI(false);
        SingleSelected(msg);
    } break;
    case SMsgType::Create_Unit:
    {
        ShowCreatingUnit(smsg.Atype);
    }
    default:
        break;
    }
}

void UnitInfoLayer::update(float delta)
{
    if (isLoad)
    {
        mCurLoadTime += delta;
        int idx     = (int)(mCurLoadTime/mFrame);
        if (idx != mLoadIdx)
        {
            mLoadIdx = idx;
            if (mLoadIdx == 68)
            {
                isLoad = false;
                mLoadBar->setVisible(false);
                return;
            }
            ChangeLoadBar(mLoadIdx, false);
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
    mLoadBar->setVisible(false);

    Actor* sActor = (Actor*)smsg.data;

    if (sActor->mCategory == UnitCategory::Building)
    {
        if (!sActor->mUnitComp->IsBuild())
        {
            showUnitWire(sActor);
            showStatus(sActor);


            mCurLoadTime = sActor->mUnitComp->GetCurLoadTime();
            mMaxLoadTime = sActor->mUnitComp->GetMaxLoadTime();
            mFrame  = mMaxLoadTime / 68.f;
            mLoadIdx     = (int)(mCurLoadTime * mFrame);
            mLoadBar->setVisible(true);
            isLoad = true;
        }
        else
        {
            if (sActor->mUnitComp->mCurAction == ActionState::Create_Unit)
            {
                printf("여기야 여기");
            }
        }
    }
     

    //showUnitInfoUI(sActor);

}

void UnitInfoLayer::showUnitInfoUI(Actor* actor)
{
    showUnitWire(actor);
    showStatus(actor);
    showName(actor);
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

void UnitInfoLayer::showProductionQueueUI() {}

ax::Node* UnitInfoLayer::CreateLoadNode(ECharName name, ECharAct act, ECharDir dir, std::string_view nodeName)
{
    AnimInfo& info = FindAnimInfo(name, act, dir);
    info.CreateAnimation();

    auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
    node->setName(nodeName);

    ax::Animate* animate = ax::Animate::create(info.animation.get());

    ax::Action* action = ax::Repeat::create(animate, 1);
    action->setTag(20202);
    node->runAction(action);

    return node;
}

void UnitInfoLayer::ChangeLoadBar(int idx, bool isEmpty)
{
    mLoadBar->stopActionByTag(20202);

    ECharAct act = ECharAct::Load;

    if (!isEmpty)   act = ECharAct::Load;
    else            act = ECharAct::Empty;

    AnimInfo& animInfo = FindAnimInfoByIndex(ECharName::LoadBar, act,
                                             ECharDir::Face, idx);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

    ax::Action* action;
    action = ax::RepeatForever::create(animate);
    action->setTag(20202);
    mLoadBar->runAction(action);
}

void UnitInfoLayer::ShowCreatingUnit(ActorType type)
{
    auto Bg = ax::Sprite::create("UnitList.png"sv);
    addChild(Bg, 1.f);
}

