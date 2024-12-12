#include "pch.h"
#include "Actor.h"
#include "IActorComponent.h"
#include "ActorMessage.h"
#include "World.h"
#include "AllActorCompoenet.h"

void SendActorMessage(Actor* r, ActorMessage msg)
{
    
    // Actor 안에 
    // Message를 받을 Component를 찿아서
    // 전달해 준다...
    //

    switch (msg.msgType)
    {
    case ActorMessage::MoveToTarget:
    {
        AMsgData_Vec2* v = (AMsgData_Vec2*)msg.data;
        AddGoal_MoveToTarget(r, v->pos);
    }
        break;

    case ActorMessage::AddToNextTarget:
        {
            AMsgData_Vec2* v = (AMsgData_Vec2*)msg.data;
            if (r->mMoveComp) r->mMoveComp->PushTargetList(v->pos);
        }
        break;
    case ActorMessage::Contacted:
        if (r->mProjectileComp) r->mProjectileComp->MessageProc(msg);
        if (r->mCursorComp)   r->mCursorComp->MessageProc(msg);
        if (r->mFarmComp)     r->mFarmComp->MessageProc(msg);
        if (r->mUnitComp)     r->mUnitComp->MessageProc(msg);
        if (r->mTreeComp)     r->mTreeComp->MessageProc(msg);
        break;
    case ActorMessage::Separate:
        if (r->mCursorComp)   r->mCursorComp->MessageProc(msg);
        if (r->mTreeComp)     r->mTreeComp->MessageProc(msg);
        break;
    case ActorMessage::MoveClick:
        if (r->mCursorComp)   r->mCursorComp->MessageProc(msg);
        break;
    case ActorMessage::GameClick:
        if (r->mCursorComp)   r->mCursorComp->MessageProc(msg);
        if (r->mUnitComp)  r->mUnitComp->MessageProc(msg);
        break;
    case ActorMessage::ChangeStatus:
        if (r->mUnitComp)     r->mUnitComp->MessageProc(msg);
        break;
    case ActorMessage::Attack:
        if (r->mUnitComp) r->mUnitComp->MessageProc(msg);
        break;
    case ActorMessage::Damaged:
        if (r->mUnitComp) r->mUnitComp->MessageProc(msg);
        break;
    default:
        break;
    }

}
