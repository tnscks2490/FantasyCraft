#include "pch.h"
#include "Actor.h"
#include "MarineComp.h"
#include "DrawComp.h"

MarineComp::MarineComp(Actor* actor)
    : UnitComp(actor)
{
    actor->mUnitComp = this;
    SetUnitStatus(ActorType::Marine);
    mWireFrame = ax::Sprite::create("Marine.png"sv);
    mActor->GetRoot()->addChild(mWireFrame);
    mWireFrame->setVisible(false);
}

MarineComp::~MarineComp() {}

void MarineComp::update(float delta) {}

void MarineComp::MessageProc(ActorMessage& msg)
{
    
    switch (msg.msgType)
    {
    case MsgType::SetTarget:
    {
        mTarget = msg.sender;

        ActorMessage msg = {MsgType::Attack, mActor, nullptr, nullptr};
        SendActorMessage(mTarget, msg);
        auto pos   = mTarget->GetPosition() - mActor->GetPosition();
        mActor->mDrawComp->mCurAnimInfo->dir = mActor->mDrawComp->CalcAniDir(pos/pos.length());
        mCurAction = ActionState::Attack;
    }
    break;
    default:
        break;
    }
}
