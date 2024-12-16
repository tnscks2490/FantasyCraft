#include "pch.h"
#include "UILayer.h"



bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    mUISprite = ax::Sprite::create("tconsole.png"sv);
    addChild(mUISprite);
    return true;
}
