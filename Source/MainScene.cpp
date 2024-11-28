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

#include "pch.h"
#include "MainScene.h"
#include "TcpClient.h"
#include "Actor.h"
#include "MoveComp.h"
#include "PathFind.h"
#include "TileNode.h"


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
    mPath            = new PathFind(width, height);

    //콘솔창에 이동가는 한 곳 띄우는 디버깅용 코드
    /*for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", mPath->mColMap->IsCollision(j, i));
        }
        printf("\n");
    }*/

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

    //mCursor = ax::Node::create();
    //mCursor->setPosition(500, 500);

    Map = ax::TMXTiledMap::create("Map/python/python.tmx");
    addChild(Map);

    auto wall = Map->getLayer("MetaInfo");

    SetTileNodes();
    OnOffTile();


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto t = wall->getTileAt(ax::Vec2(j, height - 1 - i));
            if (t)
            {
                auto value = wall->getProperty("Wall");
                if (value.asBool())
                    mTileList[i * width + j]->ChangeDrawNode();
            }
        }
    }











    // window화면 테두리 표기
    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);
    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4B::BLUE);

    scheduleUpdate();

    return true;
}


void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    ax::Vec2 mousePos = ax::Vec2(e->getCursorX(), e->getCursorY());


    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        if (player)
        {
            PK_Data data;
            data.ClientID = TcpClient::get()->GetID();
            data.input    = 'r';
            data.pos      = mousePos;
            TcpClient::get()->SendActorMessage(data);
        }
    }
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    ax::Vec2 pos;
    pos.x = e->getCursorX();
    pos.y = e->getCursorY();
    //mCursor->setPosition(pos);

}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    if (code == ax::EventKeyboard::KeyCode::KEY_P)
        getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

     if (code == ax::EventKeyboard::KeyCode::KEY_T)
    {
        TileOn = !TileOn;
        OnOffTile();

        if (!TileOn)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (mTileList[i * width + j]->IsPass == true)
                        mPath->mColMap->ClrAt(j, i);
                    else
                        mPath->mColMap->SetAt(j, i);
                }
            }
            ///////////////////////////////////
            for (int i = height - 1; i >= 0; i--)
            {
                for (int j = 0; j < width; j++)
                {
                    printf("%d ", mPath->mColMap->IsCollision(j, i));
                }
                printf("\n");
            }
        }
    }

    switch (code)
    {
    case ax::EventKeyboard::KeyCode::KEY_C:
        if (!player)
        {
            PK_Data data;
            data.ClientID = TcpClient::get()->GetID();
            data.pos      = Vec2(500, 500);
            data.input    = 77;
            TcpClient::get()->SendActorMessage(data);
        }
        break;
    default:
        break;
    }

    World::get()->PrintActorList();
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    
}

void MainScene::update(float delta)
{
    

    //ScreenMove(delta);


    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;
        break;
    }
    case GameState::update:
    {

        timeval timeout = {0, 0};
        if (TcpClient::get() && TcpClient::get()->Select(timeout))
        {
            if (TcpClient::get()->RecvData())
            {
                Decording();
            }
        }
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

void MainScene::Decording()
{
    char buf[1024] = {0};
    bool check     = true;
    int Idx        = 0;
    short Len      = 0;

    while (check)
    {

        PK_Head haed;
        PK_Data data;

        memcpy(&haed, TcpClient::get()->mRecvBuf + Idx, sizeof(PK_Head));
        Idx += sizeof(PK_Head);

        if (haed.dataLen == 0)
        {
            for (int i = 0; i < Idx - 3; i++)
            {
                TcpClient::get()->mRecvBuf[i] = 0;
            }
            check = false;
            continue;
        }

        memcpy(&data, TcpClient::get()->mRecvBuf + Idx, sizeof(PK_Data));
        Idx += sizeof(PK_Data);

        switch (data.input)
        {
        case 77:
        case 78:
        case 79:
        {

            if (player == nullptr && data.ClientID == TcpClient::get()->GetID())
            {
                Actor* actor = World::get()->CreateActor(this,data);
                player       = actor;
            }
            if (player)
            {
                bool check = false;
                for (auto actor : World::get()->w_ActorList)
                {
                    if (actor && actor->mID == data.ClientID)
                    {
                        check = true;
                    }
                }
                if (!check)
                {
                    Actor* actor = World::get()->CreateActor(this, data);
                    PK_Data d;
                    d.ClientID = TcpClient::get()->GetID();
                    d.input    = player->charNum;
                    d.pos      = player->GetRoot()->getPosition();
                    TcpClient::get()->SendActorMessage(d);
                }
            }
        }
        break;
        case 90:
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    actor->mMoveComp->SetPath(PathSearch(data.pos));
                }
            }
        }
            break;
        /*case 108:
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    Actor* pro = CreateActor(data);
                    pro->mMoveComp->SetTarget(data.pos);
                }
            }
        }
        break;*/
        case 114:
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    actor->mMoveComp->SetPath(PathSearch(data.pos));
                }
            }
            break;
        ///////////////////////
        default:
            break;
        }
    }
}

void MainScene::SetTileNodes()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            TileNode* mTileNode = TileNode::CreateTileNode(this);
            ax::Vec2 pos(8 + 16 * j, 8 + 16 * i);
            mTileNode->idx = i * width + j;
            mTileNode->SetPosition(pos);
            mTileList.push_back(mTileNode);
        }
    }
}

void MainScene::OnOffTile()
{
    for (auto tile : mTileList)
    {
        tile->mRoot->setVisible(TileOn);
    }
}

std::list<jpspath::Coord> MainScene::PathSearch(ax::Vec2 targetPos)
{
    std::list<jpspath::Coord> ResultNodes;
    jpspath::Path jps;
    jps.Init(mPath->mColMap);

    int32_t sx = player->GetRoot()->getPosition().x / 16;
    int32_t sy = player->GetRoot()->getPosition().y / 16;
    int32_t ex = targetPos.x / 16;
    int32_t ey = targetPos.y / 16;

    jps.Search(sx, sy, ex, ey, ResultNodes);
    return ResultNodes;
}

void MainScene::ScreenMove(float delta)
{
   // mCursorPos = mCursor->getPosition();

    //mTimer += delta;

    ax::Vec2 mapPos = Map->getPosition();
    if (mCursorPos.x > 1232)
    {
        mapPos.x -= 32;
        Map->setPosition(mapPos);
    }
    else if (mCursorPos.x < 48)
    {
        mapPos.x += 32;
        Map->setPosition(mapPos);
    }
    else if (mCursorPos.y > 672)
    {
        mapPos.y -= 32;
        Map->setPosition(mapPos);
    }
    else if (mCursorPos.y < 48)
    {
        mapPos.y += 32;
        Map->setPosition(mapPos);
    }
    
}


