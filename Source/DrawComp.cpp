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

ax::Node* DrawComp::CreateSpriteNode(std::string_view filename)
{
    if (mRoot.isNotNull())
    {
        auto sprite = ax::Sprite::create(filename);
        sprite->setName("Sprite");

        mRoot.get()->addChild(sprite);
        return sprite;  
    }
    return nullptr;
}
