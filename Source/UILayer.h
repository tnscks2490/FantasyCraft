#pragma once
#include "PreDefines.h"


class Player;

class UILayer : public ax::Layer
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init() override;



public:
    ax::Sprite* mUISprite;


    Player* mPlayer = nullptr;
};
