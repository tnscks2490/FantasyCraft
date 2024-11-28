#pragma once
#include "IActorComp.h"

class Actor;

class CursorComp : public IActorComp
{
public:
    CursorComp(Actor* actor);
    ~CursorComp();

    Ptr<ax::Node> mRoot;
};
