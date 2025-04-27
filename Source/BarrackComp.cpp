#include "pch.h"
#include "Actor.h"
#include "BarrackComp.h"
#include "DrawComp.h"

BarrackComp::BarrackComp(Actor* actor) :UnitComp(actor) {}

BarrackComp::~BarrackComp() {}

void BarrackComp::MessageProc(ActorMessage& msg) {}

void BarrackComp::update(float delta) {}
