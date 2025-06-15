#pragma once
#include "IActorComp.h"
#include "Actor.h"
#include "AnimInfo.h"

class DrawComp : public IActorComp
{
public:
    DrawComp(Actor* actor);
    ~DrawComp();

    virtual void update(float delta) override;

    ax::Vec2 GetBodySize() { return mBodySize; }


    ax::Node* CreateRootNode();
    ax::Node* CreatePhysicsNode(ax::Vec2 bodysize);

    ax::Node* CreateBPPhysicsNode(ax::Vec2 bodysize);
    ax::Node* Create_Small_BPPhysicsNode();
    ax::Node* Create_Middle_BPPhysicsNode();
    ax::Node* Create_Big_BPPhysicsNode();
    ax::Node* Create_Refinery_BPPhysicsNode();

    ax::Node* CreateAnimNode(ECharName name, std::string_view nodeName = "Anim");
    ax::Node* CreateAnimNode(ECharName name, ECharAct action, ECharDir dir,
                             std::string_view nodeName = "Effect");
   
    ax::Node* CreateAnimNodeByIndex(ECharName name, int idx, std::string_view nodeName = "Anim");
    ax::Node* CreateAnimNodeByIndex(ECharName name, ECharAct action, int idx, std::string_view nodeName = "Anim");
    ax::Node* CreateDeathAnim(ECharName name, std::string_view nodeName = "Anim");

    ax::Node* CreateSelectedNode(ax::Vec2 bodySize);
    ax::Node* CreateHPBarByIndex(ECharName name, int idx, std::string_view nodeName = "HpBar");
    
    ax::Node* CreateDemageNode(ActorType type);
    ax::Node* CreateGatheringNode(ActorType type);

    ax::Node* CreateCarryMineral();
    ax::Node* CreateCarryGas();


    ax::Vec2 GetCarryItemPos(ECharDir dir);

    void RemoveCarryItem();
    void RemoveGatherAnim();


    ax::Node* CreateCursorRect(ax::Vec2 sPos, ax::Vec2 ePos);
    void ChangeRectSize(ax::Vec2 ePos);

    void AddUserData();


    void ChangeAnim(ECharName Name, ECharAct action, ECharDir dir, bool repeat = true);
    void ChangeAnimDeath(ECharName Name);
    void ChangeAnimByIndex(ECharName Name, ECharAct action, ECharDir dir,int idx);
    void ChangeHpBarByIndex(ECharName Name, int idx);
    void ChangePhysicsNodeTag(int tagNum);


    ECharDir CalcAniDir(ax::Vec2 mVelocity);

    void ChangeCurDir(ax::Vec2 mTargetDir);


public:

    //TODO:추후에 수정할것 생성하는 액터에 따라서
    AnimInfo* mCurAnimInfo   = nullptr;
    ECharDir mCurDir         = ECharDir::S;
    ActionState mActionState = ActionState::Idle;

    void isSelected();

    bool selected = false;
    float Timer = 0.f;

    bool isCarryItme = false;

    ax::Vec2 mBodySize;

    int idx = 0;

public:
    Ptr<ax::Node> mRoot = nullptr;
};

