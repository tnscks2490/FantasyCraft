#pragma once
#include "IActorComp.h"
#include "Actor.h"


class DrawComp : public IActorComp
{
public:
    DrawComp(Actor* actor);
    ~DrawComp();

    virtual void update(float delta) override;


    ax::Node* CreateRootNode();
    ax::Node* CreatePhysicsNode(ax::Vec2 bodysize);

public:
    Ptr<ax::Node> mRoot = nullptr;
};

