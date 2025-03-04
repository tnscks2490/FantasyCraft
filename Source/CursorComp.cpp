#include "pch.h"
#include "CursorComp.h"
#include "Actor.h"
#include "PrePacket.h"
#include "DrawComp.h"


CursorComp::CursorComp(Actor* actor)
    : IActorComp(actor)
{
    actor->mCursorComp = this;
}

CursorComp::~CursorComp()
{
    
}

void CursorComp::update(float delta)
{
    switch (mState)
    {
    case CursorState::Idle:
        mActor->mDrawComp->ChangeAnim(ECharName::Cursor, ECharAct::Idle, ECharDir::Face);
        break;
    case CursorState::Drag:
    {
        if (mActor->GetRoot()->getChildByName("GreenRect"))
        {
            ax::DrawNode* drawnode = (ax::DrawNode*)mActor->GetRoot()->getChildByName("GreenRect");
            drawnode->clear();
            drawnode->drawRect(sPos - drawnode->getParent()->getPosition(),
                ePos - drawnode->getParent()->getPosition(), ax::Color4B::GREEN);
        }
    } break;

    case CursorState::Move:
        break;
    case CursorState::Click:
        break;
    case CursorState::BluePrint:
        break;
    case CursorState::ContactTeam:
        break;
    case CursorState::ContactEnemy:
        break;
    case CursorState::Target:
        mActor->mDrawComp->ChangeAnim(ECharName::Cursor, ECharAct::Target, ECharDir::Face);
        break;
    default:
        break;
    }
}

void CursorComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case MsgType::BPCMC:
        CreateBuildingBP(BuildingName::CommandCenter);
        break;
    default:
        break;
    }
}

void CursorComp::CursorUp()
{

    //GetDrawNode()->clear();
    CheckNodeInDrag();
    isDraging = false;
}

void CursorComp::BPFollowCursor()
{
   /* ax::Vec2 pos;
    pos.x = mRoot->getPosition().x / 32;
    pos.y = mRoot->getPosition().y / 32;
    sp->setPosition(pos*32);*/
}

void CursorComp::CursorMove(ax::Vec2 pos)
{
    //mDrawComp->mRoot->setPosition(pos);
}


void CursorComp::LClick(ax::Vec2 pos)
{
    if (bp)
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 10;
        data.pos      = pos;
        TcpClient::get()->SendMessageToServer(data);

        ReleaseBP();
            
    }
    if (mState == CursorState::Move)
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 114;
        data.pos      = pos;
        TcpClient::get()->SendMessageToServer(data);
    }
    else if (mState == CursorState::Target)
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 114;
        data.pos      = pos;
        TcpClient::get()->SendMessageToServer(data);
    }
}

void CursorComp::RClick(ax::Vec2 pos)
{

}


void CursorComp::CheckNodeInDrag()
{

    int sx = sPos.x / 16;
    int sy = sPos.y / 16;

    int ex = ePos.x / 16;
    int ey = ePos.y / 16;

    // 드래그 속 체크 노드
    
    auto checknode = ax::Node::create();
    checknode->setName("CursorCheckNode");
    //mDrawComp->mRoot->addChild(checknode);

    ax::Vec2 boxSize;
    boxSize.x = std::max(sPos.x, ePos.x) - std::min(sPos.x, ePos.x);
    boxSize.y = std::max(sPos.y, ePos.y) - std::min(sPos.y, ePos.y);

    auto body = ax::PhysicsBody::createBox(boxSize);
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);

    checknode->setPhysicsBody(body);

    // 체크노드 확인용
    auto dnode = ax::DrawNode::create();
    dnode->setName("drawCheckNode");
    dnode->setPosition(ax::Vec2(0, 0));
    checknode->addChild(dnode);
    dnode->drawRect(ax::Vec2(-boxSize.x / 2, -boxSize.y / 2), ax::Vec2(boxSize.x / 2, boxSize.y / 2),
                    ax::Color4B::BLACK);


    //위치 재조정
    ax::Vec2 nodepos;
    nodepos.x = (sPos.x - ePos.x) / 2;
    nodepos.y = (sPos.y - ePos.y) / 2;
    checknode->setPosition(nodepos);    
}

void CursorComp::DeleteCheckNode()
{
    
    //auto node = mDrawComp->mRoot->getChildByName("CursorCheckNode");

   /* if (node != nullptr)
    {
        node->getChildByName("drawCheckNode")->removeFromParent();
        node->removeFromParent();
    }*/
    
}

void CursorComp::GreenRectClear()
{
    ax::DrawNode* drawnode = (ax::DrawNode*)mActor->GetRoot()->getChildByName("GreenRect");
    drawnode->clear();
}

void CursorComp::CreateBuildingBP(BuildingName name)
{
    if (bp == nullptr)
    {
        switch (name)
        {
        case BuildingName::None:
            break;
        case BuildingName::CommandCenter:
            bp = ax::Sprite::create("123.png"sv);
            bp->setPosition(0, 0);
            mActor->GetRoot()->addChild(bp);
            break;
        default:
            break;
        }
    }
}


