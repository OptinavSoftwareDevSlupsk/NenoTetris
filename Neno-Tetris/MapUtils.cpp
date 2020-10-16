#include "MapUtils.h"

namespace Neno
{
	MapUtils::MapUtils(int mapWidth, int mapHeight)
	{
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;
	}

	int MapUtils::GetGameAreaX()
	{
		return Application::currentConfig->screenWidth - 608;
	}

	int MapUtils::GetGameAreaY()
	{
		return 64;
	}

	int MapUtils::ScreenToMapX(int screenX)
	{
		return screenX - (GetGameAreaX() + 32) / 32;
	}

	int MapUtils::ScreenToMapY(int screenY)
	{
		return screenY - GetGameAreaY() / 32;
	}

	int MapUtils::MapToScreenX(int mapX)
	{
		return (GetGameAreaX() + 32) + (mapX * 32);
	}

	int MapUtils::MapToScreenY(int mapY)
	{
		return GetGameAreaY() + (mapY * 32);
	}

	bool MapUtils::IsInMapArea(int mapX, int mapY)
	{
		return mapX >= 0 && mapX < this->mapWidth && mapY >= 0;
	}

	bool MapUtils::IsFree(Brick* map[MAP_WIDTH][MAP_HEIGHT], int mapX, int mapY)
	{
		if (mapY >= MAP_HEIGHT)
			return true;

		return map[mapX][mapY] == nullptr;
	}
}