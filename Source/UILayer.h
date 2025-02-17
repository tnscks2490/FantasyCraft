#pragma once
#include "PreDefines.h"
#include "Player.h"
#include "MessageSystem.h"



class UILayer : public ax::Layer
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init() override;

    void MessageProc(SystemMessage smsg);

    void SetUI(PlayerRace race);
    void SetBuildButton();
    void SetCancelButton();
    void ButtonMessage(ax::Object* sender);
    void SetButton(ActorType type);
    void ReturnButton();
    void SetSCVButton();

    ax::Vec2 SetButtonPosition(int num);






    ax::MenuItemImage* CreateButton(ButtonType type);


public:
    ax::Sprite* mConsoleUI;
    ax::Sprite* mMineralIcon;
    ax::Sprite* mGasIcon;
    ax::Sprite* mPopIcon;

    ax::Menu* mMenu = nullptr;
    ButtonType buttons[9];


    Player* mPlayer = nullptr;
    Actor* mCursor  = nullptr;
   
};



