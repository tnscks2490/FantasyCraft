#pragma once
#include "PreDefines.h"


class MapLayer : public ax::Layer
{
public:
    CREATE_FUNC(MapLayer);

    MapLayer();
    ~MapLayer();

    ax::TMXTiledMap* mMap           = nullptr;
    ax::PhysicsWorld* mPhysicsWorld = nullptr;

    virtual bool init() override;

    ax::TMXTiledMap* GetMap() { return mMap; }
    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }
    void CreateWalls();
    void SettingResource();
    ax::Vec2 SetStartPoint();

    void ShowPath();
    void HidePath();



public:

    std::vector<ax::Node*> mPaths;

    std::vector<ax::Vec2> walls;

    std::vector<std::vector<ax::Vec2>> WallGroup;

    int mWidth  = 128;
    int mHeight = 128;

    bool isFirstSetting = true;
    bool isShowPath     = false;
};
