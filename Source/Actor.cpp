#include "Actor.h"
#include "TcpClient.h"

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
}

void Actor::AddChild(ax::Node* node)
{
    mRoot->addChild(node);
}

