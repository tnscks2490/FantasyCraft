#include "pch.h"
#include "UI/UnitInfoLayer.h"

bool UnitInfoLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    setName("UnitInfoLayer");


    scheduleUpdate();

    return true;
}

void UnitInfoLayer::MessageProc(SystemMessage smsg) {}

void UnitInfoLayer::update(float delta) {}
