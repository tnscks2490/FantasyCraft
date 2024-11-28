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
    ax::Node* CreateAnimNode(ECharName name);


    void ChangeAnim(ECharName Name, ECharAct action, ECharDir dir);
    ECharDir CalcAniDir(ax::Vec2 mVelocity);

    float Timer = 0.f;
    ECharDir dir = ECharDir::Face;

public:
    Ptr<ax::Node> mRoot = nullptr;
};

