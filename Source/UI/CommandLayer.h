#pragma once
#include "PreDefines.h"
#include "Player.h"


class CommandLayer : public ax::Layer
{
public:
    CREATE_FUNC(CommandLayer);

    virtual bool init() override;
    void MessageProc(SystemMessage smsg);

    void ButtonMessage(ax::Object* sender);

    void SetButton(Actor* actor);
    void ReturnButton();
    void ClearSaveButtons();

    void SetUnitControlButton(Actor* actor);

    void SetCBButton();
    void SetABButton(); 

    ax::Vec2 SetButtonPosition(int num);
    ax::MenuItemImage* CreateAddButton(ButtonType type);

    Player* mPlayer = nullptr;



    ButtonType mCurbuttons[MAX_BUTTON];
    ButtonType mSavebuttons[MAX_BUTTON];

    ActorType mCurActorType;
    ax::Menu* mMenu = nullptr;
};


