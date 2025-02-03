#pragma once
#include "AnimInfo.h"
#include "SensorMemory.h"

class MoveComp;
class DrawComp;
class UnitComp;
class GoalComp;
class ProjectileComp;
class CursorComp;
class PK_Data;


enum class ActorType
{
    None,
    Cursor,
    SCV,
    Marine,
};



class Actor
{
public:
    Actor();
    Actor(PK_Data data);
    ~Actor();

    void update(float delta);


    ax::Node* GetRoot();
    void SetPosition(ax::Vec2 pos);
    ax::Vec2 GetPosition();
    ax::Vec2 GetVelocity();

public:

    short mID        = -1;
    char charNum     = 0;
    short idx        = -1;

    bool isDead = false;
    
public:
    // 컴포넌트
    MoveComp* mMoveComp = nullptr;
    DrawComp* mDrawComp = nullptr;
    UnitComp* mUnitComp = nullptr;
    GoalComp* mGoalComp = nullptr;
    //////////////
    CursorComp* mCursorComp = nullptr;

    SensorMemory* mSM = nullptr;

public:
    ActorType mActorType = ActorType::None;

};

