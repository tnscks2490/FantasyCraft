#pragma once
#include "PreDefines.h"


std::string_view IntToStringView(int num);
std::string_view FloatToStringView(float num);

std::string NumSlashNumToString(int num1, int num2);

int GetCreateCommand(ActorType type);

ax::Vec2 ChangeTiledPos(ax::Vec2 pos);
