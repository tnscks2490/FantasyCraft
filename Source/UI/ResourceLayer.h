#pragma once
#include "PreDefines.h"
#include "Player.h"


class ResourceLayer : public ax::Layer
{
public:
    CREATE_FUNC(ResourceLayer);

    virtual bool init() override;

    void MessageProc(SystemMessage smsg);
    virtual void update(float delta) override;

    void updateResource();
    void SetNumText();

public:

    Player* mPlayer = nullptr;

    ax::Sprite* mMineralIcon = nullptr;
    ax::Sprite* mGasIcon = nullptr;
    ax::Sprite* mPopIcon = nullptr;

    ax::Label* mMineralNum = nullptr;
    ax::Label* mGasNum     = nullptr;
    ax::Label* mPopNum     = nullptr;

};


