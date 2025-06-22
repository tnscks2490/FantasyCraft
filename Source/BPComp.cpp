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
        int tag = other->mActor->GetRoot()->getChildByName("Body")->getTag();

        if (mBPType == ActorType::Refinery)
        {
            int OtherX = other->mActor->GetPosition().x;
            int OtherY = other->mActor->GetPosition().y;

            OtherX /= 32;
            OtherY /= 32;

            auto actors = World::get()->w_ActorList;
            for (auto actor : actors)
            {
                if (actor->mActorType == ActorType::Gas)
                {
                    int Gx = actor->GetPosition().x/32;
                    int Gy = actor->GetPosition().y/32;

                    if (OtherX == Gx && OtherY == Gy)
                    {
                        ax::DrawNode* dNode = (ax::DrawNode*)bodyNode->getChildByName("BPBodyRect");
                        dNode->clear();
                        auto color = ax::Color4B(0, 255, 0, 100);
                        dNode->drawSolidRect(ax::Vec2(-48, -32), ax::Vec2(48, 32), color);
                        BuildPossible = true;
                    }
                }
            }
        }
        else
        {
            if (tag == 10 || tag == 20)
            {
               // 상대방의 충돌 노드는 알수있지만 자신의 어떤 노드가 충돌했는지 알수가없음
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
        int tag = other->mActor->GetRoot()->getChildByName("Body")->getTag();

        if (mBPType == ActorType::Refinery)
        {
            if (bodyNode->getChildByName("BPBodyRect"))
            {
                ax::DrawNode* dNode = (ax::DrawNode*)bodyNode->getChildByName("BPBodyRect");
                dNode->clear();
                auto color = ax::Color4B(255, 0, 0, 100);
                dNode->drawSolidRect(ax::Vec2(-48, -32), ax::Vec2(48, 32), color);
                BuildPossible = true;
            }
        }
        else
        {
            if (tag == 10 || tag == 20)
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
}



