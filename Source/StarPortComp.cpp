#include "pch.h"
#include "Actor.h"
#include "StarPortComp.h"
#include "DrawComp.h"

StarPortComp::StarPortComp(Actor* actor) : UnitComp(actor)
{

}

StarPortComp::~StarPortComp() {}

void StarPortComp::MessageProc(ActorMessage& msg) {}

void StarPortComp::update(float delta) {}
