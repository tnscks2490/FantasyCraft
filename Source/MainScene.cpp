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
#include "Goal/Base/GoalComp.h"
#include "Player.h"
#include "UnitComp.h"
#include "DrawComp.h"
#include "CursorComp.h"
#include "MessageSystem.h"
#include <iostream>
#include "2DGeometry.h"



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


    mMapLayer                = new MapLayer(); 
    mMapLayer->mPhysicsWorld = getPhysicsWorld();
    mMapLayer->setPosition(ax::Vec2(0, 210));
    addChild(mMapLayer);




    // 커서 생성
    mCursor = SpawnCursor(this);
    mCursor->SetPosition(ax::Vec2(500,500));
    mCursor->mCursorComp->cPlayer = mPlayer;
    mPlayer->cursor = mCursor;

    //나중에 구조 꼭 수정할것 너무 복잡함
    mUILayer = UILayer::create();
    mUILayer->mCursor = mCursor;
    mUILayer->StartSettingWithPlayer(mPlayer);
    addChild(mUILayer);

    mPlayer->ui = mUILayer;

 


    World::get()->mPath = new PathFind(mMapLayer->GetWidth(), mMapLayer->GetHeight());

    // 이동불가능한 지형을 데이터로 넣기 TMX에다가쓰는방식(맵을 바꾸면서 수정해야함)
    auto wall = mMapLayer->GetMap()->getLayer("Wall");
    World::get()->mPath->DefaultSetting(wall);
    World::get()->mPath->DebugMap();
    
   

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
    ax::Vec2 realpos  = mousePos - mMapLayer->getPosition();

    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        if (mCursor->mCursorComp->mState != CursorState::Idle)
        {
            /*mCursor->mCursorComp->mState = CursorState::Idle;
            if (mPlayer->mMainActor)
            {
                SystemMessage smsg;
                smsg.Atype = mPlayer->mMainActor->mActorType;
                SendSystemMessage(mUILayer, mPlayer, smsg);
            }*/
            
        }
        else
        {
            if (mPlayer->mMainActor&& mCursor->mCursorComp->mBP)
            {
               SystemMessage smsg = {SMsgType::BPCancel, ReceiverType::UI, ActorType::None, ButtonType::None,  &mPlayer->mMainActor};
               SendSystemMessage(mUILayer, mPlayer, smsg);
            }
            mCursor->mCursorComp->RClick(mousePos);
            
        }
    }
    else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        mCursor->mCursorComp->LClick(realpos);
        if (mCursor->mCursorComp->mState == CursorState::Idle)
        {
            mCursor->mCursorComp->mState = CursorState::Drag;
            mCursor->mCursorComp->sPos   = mousePos;
            mCursor->mCursorComp->ePos   = mousePos + ax::Vec2(1,1);
        }
        else if (mCursor->mCursorComp->mState == CursorState::Target)
        {
            //AddGoal_MoveToPath(mPlayer->mMainActor, realpos);
            //mCursor->mCursorComp->mState = CursorState::Idle;
            
            printf("이게 문제야 문제");
        }
        else
        {
            mCursor->mCursorComp->mState = CursorState::Idle;
            if (mPlayer->mMainActor)
            {
                SystemMessage smsg;
                smsg.Atype = mPlayer->mMainActor->mActorType;
                SendSystemMessage(mUILayer, mPlayer, smsg);
            }
            
        }
        
    }
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    ax::Vec2 mousePos = ax::Vec2(e->getCursorX(), e->getCursorY());

    mCursor->mCursorComp->ePos = ax::Vec2(e->getCursorX(), e->getCursorY());
    ax::Vec2 sPos              = mCursor->mCursorComp->sPos;
    ax::Vec2 ePos              = mCursor->mCursorComp->ePos;


    // TODO: 나중에 꼭 정리할것 
    // LeftClick
    auto Lfunc = [&](PhysicsWorld& world, PhysicsShape& shape, void* userData) -> bool {
        auto A                = shape.getBody()->getNode();
        std::string_view name = A->getName();

        std::cout << name.data() << "\n" << std::endl;

        if (A->getTag() == 10 || A->getTag() == 20)
        {
            auto aRoot         = A->getParent();
            UserData* userData = (UserData*)aRoot->getUserData();

            if (mCursor->mCursorComp->mState == CursorState::Target)
            {
                ActorMessage msg = {MsgType::SetTarget, userData->mActor, nullptr, nullptr};
                for (auto ac : mPlayer->PlayerActors)
                {
                    if (ac != nullptr)
                        SendActorMessage(ac, msg);
                }
            }
            else
            {
                if (userData->mActor->mID == TcpClient::get()->GetID())
                {
                    mPlayer->PreSelected(userData->mActor);
                }
            }
            
        }
        return true;
    };
    //RightClick
    auto Rfunc = [&](PhysicsWorld& world, PhysicsShape& shape, void* userData) -> bool {
        auto A                = shape.getBody()->getNode();
        std::string_view name = A->getName();

        std::cout << name.data() << "\n" << std::endl;

        if (A->getTag() == 10)
        {
            auto aRoot         = A->getParent();
            UserData* userData = (UserData*)aRoot->getUserData();

            auto ac = userData->mActor;
            if (ac->mUnitComp)
            {
                auto builder = mPlayer->mMainActor;
                if (builder->mActorType == ActorType::SCV)
                {
                    ActorMessage msg = {MsgType::Build_Continue, ac, nullptr, nullptr};
                    SendActorMessage(builder, msg);
                }
            }
           
        }
        return true;
    };

    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        if (mCursor->mCursorComp->mState == CursorState::Target)
        {
            getPhysicsWorld()->queryRect(Lfunc, Rect(mousePos.x, mousePos.y, 5, 5), nullptr);
        }
        else if (mCursor->mCursorComp->mState == CursorState::Drag)
        {
            float width = GetRectWidth(sPos, ePos);
            float height = GetRectHeight(sPos, ePos);
            ax::Vec2 zpos = GetZeroPointInRect(sPos, ePos);

            // 여러개가 선택된다면 해당 함수만 여러번 호출된다.
            getPhysicsWorld()->queryRect(Lfunc, Rect(zpos.x, zpos.y, width, height), nullptr);

            if (mPlayer->PrePlayerActorsNum() > 0)
                mPlayer->ReSelected();
            
            mCursor->mCursorComp->GreenRectClear();
            mCursor->mCursorComp->mState = CursorState::Idle;
            mCursor->mCursorComp->sPos   = mCursor->mCursorComp->ePos;
        }
    }
    else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        getPhysicsWorld()->queryRect(Rfunc, Rect(mousePos.x, mousePos.y, 5, 5), nullptr);
    }

}
//마우스를 놓을 때 노드의 크기를 시작지점과 끝지점 기준으로 넓히고 해당 크기만큼 돌면서 컨택한 노드가 있는지 확인하는 코드 추가
//따라서 드래그했을때 해당 사각형 안에 있는 노드(즉 엑터)들이 플레이어의 엑터리스트에 들어가야함
void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);

    ax::Vec2 mousepos = ax::Vec2(e->getCursorX(), e->getCursorY());


    mCursor->SetPosition(mousepos);


    if (mCursor->mCursorComp->mState == CursorState::Drag)
    {
         mCursor->mCursorComp->ePos = mousepos;
    }
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
        if (mPlayer->PlayerActorsNum() == 1)
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


    // SCV 생성
    case ax::EventKeyboard::KeyCode::KEY_C:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = Vec2(500, 500);
        data.input    = 100;
        TcpClient::get()->SendMessageToServer(data);
    } break;

    // Marine 생성
    case ax::EventKeyboard::KeyCode::KEY_V:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = ax::Vec2(500, 500);
        data.input    = 101;
        TcpClient::get()->SendMessageToServer(data);
    }break;
    ///////////////////////////// input 나중에 정렬할것
    case ax::EventKeyboard::KeyCode::KEY_X:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = Vec2(500, 500);
        data.input    = 102;
        TcpClient::get()->SendMessageToServer(data);
    }
    break;

    case ax::EventKeyboard::KeyCode::KEY_M:
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.pos      = ax::Vec2(300, 500);
        data.input    = 50;
        TcpClient::get()->SendMessageToServer(data);
    }
    break;

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

    auto AbodyNode = A;
    auto BbodyNode = B;

    while (A->getName() != "Root")
    {
        A = A->getParent();
    }
    while (B->getName() != "Root")
    {
        B = B->getParent();
    }

    UserData* dataA = (UserData*)A->getUserData();
    UserData* dataB = (UserData*)B->getUserData();

    ActorMessage amsgA = {MsgType::Contacted, dataB->mActor, AbodyNode, dataB};
    SendActorMessage(dataA->mActor, amsgA);

    ActorMessage amsgB = {MsgType::Contacted, dataA->mActor, BbodyNode, dataA};
    SendActorMessage(dataB->mActor, amsgB);

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

    auto A = contact.getShapeA()->getBody()->getNode();
    auto B = contact.getShapeB()->getBody()->getNode();

    auto AbodyNode = A;
    auto BbodyNode = B;

    while (A->getName() != "Root")
    {
        A = A->getParent();
    }
    while (B->getName() != "Root")
    {
        B = B->getParent();
    }

    UserData* dataA = (UserData*)A->getUserData();
    UserData* dataB = (UserData*)B->getUserData();

    ActorMessage amsgA = {MsgType::Separate, dataB->mActor, AbodyNode, dataB};
    SendActorMessage(dataA->mActor, amsgA);

    ActorMessage amsgB = {MsgType::Separate, dataA->mActor, BbodyNode, dataA};
    SendActorMessage(dataB->mActor, amsgB);

   
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
        case 10:
        {
            if (data.ClientID == TcpClient::get()->GetID())
            {
                //data.pos를 사용하는게 더 나아보임 나중에 수정할것
                ax::Vec2 pos = mCursor->GetPosition()-mMapLayer->getPosition();
                ActorMessage msg = {MsgType::Build, nullptr, nullptr, &pos};
                SendActorMessage(mPlayer->mMainActor, msg);

                printf("설치중");
            }
        }  break;
        case 50:
        {
            Actor* actor = SpawnMineral(mMapLayer, data);
            actor->SetPosition(data.pos);
        }
        break;
        case 77:
        case 78:
        case 79:
        {
            Actor* actor = SpawnSCV(mMapLayer, data);
            actor->SetPosition(data.pos);
        } break;
        case 90:
        {
            for (auto actor : mPlayer->PlayerActors)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    actor->mMoveComp->SetPath(data.pos);
                }
            }
        } break;

        // Actor 생성 라인
        case 100: //SCV 생성
        {
            Actor* actor = SpawnSCV(mMapLayer, data);
            actor->SetPosition(data.pos);
        } break;

        case 101:  // 마린 생성
        {
            Actor* actor = SpawnMarine(mMapLayer, data);
            actor->SetPosition(data.pos);
        } break;

        case 102:  // 커맨드센터 생성
        {
            Actor* actor = SpawnCommandCenter(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        } break;
        case 103: // 서플라이 생성
        {
            Actor* actor = SpawnSupplyDepot(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        } break;
        case 104: // 배럭 생성
        {
            Actor* actor = SpawnBarrack(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 105:  // 엔지니어링 베이 생성
        {
            Actor* actor = SpawnEngineeringBay(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 106:  // 리파이너리(가스) 생성
        {
            Actor* actor = SpawnRefinery(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 107:  // 아카데미 생성
        {
            Actor* actor = SpawnAcademy(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 108:  // 아머리 생성
        {
            Actor* actor = SpawnArmory(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 109:  // 벙커 생성
        {
            Actor* actor = SpawnBunker(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 110:  // 스타포트 생성
        {
            Actor* actor = SpawnStarPort(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 111:  // 사이언스퍼실리티 생성
        {
            Actor* actor = SpawnScienceFacility(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;
        case 112:  // 펙토리 생성
        {
            Actor* actor = SpawnFactory(mMapLayer, data);
            actor->SetPosition(data.pos);

            if (data.ClientID == TcpClient::get()->GetID())
            {
                ActorMessage msg = {MsgType::SendInfo, actor, nullptr, nullptr};
                SendActorMessage(mPlayer->mMainActor, msg);
            }
        }
        break;

        case 114: // MoveToPath
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor)
                {
                    if (actor->mDrawComp->selected && !actor->mUnitComp->IsCmdLocked())
                        AddGoal_MoveToPath(actor, data.pos);
                }
                

            }
        } break;

        case 115: // 건물 건설
        {
            for (auto actor : World::get()->w_ActorList)
            {
                if (actor && actor->mID == data.ClientID)
                {
                    if (actor->mDrawComp->selected)
                        AddGoal_BuildStructure(actor,ActorType::Cursor);
                }
            }
        }
        break;
        case 117: // 사망 이펙트띄우기
        {
            auto node = ax::Node::create();
            this->addChild(node,1);
            node->setPosition(data.pos);
            TestFunc(node);
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

void MainScene::TestFunc(ax::Node* node)
{
    AnimInfo& animInfo = FindAnimInfo(ECharName::SCV, ECharAct::Death, ECharDir::Face);
    animInfo.CreateAnimation();

    auto sprite            = ax::Sprite::createWithSpriteFrame(animInfo.animation->getFrames().front()->getSpriteFrame());
    node->addChild(sprite);
    ax::Animate* animate = ax::Animate::create(animInfo.animation.get());
    ax::Action* action = ax::RepeatForever::create(animate);    
    node->runAction(action);
}
