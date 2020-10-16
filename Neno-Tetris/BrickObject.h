#pragma once
#include <vector>
#include <string>
#include "Brick.h"
#include "MapUtils.h"

namespace Neno
{
	class BrickObject
	{
	private: 
		int mapX;
		int mapY;
		int width;
		int height;
		int rotate; //0-3
		Brick* baseBricks[4][4];
		Brick* currentBricks[4][4];
		Color* color;

		void MoveToLeftDown(Brick* array[4][4]);
		bool CanRotateClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		bool CanRotateCounterClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		void GetRotatedClockwise(Brick* array[4][4]);
		void GetRotatedCounterClockwise(Brick* array[4][4]);
	public:
		~BrickObject();
		BrickObject(Color* color, Texture* brickTexture, int width, int height, std::string pattern);
		void RotateClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT], bool force = false);
		void RotateCounterClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT], bool force = false);
		void Draw();
		void DrawHelp(int x, int y);
		void DrawRelative(int x, int y);
		bool CanPlace(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		void Move(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		bool CanMove(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		void SetPosition(int x, int y);
		bool AddToMap(Brick* map[MAP_WIDTH][MAP_HEIGHT]);
		void RotateToZero(Brick* map[MAP_WIDTH][MAP_HEIGHT]);

		int GetMapX();
		int GetMapY();

		static MapUtils* mapUtils;
	};
}

