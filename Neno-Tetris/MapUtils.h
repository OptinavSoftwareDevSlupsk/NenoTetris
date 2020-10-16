#pragma once
#include <Neno/Core/Neno.h>
#include "Brick.h"
#define MAP_WIDTH 10
#define MAP_HEIGHT 20

using namespace Neno::Core;

namespace Neno
{
	class MapUtils
	{
	private:
		int mapWidth;
		int mapHeight;
	public:
		MapUtils(int mapWidth, int mapHeight);
		int GetGameAreaX();
		int GetGameAreaY();
		int ScreenToMapX(int screenX);
		int ScreenToMapY(int screenY);
		int MapToScreenX(int mapX);
		int MapToScreenY(int mapY);
		bool IsInMapArea(int mapX, int mapY);
		bool IsFree(Brick* map[MAP_WIDTH][MAP_HEIGHT], int mapX, int mapY);
	};
}

