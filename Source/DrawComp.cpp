#include "pch.h"
#include "DrawComp.h"


DrawComp::DrawComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mDrawComp = this;
}

DrawComp::~DrawComp() {}

void DrawComp::update(float delta) {}

ax::Node* DrawComp::CreateRootNode()
{
    if (mRoot.isNull())
    {
        auto node = ax::Node::create();
        mRoot     = node;
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

        //루트노드에 피직스노드붙여주기
        mRoot.get()->addChild(bodyNode);
        return bodyNode;
    }
    return nullptr;
}

ax::Node* DrawComp::CreateAnimNode(ECharName name, ECharAct action, ECharDir dir)
{
    if (mRoot.isNotNull())
    {
        AnimInfo& info = FindAnimInfo(name, action, dir);
        info.CreateAnimation();

        auto node = ax::Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
        node->setName("Anim");

        auto animate = ax::Animate::create(info.animation.get());

        ax::Action* action;
        action = ax::RepeatForever::create(animate);
        action->setTag(20202);
        node->runAction(action);

        mRoot->addChild(node);
        return node;  
    }
    return nullptr;
}

void DrawComp::ChangeAnim(AnimInfo* info)
{
    auto anim = mRoot->getChildByName("Anim");

    anim->stopActionByTag(20202);

    info->CreateAnimation();



}

