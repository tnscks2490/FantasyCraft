#pragma once
#include "axmol.h"
#include "AnimInfo.h"

class MoveComp;
class DrawComp;
class ProjectileComp;


class Actor
{
public:
    Actor();
    ~Actor();

    void update(float delta);


    ax::Node* GetRoot();
    ax::Vec2 GetVelocity();

public:

    short mID        = -1;
    char charNum     = 0;

    
public:
    // 컴포넌트
    MoveComp* mMoveComp = nullptr;
    DrawComp* mDrawComp = nullptr;


    


};

