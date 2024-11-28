#include "pch.h"
#include "Actor.h"
#include "TcpClient.h"
#include "MoveComp.h"
#include "DrawComp.h"


Actor::Actor()
{
}

Actor::~Actor()
{
    //TcpClient::get()->SendActorMessage(this, 'd');
}

void Actor::update(float delta)
{
    if (mMoveComp) mMoveComp->update(delta);
    if (mDrawComp) mDrawComp->update(delta);
}


ax::Node* Actor::GetRoot()
{
    if (mDrawComp)
    {
        if (mDrawComp->mRoot.isNotNull())
            return mDrawComp->mRoot.get();
    }

    return nullptr;
}

