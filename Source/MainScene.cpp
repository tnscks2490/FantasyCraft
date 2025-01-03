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
#include "World.h"
#include "Actor.h"
#include "MoveComp.h"
#include "PathFind.h"
#include "TileNode.h"
#include "Player.h"
#include "Cursor.h"
#include "UnitComp.h"


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


    visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;    

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
    contactListener->onContactPreSolve = AX_CALLBACK_2(MainScene::onContactPreSolve, this);
    contactListener->onContactSeparate = AX_CALLBACK_1(MainScene::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    
    // 플레이어 생성
    mPlayer                  = new Player;
    mPlayer->mRace = PlayerRace::Terran;

    mMapLayer                = MapLayer::create();
    mMapLayer->mPhysicsWorld = getPhysicsWorld();
    mMapLayer->setPosition(ax::Vec2(0, 210));
    addChild(mMapLayer);

    // 커서 생성
    mCursor = new Cursor(this);

    mUILayer = UILayer::create();
    mUILayer->SetUI(mPlayer->mRace);
    addChild(mUILayer);
    
    mUILayer->mCursor = mCursor;
 


    World::get()->mPath = new PathFind(mMapLayer->GetWidth(), mMapLayer->GetHeight());

    auto wall = mMapLayer->GetMap()->getLayer("MetaInfo");
    World::get()->mPath->DefaultSetting(wall);

    
   

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
        if (mCursor->sp)
        {
            mCursor->ReleaseSp();
        }
        else
        {
            if (mPlayer->isSelected())
            {
                PK_Data data;
                data.ClientID = TcpClient::get()->GetID();
                data.input    = 'r';
                data.pos      = mousePos - (ax::Vec2(0, 210));
                TcpClient::get()->SendMessageToServer(data);
            }
        }
        

    }
    else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        mCursor->LeftClickDown();
        mCursor->isDraging = true;
        mCursor->sPos      = mousePos;
        mCursor->setPosition(mCursor->sPos);

        if (mCursor->sp)
        {
            if (mPlayer->PlayerActors.size() == 1 && mPlayer->PlayerActors[0]->mActorType == ActorType::SCV)
            {
                mPlayer->mMainActor = mPlayer->PlayerActors[0];
                PK_Data data;
                data.ClientID = TcpClient::get()->GetID();
                data.input    = 10;
                data.pos      = mCursor->sPos;
                TcpClient::get()->SendMessageToServer(data);

                /*Actor* actor = mPlayer->PlayerActors[0];
                ActorMessage msg;
                msg.msgType = MsgType::Build;
                msg.sender  = nullptr;
                msg.data    = nullptr;

                SendActorMessage(actor,msg);*/

            }
        }
    }
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    mCursor->ePos = ax::Vec2(e->getCursorX(), e->getCursorY());

    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        mCursor->LeftClickUp();
        mCursor->CursorUp();
       
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

    mCursor->GetRoot()->setPosition(mousepos);
    if (mCursor->isDraging)
    { 
        mCursor->GetDrawNode()->clear();
        mCursor->setPosition(mousepos);
        mCursor->GetDrawNode()->drawSolidRect(mCursor->sPos - mousepos,
            ax::Vec2::ZERO, ax::Color4B::GREEN);
    }
    mCursor->DeleteCheckNode();
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    if (code == ax::EventKeyboard::KeyCode::KEY_P)
    {
        printf("\n");
        for (int i = 0; i < World::get()->mPath->mColMap->GetHeight(); i++)
        {
            for (int j = 0; j < World::get()->mPath->mColMap->GetWidth(); j++)
            {
                if (World::get()->mPath->mColMap->IsCollision(j, i))
                    printf("O");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }

    switch (code)
    {
    case ax::EventKeyboard::KeyCode::KEY_O:
    {
        if (mPlayer->PlayerActors.size() == 1)
        {
            if (mPlayer->PlayerActors[0]->mActorType == ActorType::SCV)
            {
                Actor* actor = mPlayer->PlayerActors[0];

                PK_Data data;
                data.ClientID = TcpClient::get()->GetID();
                data.pos      = actor->GetPosition();
                data.input    = 77;
                TcpClient::get()->SendMessageToServer(data);
               
            }
        }
    } break;

    case ax::EventKeyboard::KeyCode::KEY_1:
        selectidx = 1;
        break;

    case ax::EventKeyboard::KeyCode::KEY_2:
        selectidx = 2;
        break;

    case ax::EventKeyboard::KeyCode::KEY_SPACE:
        mPlayer->PrintSelectActors();
        break;

    case ax::EventKeyboard::KeyCode::KEY_C:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = Vec2(500, 500);
        data.input    = 77;
        TcpClient::get()->SendMessageToServer(data);
    } break;

    case ax::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = Vec2(16, 0);
        data.input    = 6;
        TcpClient::get()->SendMessageToServer(data);
    } break;

    case ax::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = Vec2(-16,0);
        data.input    = 4;
        TcpClient::get()->SendMessageToServer(data);
    } break;


    default:
        break;
    }
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    
}

bool MainScene::onContactBegin(ax::PhysicsContact& contact)
{

    auto A = contact.getShapeA()->getBody()->getNode();
    auto B = contact.getShapeB()->getBody()->getNode();

    if (A->getName() == "CursorCheckNode" && B->getTag()==10)
    {
        auto bRoot = B->getParent();

        UserData* userData = (UserData*)bRoot->getUserData();

        if (userData->mActor->mID == TcpClient::get()->GetID())
        {
            mPlayer->Selected(userData->mActor);
        }
        return false;
    }
    else if (B->getName() == "CursorCheckNode" && A->getTag() == 10)
    {
        auto aRoot         = A->getParent();
        UserData* userData = (UserData*)aRoot->getUserData();

        if (userData->mActor->mID == TcpClient::get()->GetID())
        {
            mPlayer->Selected(userData->mActor);
        }
        return false;
    }

    return true;
}

bool MainScene::onContactPreSolve(ax::PhysicsContact& contact, ax::PhysicsContactPreSolve& solve)
{
    auto A = contact.getShapeA()->getBody()->getNode();
    auto B = contact.getShapeB()->getBody()->getNode();

    if (A->getTag() == 10 &&  B->getTag() == 10)
    {
        UserData* userDataA = (UserData*)A->getParent()->getUserData();
        UserData* userDataB = (UserData*)B->getParent()->getUserData();

        Actor* actorA = userDataA->mActor;
        Actor* actorB = userDataB->mActor;
 
        if (actorA->GetPosition().distance(actorA->mMoveComp->mLastTarget) <
            actorB->GetPosition().distance(actorB->mMoveComp->mLastTarget))
        {
            actorB->mMoveComp->CollisionMove(actorA->mMoveComp->mBodyBorder);
        }
        else if (actorA->GetPosition().distance(actorA->mMoveComp->mLastTarget) >
                 actorB->GetPosition().distance(actorB->mMoveComp->mLastTarget))
        {
            actorA->mMoveComp->CollisionMove(actorB->mMoveComp->mBodyBorder);
        }

        return true;
    }
    return true;
}

void MainScene::onContactSeparate(ax::PhysicsContact& contact)
{

    /*auto A = contact.getShapeA()->getBody()->getNode();
    auto B = contact.getShapeB()->getBody()->getNode();

    if (A->getPhysicsBody()->getTag() == B->getPhysicsBody()->getTag())
    {
        auto aRoot          = A->getParent();
        auto bRoot          = B->getParent();
        UserData* userDataA = (UserData*)aRoot->getUserData();
        UserData* userDataB = (UserData*)bRoot->getUserData();

        Actor* actorA = userDataA->mActor;
        Actor* actorB = userDataB->mActor;

        if (actorA->GetPosition().distance(actorA->mMoveComp->mLastTarget) <
            actorB->GetPosition().distance(actorB->mMoveComp->mLastTarget))
        {
            actorB->mMoveComp->SetPath(World::get()->mPath, actorB->mMoveComp->mLastTarget);
        }
        else if (actorA->GetPosition().distance(actorA->mMoveComp->mLastTarget) >
                 actorB->GetPosition().distance(actorB->mMoveComp->mLastTarget))
        {
            actorA->mMoveComp->SetPath(World::get()->mPath, actorA->mMoveComp->mLastTarget);
        }
    }*/
}

void MainScene::update(float delta)
{
    
    // 마우스가 화면 끝으로 갔을 때 화면 전체를 옮긴다.
    // 해당기능은 마우스의 위치백터만큼 화면에 더해야한다.
    //ScreenMove(delta);

    mCursor->update(delta);

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

void MainScene::DebugPath()
{
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            if (World::get()->mPath->mColMap->IsCollision(j, i))
            {
                auto node = DrawNode::create();
                node->setPosition(ax::Vec2(j * 16, i * 16));
                node->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4B::RED);
                addChild(node);
            }
            else
            {
                auto node = DrawNode::create();
                node->drawRect(ax::Vec2(-8, -8), ax::Vec2(8, 8), ax::Color4B::BLACK);
                addChild(node);
            }
        }
    }
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
        case 6:
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->idx == selectidx)
                {
                    actor->mMoveComp->SetTarget(actor->GetRoot()->getPosition() + data.pos);
                }
            }
        } break;

        case 4:
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->idx == selectidx)
                {
                    actor->mMoveComp->SetTarget(actor->GetRoot()->getPosition() + data.pos);
                }
            }
        } break;

        case 10:
        {
            if (data.ClientID == TcpClient::get()->GetID())
            {
                ////메세지를 쏴야한다~
                //ActorMessage msg;
                //msg.msgType = MsgType::Build;
                //msg.data = nullptr;
                //msg.sender  = nullptr;

                //SendActorMessage(nullptr,msg);
                Actor* CC = SpawnCommandCenter(mMapLayer, data);
                ax::Vec2 Pos;
                Pos = data.pos - mMapLayer->getPosition();
                CC->SetPosition(Pos);

                ActorMessage msg;
                msg.data = nullptr;
                msg.msgType = MsgType::Build;
                msg.sender  = CC;
                SendActorMessage(mPlayer->mMainActor, msg);

                printf("설치중");
            }
        }  break;

        case 77:
        case 78:
        case 79:
        {

            if (data.ClientID == TcpClient::get()->GetID())
            {
                Actor* actor = SpawnSCV(mMapLayer,data);
                actor->SetPosition(ax::Vec2(500, 500));
            }
            if (true)
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
                    /*Actor* actor = World::get()->CreateActor(this, data);
                    PK_Data d;
                    d.ClientID = TcpClient::get()->GetID();
                    d.input    = player->charNum;
                    d.pos      = player->GetRoot()->getPosition();
                    TcpClient::get()->SendActorMessage(d);*/
                }
            }
        }
        break;
        case 90:
        {
            for (auto actor : mPlayer->PlayerActors)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    actor->mMoveComp->SetPath(data.pos);
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
                for (auto actor : mPlayer->PlayerActors)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    actor->mMoveComp->SetPath(data.pos);
                }
            }
            break;
        ///////////////////////
        default:
            break;
        }
    }
}




void MainScene::ScreenMove(float delta)
{
    auto mCursorPos = mCursor->GetPosition();


    ScreenMoveTimer += delta;

    if (ScreenMoveTimer > 0.02f)
    {
        ScreenMoveTimer = 0;
        ax::Vec2 mapPos = mMapLayer->GetMap()->getPosition();
        if (mCursorPos.x > visibleSize.x - 32 && mapPos.x > -768)
        {
            mapPos.x -= 8;
            mMapLayer->GetMap()->setPosition(mapPos);
        }
        else if (mCursorPos.x < 32 && mapPos.x < 0)
        {
            mapPos.x += 8;
            mMapLayer->GetMap()->setPosition(mapPos);
        }
        else if (mCursorPos.y > visibleSize.y - 32  && mapPos.y > -1296)
        {
            mapPos.y -= 8;
            mMapLayer->GetMap()->setPosition(mapPos);
        }
        else if (mCursorPos.y < 32 && mapPos.y < 0)
        {
            mapPos.y += 8;
            mMapLayer->GetMap()->setPosition(mapPos);
        }
    }
}
