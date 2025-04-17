#pragma once
#include "PreDefines.h"
#include "Player.h"

class UILayer : public ax::Layer
{
public:
    CREATE_FUNC(UILayer);

    virtual bool init() override;

    void MessageProc(SystemMessage smsg);


    void StartSettingWithPlayer(Player* player);

    // 콘솔이미지 종족에 따라 변경
    void SetUI();



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


