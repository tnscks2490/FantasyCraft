#pragma once
#include "PreDefines.h"
#include "UnitComp.h"
#include <stdlib.h>
#include <time.h>


struct AABOX
{
    int left;
    int right;
    int top;
    int bottom;
};


bool isContacted(AABOX blue, AABOX red);

ax::Vec2 GetZeroPointInRect(ax::Vec2 sPos, ax::Vec2 ePos);
float GetRectWidth(ax::Vec2 sPos, ax::Vec2 ePos);
float GetRectHeight(ax::Vec2 sPos, ax::Vec2 ePos);
float length(ax::Vec2 v1, ax::Vec2 v2);




/////////////////////////////////////
// 좌표계산식 필요한거 여기다 추가할것//

ax::Vec2 GetRandomPosToBuild(BuildingSize size, ax::Vec2 pos);
