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

    SettingResource();

    return true;
}

void MapLayer::CreateWalls()
{
    auto walls = mMap->getLayer("Wall");

    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            auto gid = walls->getTileGIDAt(ax::Vec2(j, i));
            if (gid != 0)
            {
                World::get()->mPath->SetTile(j, (mHeight - 1 - i));
                auto draw = ax::DrawNode::create();
                draw->drawRect(ax::Vec2(-16, -16), ax::Vec2(16, 16), ax::Color4B::RED);
                addChild(draw);
                draw->setPosition(ax::Vec2(j * 32, (mHeight-1 - i) * 32));
            }
        }
    }

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

        PK_Data data;
        data.ClientID = TcpClient::get()->GetID();
        data.input    = 50;
        data.pos      = pos;
        TcpClient::get()->SendMessageToServer(data);
        
        printf("123");
    }

}
