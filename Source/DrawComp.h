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
    ax::Node* CreateAnimNode(ECharName name,ECharAct action, ECharDir dir);


    void ChangeAnim(AnimInfo* info);

public:
    Ptr<ax::Node> mRoot = nullptr;
};

