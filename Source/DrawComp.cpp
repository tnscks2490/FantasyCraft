#include "pch.h"
#include "DrawComp.h"
#include "MoveComp.h"


DrawComp::DrawComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mDrawComp = this;
}

DrawComp::~DrawComp() {}

void DrawComp::update(float delta)
{
    if (mActor->mMoveComp)
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
           /* if (mCurAction == ECharAct::Move)
            {
                
            }*/
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

        ax::Vec2 bodysize(16, 16);


        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setTag(10);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);      
        node->setAnchorPoint(ax::Vec2(0.5f, 0.5f));
        node->setPhysicsBody(body);
       
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
        body->setGravityEnable(false);

        body->setContactTestBitmask(0xFFFFFFFF);
        body->setCollisionBitmask(0xFFFFFFFF);
        body->setCategoryBitmask(0xFFFFFFFF);
        body->setDynamic(true);
        bodyNode->setPhysicsBody(body);


        auto drawNode = ax::DrawNode::create();
        drawNode->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4F::RED);
        bodyNode->addChild(drawNode);

        //루트노드에 피직스노드붙여주기
        mRoot->addChild(bodyNode);
        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, std::string_view nodeName)
{
    if (mRoot.isNotNull())
    {
        //AnimInfo& info = FindAnimInfo(name,ECharAct::Idle,ECharDir::Face);
        AnimInfo& info = FindAnimInfo(name, ECharAct::Idle, ECharDir::S); // 마린전용
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

        return node;
    }
    return nullptr;
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

    if (mVelocity.y > 0)
    {
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(11.25)))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(33.75)))
            return ECharDir::ENE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(56.25)))
            return ECharDir::NE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::NNE;
        if (mVelocity.x < cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::N;
        if (mVelocity.x > -cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::N;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::NNW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(56.25)))
            return ECharDir::NW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(33.75)))
            return ECharDir::WNW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(11.25)))
            return ECharDir::W;

    }
    else
    {
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(11.25)))
            return ECharDir::E;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(33.75)))
            return ECharDir::ESE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(56.25)))
            return ECharDir::SE;
        if (mVelocity.x > cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::SSE;
        if (mVelocity.x < cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::S;
        if (mVelocity.x > -cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::S;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(78.75)))
            return ECharDir::SSW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(56.25)))
            return ECharDir::SW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(33.75)))
            return ECharDir::WSW;
        if (mVelocity.x < -cos(AX_DEGREES_TO_RADIANS(11.25)))
            return ECharDir::W;
    }

    return ECharDir::S;
}

void DrawComp::isSelected()
{
    if (selected)
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("SelectNode");
        //selectNode->setVisible(true);
    }
    else
    {
        auto selectNode = (ax::DrawNode*)mRoot->getChildByName("SelectNode");
        selectNode->setVisible(false);
    }
}

