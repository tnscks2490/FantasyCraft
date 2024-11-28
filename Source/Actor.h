#pragma once
#include "axmol.h"

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

public:

    short mID          = -1;
    char charNum     = 0;

    
public:
    // 컴포넌트
    MoveComp* mMoveComp = nullptr;
    DrawComp* mDrawComp = nullptr;


};

