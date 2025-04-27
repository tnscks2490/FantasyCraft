#include "pch.h"
#include "Actor.h"
#include "AcademyComp.h"
#include "DrawComp.h"

AcademyComp::AcademyComp(Actor* actor) :UnitComp(actor) {}

AcademyComp::~AcademyComp() {}

void AcademyComp::MessageProc(ActorMessage& msg) {}

void AcademyComp::update(float delta) {}
