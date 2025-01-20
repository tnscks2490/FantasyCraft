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

    void CursorUp();
    void BPFollowCursor();

    void CursorMove(ax::Vec2 pos);
    void LeftClick(ax::Vec2 pos);
    void RightClick(ax::Vec2 pos);

public:
    void CheckNodeInDrag();
    void DeleteCheckNode();

    void GreenRectClear();


    void LeftClickUp()  { isLeftClick = false;  }
    void RightClickUp() { isRightClick = false; }
    void LeftClickDown() { isLeftClick = true; }
    void RightClickDown() { isRightClick = true; }

    void ReleaseSp() { if (sp)sp->removeFromParent();sp = nullptr; }

    void CreateBuildingBluePrint(BuildingName name);

public:

    Player* cPlayer = nullptr;

    ax::Sprite* sp = nullptr;

    ax::Vec2 sPos;
    ax::Vec2 ePos;

    bool isDraging = false;
    bool isLeftClick = false;
    bool isRightClick = false;

    bool OnContactTeam = false;
    bool OnContactEnemy = false;

    CursorState mState = CursorState::Idle;
};
