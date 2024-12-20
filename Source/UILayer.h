#pragma once
#include "PreDefines.h"
#include "Player.h"


class UILayer : public ax::Layer
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init() override;

    void SetUI(PlayerRace race);



public:
    ax::Sprite* mConsoleUI;
    ax::Sprite* mMineralIcon;
    ax::Sprite* mGasIcon;
    ax::Sprite* mPopIcon;



    Player* mPlayer = nullptr;
};
