#pragma once
#include "PreDefines.h"
#include "Player.h"


class CommandLayer : public ax::Layer
{
public:
    CREATE_FUNC(CommandLayer);

    virtual bool init() override;
    virtual void update(float delat) override;


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

    void SingleSelected(SystemMessage smsg);
    void MultiSelected(SystemMessage smsg);


public:
    Player* mPlayer = nullptr;

    Actor* mActor      = nullptr;
    Actor* mActors[12] = {nullptr};

    ButtonType mCurbuttons[MAX_BUTTON];
    ButtonType mSavebuttons[MAX_BUTTON];

    ActorType mCurActorType;
    ActionState mCurActionState = ActionState::Idle;
    ActionState mCurActorState = ActionState::Idle;
    ax::Menu* mMenu = nullptr;


};


