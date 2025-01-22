#include "pch.h"
#include "MapLayer.h"



MapLayer::MapLayer()
{
    printf("1\n");
    if (this->init())
    {
        printf("2\n");
        this->autorelease();
        printf("3\n");
    }
    printf("4\n");
}

MapLayer::~MapLayer() {}

bool MapLayer::init()
{
    printf("11\n");
    if (!Layer::init())
    {
        printf("22\n");
        return false;
        printf("33\n");
    }
    printf("44\n");

    mMap = ax::TMXTiledMap::create("Map/Python/Map.tmx");
    printf("55\n");
    this->addChild(mMap);

    //CreateWalls();


    return true;
}

void MapLayer::CreateWalls()
{
    auto wallLayer = mMap->getLayer("Wall");


    for (int i = 1; i < mHeight-1; i++)
    {
        for (int j = 1; j < mWidth-1; j++)
        {
            auto tile = wallLayer->getTileAt(ax::Vec2(j, i));
            auto t = wallLayer->getTileGIDAt(ax::Vec2(j,i));
            if (t != 0)
            {
                walls.push_back(tile->getPosition());
            }
            

        }
        printf("\n");
    }


    for (int i = 0; i < walls.size() - 1; i++)
    {
        auto dist = walls[i].distance(walls[i + 1]);
        if (dist < 50)
        {
            auto node = ax::DrawNode::create();
            node->drawLine(walls[i], walls[i + 1], ax::Color4B::RED);
            this->addChild(node);
        }
        
    }


    printf("워 레이어 생성");
}
