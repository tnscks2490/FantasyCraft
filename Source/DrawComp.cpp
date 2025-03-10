#include "pch.h"
#include "DrawComp.h"
#include "World.h"
#include "MoveComp.h"
#include "CursorComp.h"


DrawComp::DrawComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mDrawComp = this;
}

DrawComp::~DrawComp()
{
    if (mRoot.isNotNull())
        mRoot->removeFromParent();
}

void DrawComp::update(float delta)
{
    if (mActor->mMoveComp && mActor->mMoveComp->IsOn)
    {
        if (mActor->mMoveComp->IsMoving)
        {
            ECharDir newdir = CalcAniDir(mActor->GetVelocity());
            if (mCurDir != newdir)
            {
                mCurDir = newdir;
                mCurAction = ECharAct::Move;
                ChangeAnim(mCurAnim, ECharAct::Move, mCurDir);
            }
        }
        else
        {
           mCurAction = ECharAct::Idle;
           ChangeAnim(mCurAnim, ECharAct::Idle, mCurDir);
        }
    }

    // 커서에 한해서 변경하는 것
    if (mActor->mCursorComp)
    {
        if (mActor->mCursorComp->mState == CursorState::Idle && mCurAction != ECharAct::Idle)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::Idle, ECharDir::Face);
            mCurAction = ECharAct::Idle;
        }
        if (mActor->mCursorComp->mState == CursorState::ContactTeam
            && mCurAction != ECharAct::OnCursorTeam)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::OnCursorTeam, ECharDir::Face);
            mCurAction = ECharAct::OnCursorTeam;
        }
        if (mActor->mCursorComp->mState == CursorState::ContactEnemy
            && mCurAction != ECharAct::OnCursorEnemy)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::OnCursorEnemy, ECharDir::Face);
            mCurAction = ECharAct::OnCursorEnemy;
        }
        if (mActor->mCursorComp->mState == CursorState::Drag && mCurAction != ECharAct::Drag)
        {
            ChangeAnim(ECharName::Cursor, ECharAct::Drag, ECharDir::Face);
            mCurAction = ECharAct::Drag;
        }
        
    }

}

ax::Node* DrawComp::CreateRootNode()
{
    if (mRoot.isNull())
    {
        auto node = ax::Node::create();
        mRoot     = node;
        node->setName("Root");

        AddUserData();

        ///////////////////////////////
        // 루트노드 확인용 드로우 노드 //
        ///////////////////////////////
        auto draw = ax::DrawNode::create();
        draw->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4B::RED);
        node->addChild(draw);
        
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreatePhysicsNode(ax::Vec2 bodysize)
{
    if (mRoot.isNotNull())
    {
        //노드 생성
        auto bodyNode = ax::Node::create();
        bodyNode->setName("Body");
        
        
        //피직스바디생성 및 노드에 붙여주기

        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        bodyNode->setPhysicsBody(body);
        bodyNode->setTag(10);


        //루트노드에 피직스노드붙여주기
        mRoot->addChild(bodyNode);
        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateBPPhysicsNode(ax::Vec2 bodysize)
{
    if (mRoot.isNotNull())
    {
        auto bodyNode = ax::Node::create();
        bodyNode->setName("BPBody");
        // 피직스바디생성 및 노드에 붙여주기
        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        bodyNode->setPhysicsBody(body);
        bodyNode->setTag(11);

        ax::DrawNode* rect = ax::DrawNode::create();
        auto color         = ax::Color4B(0, 255, 0, 100);
        rect->drawSolidRect(ax::Vec2(-16, -16), ax::Vec2(16, 16), color);
        rect->setName("BPBodyRect");
        bodyNode->addChild(rect);

        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Small_BPPhysicsNode()
{
    ax::Vec2 bodysize(32, 32);
    if (mRoot.isNotNull())
    {
        auto body1 = CreatePhysicsNode(bodysize);
        auto rect  = ax::DrawNode::create();
        rect->drawSolidRect(ax::Vec2(-16, -16), ax::Vec2(16,16), ax::Color4B::GREEN);
        body1->addChild(rect);
        body1->setPosition(ax::Vec2(-32, 32));
        return body1;
    }
    return nullptr;
}

ax::Node* DrawComp::Create_Middle_BPPhysicsNode()
{
    return nullptr;
}

ax::Node* DrawComp::Create_Big_BPPhysicsNode()
{
    ax::Vec2 bodysize(32, 32);
    if (mRoot.isNotNull())
    {
        auto mainBody = ax::Node::create();
        mainBody->setName("BPMainBody");
        mRoot->addChild(mainBody,2.f);


        //탐지 피직스바디
        ////////////////////////////////////////////
        auto body1 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body1);
        body1->setPosition(ax::Vec2(-48, 32));

        auto body2 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body2);
        body2->setPosition(ax::Vec2(-16, 32));

        auto body3 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body3);
        body3->setPosition(ax::Vec2(16, 32));

        auto body4 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body4);
        body4->setPosition(ax::Vec2(48, 32));

        /////////////////////////////////////////
        auto body5 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body5);
        body5->setPosition(ax::Vec2(-48, 0));

        auto body6 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body6);
        body6->setPosition(ax::Vec2(-16, 0));

        auto body7 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body7);
        body7->setPosition(ax::Vec2(16, 0));

        auto body8 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body8);
        body8->setPosition(ax::Vec2(48, 0));

        ///////////////////////////////////////////
        auto body9 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body9);
        body9->setPosition(ax::Vec2(-48, -32));

        auto body10 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body10);
        body10->setPosition(ax::Vec2(-16, -32));

        auto body11 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body11);
        body11->setPosition(ax::Vec2(16, -32));

        auto body12 = CreateBPPhysicsNode(bodysize);
        mainBody->addChild(body12);
        body12->setPosition(ax::Vec2(48, -32));
        //////////////////////////////////////////////


        

        return mainBody;
    }
    return nullptr;
}


ax::Node* DrawComp::CreateCursorRect(ax::Vec2 sPos,ax::Vec2 ePos)
{
    if (mRoot.isNotNull())
    {
        auto drawnode = ax::DrawNode::create();
        drawnode->drawRect(sPos, ePos, ax::Color4B::GREEN);
        drawnode->setName("GreenRect");
        mRoot->addChild(drawnode);
    }
    return nullptr;
}

void DrawComp::ChangeRectSize(ax::Vec2 ePos)
{
    if (mRoot.isNotNull())
    {
        if (mRoot->getChildByName("GreenRect"))
        {
            ax::DrawNode* dnode = (ax::DrawNode*)mRoot->getChildByName("GreenRect");
            
        }
    }
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(name, ECharAct::Idle, ECharDir::S);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        return node;  
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, ECharAct action, ECharDir dir, std::string_view nodeName)
{
     if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(name, action, dir);  
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        mCurAnim = name;
        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNodeByIndex(ECharName name, int idx, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfoByIndex(name, ECharAct::Idle, ECharDir::Face,idx);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName(nodeName);
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateSelectedNode()
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(ECharName::Select, ECharAct::Idle, ECharDir::Face);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("SelectNode");
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        node->setVisible(false);

        return node;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateDemageNode(Actor* attackActor)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(ECharName::Effect, ECharAct::SCVSpark, ECharDir::Face);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("EffectNode");
        mRoot->addChild(node);

        ax::Animate* animate = ax::Animate::create(info.animation.get());

        ax::Action* action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        return node;
    }
    return nullptr;
}



void DrawComp::AddUserData()
{
    if (mRoot.isNotNull())
    {
        UserData* mUserData = new UserData;
        mUserData->mActor   = mActor;
        mRoot->setUserData(mUserData);
    }
}


void DrawComp::ChangeAnim(ECharName Name, ECharAct act, ECharDir dir)
{
    auto animNode = mRoot->getChildByName("Anim");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfo(Name, act, dir);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

    ax::Action* action;
    action = ax::RepeatForever::create(animate);
    action->setTag(20202);
    animNode->runAction(action);
}

void DrawComp::ChangeAnimByIndex(ECharName Name, ECharAct act, ECharDir dir, int idx)
{
    auto animNode = mRoot->getChildByName("Anim");
    animNode->stopActionByTag(20202);

    AnimInfo& animInfo = FindAnimInfoByIndex(Name, act, dir,idx);
    animInfo.CreateAnimation();

    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());

    ax::Action* action;
    action = ax::RepeatForever::create(animate);
    action->setTag(20202);
    animNode->runAction(action);
}


ECharDir DrawComp::CalcAniDir(ax::Vec2 mVelocity)
{
    /*float cos45 = cos(AX_DEGREES_TO_RADIANS(45));

    if (mVelocity.x > cos45)
        return ECharDir::Right;
    if (mVelocity.x < -cos45)
        return ECharDir::Left;
    if (mVelocity.y > 0)
        return ECharDir::Back;

    return ECharDir::Face;*/


    float cos45 = cos(AX_DEGREES_TO_RADIANS(45));
    float x     = 22.5;
    float a     = 11.25;
    if (mVelocity.y >= 0)
    {
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a)))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+x)))
            return ECharDir::ENE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*2))))
            return ECharDir::NE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*3))))
            return ECharDir::NNE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*4))))
            return ECharDir::N;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*5))))
            return ECharDir::NNW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*6))))
            return ECharDir::NW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a+(x*7))))
            return ECharDir::WNW;
        
        return ECharDir::W;
    }
    else
    {
        x *= -1;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a +(x*1))))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 2))))
            return ECharDir::ESE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 3))))
            return ECharDir::SE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 4))))
            return ECharDir::SSE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 5))))
            return ECharDir::S;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 6))))
            return ECharDir::SSW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 7))))
            return ECharDir::SW;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(a + (x * 8))))
            return ECharDir::WSW;

        return ECharDir::W;
    }
    return ECharDir::S;
}

void DrawComp::isSelected()
{
    if (selected)
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("Select");
        selectNode->setVisible(true);
    }
    else
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("Select");
        selectNode->setVisible(false);
    }
}

