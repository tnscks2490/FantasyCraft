#pragma once
#include "PreDefines.h"
#include "Player.h"


class MiniMapLayer : public ax::Layer
{
public:
    CREATE_FUNC(MiniMapLayer);

    virtual bool init() override;
    void MessageProc(SystemMessage smsg);
    void update(float delta);

     Player* mPlayer = nullptr;
};


