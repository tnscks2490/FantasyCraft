#include "pch.h"
#include "UI/MiniMapLayer.h"

bool MiniMapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    setName("MiniMapLayer");
    return true;
}

void MiniMapLayer::MessageProc(SystemMessage smsg) {}

void MiniMapLayer::update(float delta) {}
