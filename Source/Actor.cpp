#include "pch.h"
#include "Actor.h"
#include "TcpClient.h"
#include "MoveComp.h"
#include "DrawComp.h"
#include "UnitComp.h"
#include "GoalComp.h"


Actor::Actor()
{}

Actor::Actor(PK_Data data)
{
    mID    = data.ClientID;
    charNum = data.input;
}

Actor::~Actor()
{
    //TcpClient::get()->SendActorMessage(this, 'd');
}

void Actor::update(float delta)
{
    if (mGoalComp) mGoalComp->update(delta);
    if (mUnitComp) mUnitComp->update(delta);
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

void Actor::SetPosition(ax::Vec2 pos)
{
    if (mDrawComp->mRoot.isNotNull())
    {
        mDrawComp->mRoot->setPosition(pos);
    }
}


ax::Vec2 Actor::GetPosition()
{
    if (mDrawComp->mRoot.isNotNull())
    {
        return mDrawComp->mRoot->getPosition();
    }
}

ax::Vec2 Actor::GetVelocity()
{
    if (mMoveComp)
        return mMoveComp->mVelocity;
}

