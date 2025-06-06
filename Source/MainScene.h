/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "World.h"
#include "JPSPathFinder.h"
#include "PreDefines.h"
#include "MapLayer.h"
#include "UI/UILayer.h"


class MainScene : public ax::Scene
{
    typedef std::vector<TileNode*> TileList;
    enum class GameState
    {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };
    
public:
    bool init() override;
    void update(float delta) override;

    // mouse
    void onMouseDown(ax::Event* event);
    void onMouseUp(ax::Event* event);
    void onMouseMove(ax::Event* event);
    void onMouseScroll(ax::Event* event);

    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event* event);
    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event* event);

    // Contact
    bool onContactBegin(ax::PhysicsContact& contact);
    bool onContactPreSolve(ax::PhysicsContact& contact, ax::PhysicsContactPreSolve& solve);
    void onContactSeparate(ax::PhysicsContact& contact);
    // a selector callback
    void menuCloseCallback(ax::Object* sender);

    void DebugPath();

    void FirstObjectSetting();
    
    void Decording();

    void ScreenMove(float delta);
    void SetScreenPos(ax::Vec2 layerPos);

    //여기는 테스트용

    void TestFunc(ax::Node* node);







    float mTimer = 0.f;
    float ScreenMoveTimer = 0.f;

public:
    TcpClient* mClient = nullptr;
    World* mWorld      = nullptr;


    UILayer* mUILayer = nullptr;
    MapLayer* mMapLayer = nullptr;

    ax::TMXTiledMap* Map = nullptr;

    Player* mPlayer      = nullptr;
    Actor* mCursor = nullptr;

    
public:
    //Scene의 고정 값들
    
    // init() 때 값을 넣어줌
    ax::Vec2 visibleSize;



    // 총 타일의 갯수 각 타일별 32 x 32 픽셀이다

    int selectidx = -1;

private:
    GameState _gameState = GameState::init;
};

#endif  // __MAIN_SCENE_H__
