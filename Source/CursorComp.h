#pragma once
#include "IActorComp.h"
#include "Actor.h"
#include "Player.h"

enum class CursorState
{
    None,
    Idle,
    Drag,
    Move,
    Click,
    BluePrint,
    ContactTeam,
    ContactEnemy,
    Target,


};

enum class BuildingName
{
    None,
    CommandCenter,

};

class CursorComp : public IActorComp
{
public:
    CursorComp(Actor* actor);
    ~CursorComp();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg);

    void CursorUp();
    void BPFollowCursor();

    void CursorMove(ax::Vec2 pos);
    void LClick(ax::Vec2 pos);
    void RClick(ax::Vec2 pos);


    void ContactedUnit(ActorMessage& msg);
    void SeparateUnit(ActorMessage& msg);

public:
    void CheckNodeInDrag();
    void DeleteCheckNode();

    void GreenRectClear();


    void LeftClickUp()  { isLeftClick = false;  }
    void RightClickUp() { isRightClick = false; }
    void LeftClickDown() { isLeftClick = true; }
    void RightClickDown() { isRightClick = true; }

    void ReleaseBP();

    void CreateBuildingBP(BuildingName name);

public:

    Player* cPlayer = nullptr;

    Actor* mBP = nullptr;

    ax::Vec2 sPos;
    ax::Vec2 ePos;

    bool isDraging = false;
    bool isLeftClick = false;
    bool isRightClick = false;

    bool OnContactTeam = false;
    bool OnContactEnemy = false;

    CursorState mState = CursorState::Idle;
};
