#pragma once
#include "JPSPathFinder.h"



class PathFind
{
public:

    PathFind(int width, int height);
    ~PathFind() {}

    void DefaultSetting(ax::TMXLayer* wall);
    void DebugMap();

public:

    jpspath::CollisionMap::SharedPtr mColMap = nullptr;

    int mWidth;
    int mHeight;

};
