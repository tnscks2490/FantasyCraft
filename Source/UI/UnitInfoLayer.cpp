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
    // 위의 두 노드는 UnitInfoLayer를 표시하기 위한 장치들//
    /////////////////////////////////////////////////////

    mName = ax::Label::createWithTTF("", "fonts/00TT.TTF", 24);
    mName->setPosition(ax::Vec2(0, 64));
    mName->setVisible(false);
    addChild(mName, 1);

    mWire = ax::Sprite::create();
    mWire->setScale(2.f);
    mWire->setPosition(ax::Vec2(-250, 16));
    mWire->setVisible(false);
    addChild(mWire, 1);

    mHP = ax::Label::createWithTTF("", "fonts/00TT.TTF", 16);
    mHP->setColor(ax::Color3B::GREEN);
    mHP->setPosition(ax::Vec2(-250, -64));
    addChild(mHP);


    mATUpgrade = ax::Sprite::create();
    mATUpgrade->setScale(2.f);
    mATUpgrade->setPosition(ax::Vec2(-16, -54));
    mATUpgrade->setVisible(false);
    addChild(mATUpgrade, 1);

    mDFUpgrade = ax::Sprite::create();
    mDFUpgrade->setScale(2.f);
    mDFUpgrade->setPosition(ax::Vec2(-96, -54));
    mDFUpgrade->setVisible(false);
    addChild(mDFUpgrade, 1);




    mLoadBar = CreateLoadNode(ECharName::LoadBar, ECharAct::Empty, ECharDir::Face);
    addChild(mLoadBar,1.f);
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
        MultiSelected(msg);
    } break;
    case SMsgType::SSUI:
    {
        SingleSelected(msg);
    } break;
    case SMsgType::Create_Unit:
    {
    }
    default:
        break;
    }
}

void UnitInfoLayer::update(float delta)
{

    if (mCurState == LayerState::None)
        return;

    if (mCurState == LayerState::Build)
    {
        mCurLoadTime += delta;
        int idx     = (int)(mCurLoadTime/mFrame);
        if (idx != mLoadIdx)
        {
            mLoadIdx = idx;
            if (mLoadIdx == 68)
            {
                mCurState = LayerState::Idle;
                mLoadBar->setVisible(false);
                return;
            }
            ChangeLoadBar(mLoadIdx, false);
        }
    }
    // 체력 변동 자동 적용함수 넣을 것
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
    if (mActor == (Actor*)smsg.data)
        return;

    mActor = (Actor*)smsg.data;
    resetInfoData(mActor);
    

    // 해당 유닛이 건물인지 아닌지 먼저 판별
    if (mActor->mCategory == UnitCategory::Building)
    {
        if (!mActor->mUnitComp->IsBuild())
        {

            mCurLoadTime = mActor->mUnitComp->GetCurLoadTime();
            mMaxLoadTime = mActor->mUnitComp->GetMaxLoadTime();
            mFrame  = mMaxLoadTime / 68.f;
            mLoadIdx     = (int)(mCurLoadTime * mFrame);
            ChangeLayerState(LayerState::Build);
        }
        else
        {
            if (mActor->mUnitComp->mCurAction == ActionState::Create_Unit)
            {
                printf("여기야 여기");
            }
        }
    }
    else // 여기로 들어오는 순간 모두 유닛
    {
        ChangeLayerState(LayerState::Idle);
    }
    
}


void UnitInfoLayer::ChangeLayerState(LayerState cState)
{
    AllNodeUnVisible();
    switch (cState)
    {
    case LayerState::None:
        break;
    case LayerState::Idle:
    {
        mName->setVisible(true);
        mWire->setVisible(true);
        mHP->setVisible(true);

        // 각 건물별로 설명이 다르기 때문에 넣어줄것
        if (mActor->mCategory == UnitCategory::Unit)
        {
            mATUpgrade->setVisible(true);
            mDFUpgrade->setVisible(true);
        } 
    } break;
    case LayerState::Build:
    {
        mLoadBar->setVisible(true);
    } break;
    case LayerState::CreateUnit:
    {
        mName->setVisible(true);
        mWire->setVisible(true);
        mHP->setVisible(true);
        mUnitList->setVisible(true);
        mLoadBar->setVisible(true);
    }
        break;
    case LayerState::Upgrade:
    {
        mUpgradeSprite->setVisible(true);
        mLoadBar->setVisible(true);
    }
        break;
    case LayerState::MultiSelect:
        break;
    default:
        break;
    }
}

ax::SpriteFrame* UnitInfoLayer::FindWireFrame(Actor* actor)
{
    auto spritecache = ax::SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("Plist/UISprite.plist");

    std::string str = "";

    switch (actor->mActorType)
    {
    case ActorType::SCV: str = "UISprite/Wire_SCV.png"; break;
    case ActorType::Marine: str = "UISprite/Wire_Marine.png"; break;
    case ActorType::CommandCenter: str = "UISprite/Wire_CommandCenter.png"; break;
    default:
        break;
    }
    auto frame = spritecache->getSpriteFrameByName(str);
    return frame;
}
ax::SpriteFrame* UnitInfoLayer::FindATUpgradeSprite(Actor* actor)
{
    auto spritecache = ax::SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("Plist/UISprite.plist");

    std::string str = "";

    switch (actor->mActorType)
    {
    case ActorType::SCV: str = "UISprite/SCVAT.png"; break;
    case ActorType::Marine: str = "UISprite/BionicAT.png"; break;
    default:
        break;
    }
    auto frame = spritecache->getSpriteFrameByName(str);
    return frame;
}
ax::SpriteFrame* UnitInfoLayer::FindDFUpgradeSprite(Actor* actor)
{
    auto spritecache = ax::SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("Plist/UISprite.plist");

    std::string str = "";

    switch (actor->mActorType)
    {
    case ActorType::SCV:
    case ActorType::Marine: str = "UISprite/BionicDF.png"; break;

    default:
        break;
    }
    auto frame = spritecache->getSpriteFrameByName(str);
    return frame;
}

void UnitInfoLayer::resetInfoData(Actor* actor)
{
    auto ac = actor;
    mName->setString(ac->mUnitComp->GetUnitName());
    mWire->setSpriteFrame(FindWireFrame(ac));

    mATUpgrade->setSpriteFrame(FindATUpgradeSprite(ac));
    mDFUpgrade->setSpriteFrame(FindDFUpgradeSprite(ac));

    mMaxHP = ac->mUnitComp->mStatus.MaxHP;
    mCurHP = ac->mUnitComp->mStatus.HP;
    auto hpstr = NumSlashNumToString(mCurHP, mMaxHP);
    mHP->setString(hpstr);
   
}


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

void UnitInfoLayer::AllNodeUnVisible()
{
    if (mName) mName->setVisible(false);
    if (mWire) mWire->setVisible(false);    
    if (mHP) mHP->setVisible(false);       
    if (mLoadBar) mLoadBar->setVisible(false);    
    if (mATUpgrade) mATUpgrade->setVisible(false);
    if (mDFUpgrade) mDFUpgrade->setVisible(false);
    if (mUnitList)  mUnitList->setVisible(false);
    if (mUpgradeSprite) mUpgradeSprite->setVisible(false);
}



