#pragma once
#include "JPSPathFinder.h"



class PathFind
{
public:

    PathFind(int width, int height);
    ~PathFind() {}

    void DefaultSetting(ax::TMXLayer* wall);
    
public:

    jpspath::CollisionMap::SharedPtr mColMap = nullptr;

    int mWidth;
    int mHeight;

};
