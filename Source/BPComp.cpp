#include "pch.h"
#include "Actor.h"
#include "IActorComp.h"
#include "BPComp.h"
#include "DrawComp.h"



BPComp::BPComp(Actor* actor)
    : IActorComp(actor)
{ 
    mActor->mBPComp = this;
}

BPComp::~BPComp()
{
    mActor->mBPComp = nullptr;
}

void BPComp::MessageProc(ActorMessage& msg)
{
    UserData* other = (UserData*)msg.data;

    switch (msg.msgType)
    {
    case MsgType::Contacted:
    {
        ContactedUnit(msg);
    }  break;
    case MsgType::Separate:
    {
        SeparatedUnit(msg);
    }
    default:
        break;
    }
}

void BPComp::update(float delta)
{


}



void BPComp::ContactedUnit(ActorMessage& msg)
{
    auto bodyNode = msg.bodyNode;
    UserData* other = (UserData*)msg.data;

    if (other->mActor->GetRoot()->getChildByName("Body"))
    {
        if (other->mActor->GetRoot()->getChildByName("Body")->getTag() == 10)
        {
            if (bodyNode->getChildByName("BPBodyRect"))
            {
                ax::DrawNode* dNode = (ax::DrawNode*)bodyNode->getChildByName("BPBodyRect");
                dNode->clear();
                auto color = ax::Color4B(255, 0, 0, 100);
                dNode->drawSolidRect(ax::Vec2(-16, -16), ax::Vec2(16, 16), color);
                BuildPossible = false;
            }
        }
    }
}

void BPComp::SeparatedUnit(ActorMessage& msg)
{
    auto bodyNode   = msg.bodyNode;
    UserData* other = (UserData*)msg.data;

    if (other->mActor->GetRoot()->getChildByName("Body"))
    {
        if (other->mActor->GetRoot()->getChildByName("Body")->getTag() == 10)
        {
            if (bodyNode->getChildByName("BPBodyRect"))
            {
                ax::DrawNode* dNode = (ax::DrawNode*)bodyNode->getChildByName("BPBodyRect");
                dNode->clear();
                auto color = ax::Color4B(0, 255, 0, 100);
                dNode->drawSolidRect(ax::Vec2(-16, -16), ax::Vec2(16, 16), color);
                BuildPossible = true;
            }
        }
    }
}



