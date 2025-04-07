#pragma once
#include "PreDefines.h"
#include "Player.h"

class UILayer : public ax::Layer
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init() override;

    void MessageProc(SystemMessage smsg);

    // 콘솔이미지 종족에 따라 변경
    void SetUI(PlayerRace race);
    void ButtonMessage(ax::Object* sender);


    void SetButton(ActorType type);
    void ReturnButton();
    void ClearSaveButtons();


    void SetUnitControlButton(ActorType Atype);

    void SetCBButton();
    void SetABButton(); 


    ax::Vec2 SetButtonPosition(int num);
    ax::MenuItemImage* CreateAddButton(ButtonType type);







public:
    ax::Sprite* mConsoleImage;

    //지워야함
    ax::Node* BottomUI  = nullptr;
    //////////////////////////////

    ButtonType mCurbuttons[MAX_BUTTON];
    ButtonType mSavebuttons[MAX_BUTTON];
    
    ActorType mCurActorType;
    Player* mPlayer = nullptr;
    Actor* mCursor  = nullptr;
};


