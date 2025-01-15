#include "pch.h"
#include "Cursor.h"
#include "PrePacket.h"
#include "DrawComp.h"


Cursor::Cursor(ax::Node* parent)
{
    CreateCursor(parent);
}

Cursor::~Cursor() {}

ax::Node* Cursor::CreateCursor(ax::Node* parent)
{
    Actor* actor = new Actor;
    actor->mActorType = ActorType::Cursor;
    actor->mID        = TcpClient::get()->GetID();

    auto draw = new DrawComp(actor);

    auto node = draw->CreateRootNode();
    parent->addChild(node, 100.0f);

    auto body = draw->CreatePhysicsNode(ax::Vec2(16, 16));
    auto anim = draw->CreateAnimNode(ECharName::Cursor, ECharAct::Idle, ECharDir::Face, "Anim");

    // 드래그 부분 그리기
    auto drawnode = ax::DrawNode::create();
    drawnode->setName("CursorDrawNode");
    drawnode->setOpacity(70);
    node->addChild(drawnode);

    return node;
}

ax::DrawNode* Cursor::GetDrawNode()
{
   /* if (mDrawComp->mRoot->isNotNull())
    {
        auto drawnode = (ax::DrawNode*)mRoot->getChildByName("CursorDrawNode");
        return drawnode;
    }*/
    return nullptr;
}

void Cursor::update(float delta)
{
    if (sp != nullptr)
    {
        //BPFollowCursor();
    }
}

void Cursor::CursorUp()
{

    GetDrawNode()->clear();
    CheckNodeInDrag();
    isDraging = false;
}

void Cursor::BPFollowCursor()
{
   /* ax::Vec2 pos;
    pos.x = mRoot->getPosition().x / 32;
    pos.y = mRoot->getPosition().y / 32;
    sp->setPosition(pos*32);*/
}

void Cursor::CursorMove(ax::Vec2 pos)
{
    mDrawComp->mRoot->setPosition(pos);
}

void Cursor::LeftClick(ax::Vec2 pos)
{
    if (sp)
    {
        if (cPlayer->PlayerActors.size() == 1)
        {
            cPlayer->mMainActor = cPlayer->PlayerActors[0];

            PK_Data data;
            data.ClientID = TcpClient::get()->GetID();
            data.input    = 10;
            data.pos      = sPos;
            TcpClient::get()->SendMessageToServer(data);

            ReleaseSp();
        }
    }
}

void Cursor::RightClick(ax::Vec2 pos) {}


void Cursor::CheckNodeInDrag()
{

    int sx = sPos.x / 16;
    int sy = sPos.y / 16;

    int ex = ePos.x / 16;
    int ey = ePos.y / 16;

    // 드래그 속 체크 노드
    
    auto checknode = ax::Node::create();
    checknode->setName("CursorCheckNode");
    mDrawComp->mRoot->addChild(checknode);

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

void Cursor::DeleteCheckNode()
{
    
    auto node = mDrawComp->mRoot->getChildByName("CursorCheckNode");

    if (node != nullptr)
    {
        node->getChildByName("drawCheckNode")->removeFromParent();
        node->removeFromParent();
    }
    
}

void Cursor::CreateBuildingBluePrint(BuildingName name)
{
    if (sp == nullptr)
    {
        switch (name)
        {
        case BuildingName::None:
            break;
        case BuildingName::CommandCenter:
            sp = ax::Sprite::create("123.png"sv);
            sp->setPosition(0, 0);
            mDrawComp->mRoot->addChild(sp);
            break;
        default:
            break;
        }
    }
    
}

