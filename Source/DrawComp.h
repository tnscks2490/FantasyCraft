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


    ax::Node* CreateRootNode();
    ax::Node* CreatePhysicsNode(ax::Vec2 bodysize);
    ax::Node* CreateAnimNode(ECharName name, std::string_view nodeName = "Anim");
    ax::Node* CreateSelectedNode();

    void ChangeAnim(ECharName Name, ECharAct action, ECharDir dir);
    ECharDir CalcAniDir(ax::Vec2 mVelocity);

    float Timer = 0.f;
    //TODO:추후에 수정할것 생성하는 액터에 따라서
    ECharName mCurAnim  = ECharName::Marin;
    ECharAct mCurAction = ECharAct::Idle;
    ECharDir mCurDir    = ECharDir::S;


    void isSelected();

    bool selected = false;


public:
    Ptr<ax::Node> mRoot = nullptr;
};

