#include "pch.h"
#include "UI/ResourceLayer.h"

bool ResourceLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    ax::DrawNode* draw = ax::DrawNode::create();
    draw->drawRect(ax::Vec2(-192, -32), ax::Vec2(192, 32), ax::Color4B::RED);
    addChild(draw, 1);

    ax::DrawNode* dot = ax::DrawNode::create();
    dot->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::BLUE);
    addChild(dot, 1);




    mMineralIcon = ax::Sprite::create("MineralIcon.png"sv);
    mMineralIcon->setScale(2.f);
    mMineralIcon->setPosition(ax::Vec2(-128, 0));
    addChild(mMineralIcon, 1);


    /*ax::DrawNode* dot2 = ax::DrawNode::create();
    dot2->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::RED);
    mMineralIcon->addChild(dot2, 1);*/

   
    mGasIcon     = ax::Sprite::create("TGasIcon.png"sv);
    mGasIcon->setScale(2.f);
    addChild(mGasIcon, 1);

    mPopIcon     = ax::Sprite::create("TPopIcon.png"sv);
    mPopIcon->setScale(2.f);
    mPopIcon->setPosition(ax::Vec2(128, 0));
    addChild(mPopIcon, 1);



    scheduleUpdate();

    return true;
}

void ResourceLayer::MessageProc(SystemMessage smsg)
{
    switch (smsg.smsgType)
    {
    case SMsgType::ChangeResource:
    {
        updateResource();
    }
    default:
        break;
    }
}

void ResourceLayer::update(float delta)
{
     
}

void ResourceLayer::updateResource()
{
    if (mPlayer)
    {
        auto str    = std::to_string(mPlayer->mMineral);
        mMineralNum->setString(str);

        auto str2 = std::to_string(mPlayer->mGas);
        mGasNum->setString(str2);

        std::string str3 = std::to_string(mPlayer->mCurPop) + "/" + std::to_string(mPlayer->mCurMaxPop);
        mPopNum->setString(str3);          
    }
}

void ResourceLayer::SetNumText()
{
    if (mPlayer)
    {
        auto str    = std::to_string(mPlayer->mMineral);
        mMineralNum = ax::Label::createWithTTF(str, "fonts/00TT.TTF", 20);
        mMineralNum->setAlignment(ax::TextHAlignment::LEFT);
        mMineralNum->setAnchorPoint(ax::Vec2(0, 0.5f));
        mMineralNum->setPosition(ax::Vec2(-108, 0));
        mMineralNum->setColor(ax::Color3B::GREEN);
        addChild(mMineralNum, 1);

        ax::DrawNode* dot2 = ax::DrawNode::create();
        dot2->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::RED);
        mMineralNum->addChild(dot2, 1);
        /////////////////////////////////////////////////

        auto str2    = std::to_string(mPlayer->mGas);
        mGasNum   = ax::Label::createWithTTF(str2, "fonts/00TT.TTF", 20);
        mGasNum->setAlignment(ax::TextHAlignment::LEFT);
        mGasNum->setAnchorPoint(ax::Vec2(0, 0.5f));
        mGasNum->setPosition(ax::Vec2(20, 0));
        mGasNum->setColor(ax::Color3B::GREEN);
        addChild(mGasNum, 1);

        ax::DrawNode* dot3 = ax::DrawNode::create();
        dot3->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::RED);
        mGasNum->addChild(dot3, 1);

        /////////////////////////////////////////////////

        std::string str3 = std::to_string(mPlayer->mCurPop) + "/"
            + std::to_string(mPlayer->mCurMaxPop);
        mPopNum          = ax::Label::createWithTTF(str3, "fonts/00TT.TTF", 20);
        mPopNum->setAlignment(ax::TextHAlignment::LEFT);
        mPopNum->setAnchorPoint(ax::Vec2(0, 0.5f));
        mPopNum->setPosition(ax::Vec2(148, 0));
        mPopNum->setColor(ax::Color3B::GREEN);
        addChild(mPopNum, 1);

        ax::DrawNode* dot4 = ax::DrawNode::create();
        dot4->drawDot(ax::Vec2::ZERO, 3, ax::Color4B::RED);
        mPopNum->addChild(dot4, 1);
    }
}


