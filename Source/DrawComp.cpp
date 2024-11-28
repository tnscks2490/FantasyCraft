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
        auto bodyNode = ax::Node::create();
        bodyNode->setName("Body");

        auto body = ax::PhysicsBody::createBox(bodysize);
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        bodyNode->setPhysicsBody(body);
        return bodyNode;
    }
    return nullptr;
}
