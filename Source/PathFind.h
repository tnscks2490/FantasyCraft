#pragma once
#include "JPSPathFinder.h"



class PathFind
{
public:

    PathFind(int width, int height);
    ~PathFind() {}

    void DefaultSetting(ax::TMXLayer* wall);
    void DebugMap();
    void update(float delta);
 
    bool Enter();

public:

    jpspath::CollisionMap::SharedPtr mColMap = nullptr;
    std::list<ax::Vec2> GetTargetList(ax::Vec2 start, ax::Vec2 dest);
    std::list<jpspath::Coord> PathSearch(ax::Vec2 start,ax::Vec2 dest);


    int Counting = 0;

    int mWidth;
    int mHeight;

};
