#include "pch.h"
#include "MapLayer.h"



bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    mMap = ax::TMXTiledMap::create("Map/Python/python.tmx");
    this->addChild(mMap);


    CreateWalls();


    return true;
}

void MapLayer::CreateWalls()
{
    auto wallLayer = mMap->getLayer("MetaInfo");
    auto wall      = mMap->getObjectGroup("Wall");

   

    //for (int i = 1; i < mHeight-1; i++)
    //{
    //    for (int j = 1; j < mWidth-1; j++)
    //    {
    //        auto tile = wallLayer->getTileAt(ax::Vec2(j, i));
    //        auto t = wallLayer->getTileGIDAt(ax::Vec2(j,i));
    //        if (t != 0)
    //        {
    //            auto property = wallLayer->getProperty("Wall");
    //            if (property.asBool())
    //            {  
    //                walls.push_back(tile->getPosition());
    //            }
    //        }
    //        

    //    }
    //    printf("\n");
    //}


    //for (int i = 0; i < walls.size() - 1; i++)
    //{
    //    auto dist = walls[i].distance(walls[i + 1]);
    //    if (dist < 50)
    //    {
    //        auto node = ax::DrawNode::create();
    //        node->drawLine(walls[i], walls[i + 1], ax::Color4B::RED);
    //        this->addChild(node);
    //    }
    //    
    //}
    //asdf


    printf("워 레이어 생성");
}
