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
#include "Player.h"


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

    auto contactListener               = EventListenerPhysicsContact::create();
    contactListener->onContactBegin    = AX_CALLBACK_1(MainScene::onContactBegin, this);
    contactListener->onContactSeparate = AX_CALLBACK_1(MainScene::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    //mCursor = ax::Node::create();
    //mCursor->setPosition(500, 500);

    Map = ax::TMXTiledMap::create("Map/python/python.tmx");
    addChild(Map);

    mPath     = new PathFind(width, height);

    auto wall = Map->getLayer("MetaInfo");
    mPath->DefaultSetting(wall);
    
    mPlayer   = new Player;


    mCursor = ax::Node::create();
    addChild(mCursor);


    //커서 이미지
    auto sprite = ax::Sprite::create("Cursor.png"sv);
    mCursor->addChild(sprite);

    // 드래그용
    DragNode = ax::DrawNode::create();
    DragNode->setOpacity(100);

    auto body = ax::PhysicsBody::createBox(ax::Vec2(100,100));
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);
    DragNode->setPhysicsBody(body);
    addChild(DragNode);
    //mCursor->addChild(DragNode);



    testdraw = DrawNode::create();
    testdraw->setPosition(ax::Vec2(0,0));
    DragNode->addChild(testdraw);
    testdraw->drawRect(ax::Vec2(-25, -25), ax::Vec2(25, 25), Color4B::BLACK);

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
    else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        isDraging = true;
        Spos      = mousePos;
        DragNode->setPosition(Spos);
    }
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    ax::Vec2 mousepos;
    mousepos.x = e->getCursorX();
    mousepos.y = e->getCursorY();

    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        isDraging = false;
        DragNode->clear();

        auto CheckNode = ax::Node::create();
        CheckNode->setName("CheckNode");
        auto s         = ax::Sprite::create("Cursor.png"sv);
        CheckNode->addChild(s);
        
        auto body      = ax::PhysicsBody::createBox(ax::Vec2(16, 16));
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        CheckNode->setPhysicsBody(body);
        addChild(CheckNode);

        int sx = Spos.x / 16;
        int sy = Spos.y / 16;

        int ex = EPos.x / 16;
        int ey = EPos.y / 16;

        ax::Vec2 pos;
        pos.x = sx * 16;
        pos.y = sy * 16;

        CheckNode->setPosition(pos);

        CheckNode->setVisible(true);
        for (int i = sy; i <= ey - sy; i++)
        {
            for (int j = sx; j <= ex - sx; j++)
            {
                ax::Vec2 pos;
                pos.x = j * 16;
                pos.y = i * 16;

                CheckNode->setPosition(pos);
            }

        }
        //CheckNode->setVisible(false);

        /*printf("시작점 x : %f ,  y : %f\n", Spos.x, Spos.y);
        printf("끝점 x : %f ,  y : %f\n", EPos.x, EPos.y);
        if (player)
            printf("캐릭터 위치 x : %f ,  y : %f\n", player->GetRoot()->getPosition().x, player->GetRoot()->getPosition().y);*/

    }
}
//마우스를 놓을 때 노드의 크기를 시작지점과 끝지점 기준으로 넓히고 해당 크기만큼 돌면서 컨택한 노드가 있는지 확인하는 코드 추가
//따라서 드래그했을때 해당 사각형 안에 있는 노드(즉 엑터)들이 플레이어의 엑터리스트에 들어가야함
void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    ax::Vec2 mousepos;
    mousepos.x = e->getCursorX();
    mousepos.y = e->getCursorY();

    if (isDraging)
    { 
        DragNode->clear();
        DragNode->setPosition(mousepos);
        DragNode->drawSolidRect(Spos - mousepos, ax::Vec2::ZERO, ax::Color4B::GREEN);
    }
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    if (code == ax::EventKeyboard::KeyCode::KEY_P)
        getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);

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

bool MainScene::onContactBegin(ax::PhysicsContact& contact)
{
    auto A = contact.getShapeA()->getBody()->getOwner();
    auto B = contact.getShapeB()->getBody()->getOwner();

    

    printf("충돌\n");

    return false;
}

bool MainScene::onContactSeparate(ax::PhysicsContact& contact)
{
    return false;
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
        // 아래는 업데이트 내용 위에서 서버에서 받은내용을 실행하고 그 다음 데이터 처리



    }
    break;
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


