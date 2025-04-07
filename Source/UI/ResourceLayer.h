#pragma once
#include "PreDefines.h"
#include "Player.h"


class ResourceLayer : public ax::Layer
{
public:
    CREATE_FUNC(ResourceLayer);

    virtual bool init() override;

    void MessageProc(SystemMessage smsg);
    void update(float delta);


    ax::Sprite* mMineralIcon;
    ax::Sprite* mGasIcon;
    ax::Sprite* mPopIcon;
};


