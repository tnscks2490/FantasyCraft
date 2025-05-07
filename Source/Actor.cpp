#include "pch.h"
#include "Actor.h"
#include "TcpClient.h"
#include "SensorComp.h"
#include "MoveComp.h"
#include "DrawComp.h"
#include "UnitComp.h"
#include "GoalComp.h"
#include "Weapon/WeaponComp.h"
#include "CursorComp.h"
#include "BPComp.h"


Actor::Actor()
{}

Actor::Actor(PK_Data data)
{
    mID    = data.ClientID;
    charNum = data.input;
}

Actor::~Actor()
{
    if (mSensorComp) delete mSensorComp;
    if (mGoalComp) delete mGoalComp;
    if (mUnitComp) delete mUnitComp;
    if (mWeaponComp)  delete mWeaponComp;
    if (mMoveComp && mMoveComp->IsOn) delete mMoveComp;
    if (mCursorComp) delete mCursorComp;
    if (mBPComp) delete mBPComp;
    if (mDrawComp)  delete mDrawComp;
}

void Actor::update(float delta)
{
    if (mSensorComp) mSensorComp->update(delta);
    if (mGoalComp) mGoalComp->update(delta);
    if (mUnitComp) mUnitComp->update(delta);
    if (mWeaponComp) mWeaponComp->update(delta);
    if (mMoveComp && mMoveComp->IsOn) mMoveComp->update(delta);
    if (mBPComp) mBPComp->update(delta);
    if (mCursorComp) mCursorComp->update(delta);
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

