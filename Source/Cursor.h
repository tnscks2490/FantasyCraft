#pragma once
#include "PreDefines.h"

class Cursor 
{
public:
    Cursor(ax::Node* parent);
    ~Cursor();

    ax::Node* CreateCursor(ax::Node* parent);
    ax::Node* GetRoot();
    ax::Vec2 GetPosition();
    ax::DrawNode* GetDrawNode();

    

public:
    void setPosition(ax::Vec2 pos);
    void CheckNodeInDrag();
    void DeleteCheckNode();

public:
    Ptr<ax::Node> mRoot;

    ax::Vec2 sPos;
    ax::Vec2 ePos;

    bool isDraging = false;
};
