#include "pch.h"
#include "MapLayer.h"
#include "PathFind.h"


MapLayer::MapLayer()
{
    if (this->init())
    {
        this->autorelease();
    }
}

MapLayer::~MapLayer() {}

bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    mMap = ax::TMXTiledMap::create("Map/StarMap/StarMap.tmx");
    this->addChild(mMap);


    return true;
}

void MapLayer::CreateWalls()
{
    auto walls = mMap->getLayer("Wall");

    //auto draw = ax::DrawNode::create();
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            auto gid = walls->getTileGIDAt(ax::Vec2(j, i));
            if (gid != 0)
            {
                World::get()->mPath->SetTile(j, (mHeight - 1 - i));
                
                //draw->drawRect(ax::Vec2(-16 , -16), ax::Vec2(16, 16), ax::Color4B::RED);
                //draw->setPosition(ax::Vec2(j * 32, (mHeight-1 - i) * 32));
                /*draw->drawRect(ax::Vec2(-16 + j*32, -16 + (mHeight-1 - i) * 32),
                               ax::Vec2(16 + j * 32, 16 + (mHeight - 1 - i) * 32),
                               ax::Color4B::RED);*/
            }
        }
    }
   // addChild(draw);
}

void MapLayer::SettingResource()
{
    auto rscLayer = mMap->getObjectGroup("ResourcePoint");

    auto minerals = rscLayer->getObjects();
    for (auto p : minerals)
    {
        ax::ValueMap obj = p.asValueMap();

        ax::Vec2 pos;
        pos.x = obj["x"].asFloat();
        pos.y = obj["y"].asFloat();

        pos.x = (int)pos.x / 32;
        pos.y = (int)pos.y / 32;

        pos.x = pos.x * 32;
        pos.y = pos.y * 32;


        auto t = obj["type"].asString();

        if (t == "Mineral")
        {
            PK_Data data;
            data.ClientID = -1;
            data.input    = 50;
            data.pos      = pos;
            TcpClient::get()->SendMessageToServer(data);
        }
        else if (t == "Gas")
        {
            PK_Data data;
            data.ClientID = -1;
            data.input    = 51;
            data.pos      = pos;
            TcpClient::get()->SendMessageToServer(data);
        }

        auto draw = ax::DrawNode::create();
        draw->drawDot(pos, 4, ax::Color4B::ORANGE);
        draw->setPosition(ax::Vec2::ZERO);
        addChild(draw, 4);

    }

}

ax::Vec2 MapLayer::SetStartPoint()
{
    auto spawnPoints = mMap->getObjectGroup("SpawnPoint");
    auto SP = spawnPoints->getObjects();
    std::vector<ax::Vec2> startPoints;

    for (auto sp : SP)
    {
        ax::ValueMap obj = sp.asValueMap();

        ax::Vec2 pos;
        pos.x = obj["x"].asInt()/32;
        pos.y = obj["y"].asInt()/32;

        pos.x = pos.x * 32;
        pos.y = pos.y * 32;

        startPoints.push_back(pos);

        auto draw = ax::DrawNode::create();
        draw->drawDot(pos, 4, ax::Color4B::MAGENTA);
        draw->setPosition(ax::Vec2::ZERO);
        addChild(draw, 4);

    }

    int idx = TcpClient::get()->GetID();
    idx     = idx % 4;

    auto spos = startPoints[idx];

    PK_Data data;
    data.ClientID = TcpClient::get()->GetID();
    data.input    = 80;
    data.pos      = spos;
    TcpClient::get()->SendMessageToServer(data);

    for (int i = 0; i < 4; i++)
    {
        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 100;
        data.pos      = spos +ax::Vec2(i*36,-64);
        TcpClient::get()->SendMessageToServer(data);
    }

    return spos;
}

void MapLayer::ShowPath()
{
    isShowPath = true;
    auto draw  = ax::DrawNode::create();
    for (int y = 0; y < 128; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            
            if (World::get()->mPath->mColMap->IsCollision(x, y))
                draw->drawDot(ax::Vec2(x * 32, y * 32), 2, ax::Color4B::RED);
            else
                draw->drawDot(ax::Vec2(x * 32, y * 32), 2, ax::Color4B::BLUE);
           
        }
    }
    draw->setName("Dot");
    addChild(draw);
}

void MapLayer::HidePath()
{
    isShowPath = false;
    auto dot   = getChildByName("Dot");
    dot->removeFromParentAndCleanup(true);
}
