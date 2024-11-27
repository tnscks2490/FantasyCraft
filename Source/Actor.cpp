#include "pch.h"
#include "Actor.h"
#include "TcpClient.h"
#include "MoveComp.h"

Actor::Actor()
{
    mRoot = ax::Node::create();
    mRoot->retain();
}

Actor::~Actor()
{
    //TcpClient::get()->SendActorMessage(this, 'd');
}

void Actor::update(float delta)
{
    if (mMoveComp)
        mMoveComp->update(delta);
}

void Actor::AddChild(ax::Node* node)
{
    mRoot->addChild(node);
}

