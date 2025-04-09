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


    Player* mPlayer = nullptr;

    ax::Node* mMultiSelect = nullptr;
    ax::Node* mSingleSelect = nullptr;
};


