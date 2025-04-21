#pragma once
#include "PreDefines.h"
#include "Player.h"

enum class LayerState
{
    None,
    Idle,
    Build,
    CreateUnit,
    Upgrade,
    MultiSelect,

};



class UnitInfoLayer : public ax::Layer
{
public:
    CREATE_FUNC(UnitInfoLayer);

    virtual bool init() override;
    virtual void update(float delta) override;

    void MessageProc(SystemMessage smsg);


    void MultiSelected(SystemMessage smsg);
    void SingleSelected(SystemMessage smsg);



    // 이름은 상시 표기
 

    void ChangeLayerState(LayerState cState);
    ax::SpriteFrame* FindWireFrame(Actor* actor);
    ax::SpriteFrame* FindATUpgradeSprite(Actor* actor);
    ax::SpriteFrame* FindDFUpgradeSprite(Actor* actor);


    // UnitInfoLayer에 출력되는 값들을 재설정해줌
    void resetInfoData(Actor* actor);











    ax::Node* CreateLoadNode(ECharName name, ECharAct action, ECharDir dir,
                             std::string_view nodeName = "LoadBar");

    void ChangeLoadBar(int idx, bool isEmpty);

    void AllNodeUnVisible();

public:
    LayerState mCurState = LayerState::None;




    /////////////////////////////////////////////
    Player* mPlayer = nullptr;

    // 다중선택 이미지 넣는 노드
    ax::Node* mMultiSelect = nullptr;

    Actor* mActor = nullptr;
    Actor** mActors;


    float mTimer = 0.f;
    float mCurLoadTime = 0.f;
    float mMaxLoadTime = 0.f;
    float mFrame       = 0.f;
    int mLoadIdx       = 0;

    int mMaxHP = 0;
    int mCurHP = 0;


    ax::Label* mName  = nullptr;
    ax::Sprite* mWire = nullptr;
    ax::Label* mHP    = nullptr;
    ax::Node* mLoadBar = nullptr;
    ax::Sprite* mATUpgrade = nullptr;
    ax::Sprite* mDFUpgrade = nullptr;
    ax::Sprite* mUnitList  = nullptr;
    ax::Sprite* mUpgradeSprite = nullptr;
    
    
};


