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

#include "MainScene.h"
#include "TcpClient.h"


using namespace ax;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initPhysicsWorld())
    {
        return false;
    }
 
    TcpClient::get();


    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;    

    // touch Listner::PC전용이므로 필요없음
    //auto touchListener = EventListenerTouchAllAtOnce::create();
    //touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    //touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    //touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto mouseListener           = EventListenerMouse::create();
    mouseListener->onMouseMove   = AX_CALLBACK_1(MainScene::onMouseMove, this);
    mouseListener->onMouseUp     = AX_CALLBACK_1(MainScene::onMouseUp, this);
    mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener           = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed  = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);


    // window화면 테두리 표기
    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);
    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4B::BLUE);

    scheduleUpdate();

    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
   
}

void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
  
}

void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta)
{
    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;
        break;
    }
    case GameState::update:
    {
        //timeval timeout = {0, 0};
        //if (TcpClient::get() && TcpClient::get()->Select(timeout))
        //{
        //    if (TcpClient::get()->RecvData())
        //    {
        //        Decording();
        //    }
        //}

        //// 받아온 데이터를 토대로 함수 실행
        //for (auto actor : mActorList)
        //{
        //    if (actor)
        //        actor->update(delta);
        //}

        //for (auto actor : mPJList)
        //{
        //    if (actor)
        //    {
        //        actor->update(delta);
        //    }
        //    // 투사체 액터 삭제하기
        //    // 나중에 꼭 수정할것
        //    /* if (actor->mRoot->isVisible() == false)
        //     {
        //         delete actor->mMoveComp;
        //         delete actor->mPJComp;
        //         actor->mRoot->removeFromParent();
        //         actor = nullptr;
        //     }*/
        //}
        break;
    }
    case GameState::pause: { break; }
    case GameState::menu1: { break; }
    case GameState::menu2: { break; }
    case GameState::end:
    { 
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }
    } 
}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}

//void MainScene::Decording()
//{
//    char buf[1024] = {0};
//    bool check     = true;
//    int Idx        = 0;
//    short Len      = 0;
//
//    while (check)
//    {
//
//        PK_Head haed;
//        PK_Data data;
//
//        memcpy(&haed, TcpClient::get()->mRecvBuf + Idx, sizeof(PK_Head));
//        Idx += sizeof(PK_Head);
//
//        if (haed.dataLen == 0)
//        {
//            for (int i = 0; i < Idx - 3; i++)
//            {
//                TcpClient::get()->mRecvBuf[i] = 0;
//            }
//            check = false;
//            continue;
//        }
//
//        memcpy(&data, TcpClient::get()->mRecvBuf + Idx, sizeof(PK_Data));
//        Idx += sizeof(PK_Data);
//
//        switch (data.input)
//        {
//        case 77:
//        case 78:
//        case 79:
//        {
//
//            if (mPlayActor == nullptr && data.ClientID == TcpClient::get()->GetID())
//            {
//                Actor* actor = CreateActor(data);
//                mPlayActor   = actor;
//            }
//            if (mPlayActor)
//            {
//                bool check = false;
//                for (auto actor : mActorList)
//                {
//                    if (actor && actor->mID == data.ClientID)
//                    {
//                        check = true;
//                    }
//                }
//                if (!check)
//                {
//                    Actor* actor = CreateActor(data);
//                    PK_Data d;
//                    d.ClientID = TcpClient::get()->GetID();
//                    d.input    = mPlayActor->charNum;
//                    d.pos      = mPlayActor->sprite->getPosition();
//                    TcpClient::get()->SendActorMessage(d);
//                }
//            }
//        }
//        break;
//        case 108:
//        {
//            for (auto actor : mActorList)
//            {
//                if (actor && actor->mID == data.ClientID)
//                {
//                    Actor* pro = CreateActor(data);
//                    pro->mMoveComp->SetTarget(data.pos);
//                }
//            }
//        }
//        break;
//        case 114:
//            for (auto actor : mActorList)
//            {
//                if (actor && actor->mID == data.ClientID)
//                {
//                    actor->mMoveComp->SetPath(PathSearch(data.pos));
//                }
//            }
//            break;
//        ///////////////////////
//        default:
//            break;
//        }
//    }
//}
