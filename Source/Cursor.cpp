#include "pch.h"
#include "Cursor.h"



Cursor::Cursor(ax::Node* parent)
{
    CreateCursor(parent);
}

Cursor::~Cursor() {}

ax::Node* Cursor::CreateCursor(ax::Node* parent)
{
    // 루트 노드 만들기
    auto node = ax::Node::create();
    mRoot     = node;
    mRoot->setName("CursorRootNode");
    parent->addChild(mRoot.get());

    // 드래그 부분 그리기
    auto drawnode = ax::DrawNode::create();
    drawnode->setName("CursorDrawNode");
    drawnode->setOpacity(70);
    mRoot->addChild(drawnode);

   /* auto dragbody = ax::Node::create();
    dragbody->setName("CursorBN");
    auto ddbody     = ax::PhysicsBody::createBox(ax::Vec2(16, 16));
    ddbody->setContactTestBitmask(0xFFFFFFFF);
    ddbody->setDynamic(false);
    dragbody->setPhysicsBody(ddbody);*/

    // 커서스프라이트
    auto cursorSprite = ax::Sprite::create("Cursor.png"sv);
    cursorSprite->setName("CursorSpriteNode");
    mRoot->addChild(cursorSprite);


    return node;
}

ax::Node* Cursor::GetRoot()
{
    if (mRoot.get())
        return mRoot.get();
}

ax::DrawNode* Cursor::GetDrawNode()
{
    if (mRoot.get())
    {
        auto drawnode = (ax::DrawNode*)mRoot->getChildByName("CursorDrawNode");
        return drawnode;
    }
    return nullptr;
}

void Cursor::setPosition(ax::Vec2 pos)
{
    if (mRoot.get())
    {
        mRoot->setPosition(pos);
    }
}

void Cursor::CheckNodeInDrag()
{

    int sx = sPos.x / 16;
    int sy = sPos.y / 16;

    int ex = ePos.x / 16;
    int ey = ePos.y / 16;

    /*for (int i = std::min(sy, ey); i <= std::max(sy, ey); i++)
    {
        for (int j = std::min(sx, ex); j <= std::max(sx, ex); j++)
        {
            ax::Vec2 pos;
            pos.x = j * 16;
            pos.y = i * 16;

            CheckNode->setPosition(pos - mRoot->getPosition()); 
        }
    }
    CheckNode->setPosition(ax::Vec2::ZERO);*/

       // 드래그 속 체크 노드
    
    auto checknode = ax::Node::create();
    checknode->setName("CursorCheckNode");
    mRoot->addChild(checknode);

    ax::Vec2 boxSize;
    boxSize.x = std::max(sPos.x, ePos.x) - std::min(sPos.x, ePos.x);
    boxSize.y = std::max(sPos.y, ePos.y) - std::min(sPos.y, ePos.y);

    auto body = ax::PhysicsBody::createBox(boxSize);
    body->setContactTestBitmask(true);
    body->setDynamic(false);

    checknode->setPhysicsBody(body);

    // 체크노드 확인용
    auto dnode = ax::DrawNode::create();
    dnode->setName("drawCheckNode");
    dnode->setPosition(ax::Vec2(0, 0));
    checknode->addChild(dnode);
    dnode->drawRect(ax::Vec2(-boxSize.x / 2, -boxSize.y / 2), ax::Vec2(boxSize.x / 2, boxSize.y / 2),
                    ax::Color4B::BLACK);
    ax::Vec2 nodepos;
    nodepos.x = (sPos.x - ePos.x) / 2;
    nodepos.y = (sPos.y - ePos.y) / 2;
    // checknode->setAnchorPoint(ax::Vec2(0.f,0.f));
    checknode->setPosition(nodepos);    

}

void Cursor::DeleteCheckNode()
{
    ax::Node* node = nullptr;
    node           = mRoot->getChildByName("CursorCheckNode");

    if (node)
    {
        node->getChildByName("drawCheckNode")->removeFromParent();
        node->removeFromParent();
    }
    
}

