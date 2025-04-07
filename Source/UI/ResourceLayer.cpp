#include "pch.h"
#include "UI/ResourceLayer.h"

bool ResourceLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    setName("ResourceLayer");

    return true;
}

void ResourceLayer::MessageProc(SystemMessage smsg) {}

void ResourceLayer::update(float delta) {}
