#pragma once
#include "PreDefines.h"
#include "Player.h"


class UnitInfoLayer : public ax::Layer
{
public:
    CREATE_FUNC(UnitInfoLayer);

    virtual bool init() override;
    virtual void update(float delta) override;

    void MessageProc(SystemMessage smsg);

    void SwitchSelectUI(bool isMulti);

    void MultiSelected(SystemMessage smsg);
    void SingleSelected(SystemMessage smsg);


    //// singleSelect 하나에 대한 함수
    void showUnitInfoUI(Actor* actor);
    void showUnitWire(Actor* actor);
    void showStatus(Actor* actor);
    void showUpgrade(Actor* actor);
    void showName(Actor* actor);
    //////////////////////////////////



    void showBuildingConstructionUI();
    void showProductionQueueUI();

    ax::Node* CreateLoadNode(ECharName name, ECharAct action, ECharDir dir,
                             std::string_view nodeName = "LoadBar");

    void ChangeLoadBar(int idx, bool isEmpty);
    void ShowCreatingUnit(ActorType type);


public:
    Player* mPlayer = nullptr;

    ax::Node* mMultiSelect = nullptr;
    ax::Node* mSingleSelect = nullptr;

    ax::Node* mLoadBar = nullptr;


    float mTimer = 0.f;
    float mCurLoadTime = 0.f;
    float mMaxLoadTime = 0.f;
    float mFrame       = 0.f;
    int mLoadIdx       = 0;
    bool isLoad  = false;
};


