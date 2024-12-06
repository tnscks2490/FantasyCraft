#include "pch.h"
#include "MapLayer.h"



bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    mMap = ax::TMXTiledMap::create("Map/python/python.tmx");
    this->addChild(mMap);


    CreateWalls();


    return true;
}

void MapLayer::CreateWalls()
{
    auto wallLayer = mMap->getLayer("MetaInfo");

    auto  t = wallLayer->getProperty("Wall");


    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
        }
    }


    for (int i = 0; i < walls.size() - 1; i++)
    {
        
    }



    printf("워 레이어 생성");
}
