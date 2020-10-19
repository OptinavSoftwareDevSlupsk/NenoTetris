#include "BrickObject.h"

namespace Neno
{
	MapUtils* BrickObject::mapUtils = nullptr;

	BrickObject::~BrickObject()
	{
		delete[] baseBricks;
		delete[] currentBricks;
	}
	BrickObject::BrickObject(Color* color, Texture* brickTexture, int width, int height, std::string pattern)
	{
		this->width = width;
		this->height = height;
		this->rotate = 0;
		this->mapX = 0;
		this->mapY = 0;
		this->color = color;

		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				baseBricks[_x][_y] = nullptr;
			}
		}

		for (int a = 0; a < pattern.size(); a++)
		{
			int y = a / width;
			int x = a - (width * y);

			if(pattern.at(a) == '1') baseBricks[x][y] = new Brick(color, brickTexture);
		}

		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				currentBricks[_x][_y] = baseBricks[_x][_y];
			}
		}
	}

	void BrickObject::RotateClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT], bool force)
	{
		if (CanRotateClockwise(map) || force)
		{
			Brick* temp[4][4];
			GetRotatedClockwise(temp);
			MoveToLeftDown(temp);
			
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					currentBricks[x][y] = temp[x][y];
				}
			}

			rotate++;

			if (rotate > 3)
				rotate = 0;
		}
	}

	void BrickObject::RotateCounterClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT], bool force)
	{
		if (CanRotateCounterClockwise(map) || force)
		{
			Brick* temp[4][4];
			GetRotatedCounterClockwise(temp);
			MoveToLeftDown(temp);

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					currentBricks[x][y] = temp[x][y];
				}
			}

			rotate--;

			if (rotate < 0)
				rotate = 3;
			
		}
	}

	void BrickObject::MoveToLeftDown(Brick* array[4][4])
	{
		int moveX = 4;
		int moveY = 4;

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (array[x][y] != nullptr)
				{
					if (x < moveX)
						moveX = x;

					if (y < moveY)
						moveY = y;
				}
			}
		}

		Brick* temp[4][4];
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				int newX = x - moveX;
				int newY = y - moveY;

				if (newX < 0)
					newX = 4 + newX;

				if (newY < 0)
					newY = 4 + newY;

				if (newX > 3)
					newX -= 4;

				if (newY > 3)
					newY -= 4;

				temp[newX][newY] = array[x][y];
			}
		}

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				array[x][y] = temp[x][y];
			}
		}
	}

	bool BrickObject::CanPlace(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				if (currentBricks[_x][_y] != nullptr && !mapUtils->IsFree(map, x + _x, y + _y))
				{
					return false;
				}
			}
		}

		return true;
	}

	void BrickObject::Draw()
	{
		int x = mapUtils->MapToScreenX(this->mapX);
		int y = mapUtils->MapToScreenY(this->mapY);
		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				if(currentBricks[_x][_y] != nullptr)
					currentBricks[_x][_y]->Draw(x + (_x * 32), y + (_y * 32), 32, 32);
			}
		}
	}

	void BrickObject::DrawHelp(int x, int y)
	{
		int screenX = mapUtils->MapToScreenX(x);
		int screenY = mapUtils->MapToScreenY(y);
		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				if (currentBricks[_x][_y] != nullptr)
				{
					Primitives::DrawRectangleOutline(screenX + (_x * 32), screenY + (_y * 32), 32, 32, 4, *color);
				}
			}
		}
	}

	void BrickObject::DrawRelative(int x, int y)
	{
		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				if (baseBricks[_x][_y] != nullptr)
					baseBricks[_x][_y]->Draw(x + (_x * 32), y + (_y * 32), 32, 32);
			}
		}
	}

	void BrickObject::Move(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		if (CanMove(x,y, map))
		{
			this->mapX += x;
			this->mapY += y;
		}
	}

	void BrickObject::SetPosition(int x, int y)
	{
		this->mapX = x;
		this->mapY = y;
	}

	bool BrickObject::CanRotateClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		Brick* testArray[4][4];

		GetRotatedClockwise(testArray);

		MoveToLeftDown(testArray);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (testArray[x][y] != nullptr)
				{
					if (!mapUtils->IsInMapArea(mapX + x, mapY + y) || !mapUtils->IsFree(map, mapX + x, mapY + y))
						return false;
				}
			}
		}

		return true;
	}

	bool BrickObject::CanRotateCounterClockwise(Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		Brick* testArray[4][4];

		GetRotatedCounterClockwise(testArray);

		MoveToLeftDown(testArray);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (testArray[x][y] != nullptr)
				{
					if (!mapUtils->IsInMapArea(mapX + x, mapY + y) || !mapUtils->IsFree(map, mapX + x, mapY + y))
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	void BrickObject::GetRotatedClockwise(Brick* array[4][4])
	{
		int n = 4;

		for (int x = 0; x < n / 2; x++) {
			for (int y = x; y < n - x - 1; y++) {
				array[x][y] = currentBricks[n - 1 - y][x];
				array[n - 1 - y][x] = currentBricks[n - 1 - x][n - 1 - y];
				array[n - 1 - x][n - 1 - y] = currentBricks[y][n - 1 - x];
				array[y][n - 1 - x] = currentBricks[x][y];
			}
		}
	}

	void BrickObject::GetRotatedCounterClockwise(Brick* array[4][4])
	{
		int n = 4;

		for (int x = 0; x < n / 2; x++) {
			for (int y = x; y < n - x - 1; y++) {
				array[x][y] = currentBricks[y][n - 1 - x];
				array[y][n - 1 - x] = currentBricks[n - 1 - x][n - 1 - y];
				array[n - 1 - x][n - 1 - y] = currentBricks[n - 1 - y][x];
				array[n - 1 - y][x] = currentBricks[x][y];
			}
		}
	}

	bool BrickObject::CanMove(int x, int y, Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		int minX = 4;
		int minY = 4;
		int maxX = 0;
		int maxY = 0;

		for (int _x = 0; _x < 4; _x++)
		{
			for (int _y = 0; _y < 4; _y++)
			{
				if (currentBricks[_x][_y] != nullptr)
				{
					if (_x < minX)
						minX = _x;

					if (_y < minY)
						minY = _y;

					if (_x > maxX)
						maxX = _x;

					if (_y > maxY)
						maxY = _y;
				}
			}
		}
		bool isInMapArea = mapUtils->IsInMapArea(this->mapX + x - minX, this->mapY + y - minY) && mapUtils->IsInMapArea(this->mapX + x + maxX, this->mapY + y + maxY);
		
		if (isInMapArea)
		{
			for (int _x = 0; _x < 4; _x++)
			{
				for (int _y = 0; _y < 4; _y++)
				{
					if (currentBricks[_x][_y] != nullptr && !mapUtils->IsFree(map,this->mapX + x + _x, this->mapY + y + _y))
					{
						return false;
					}
				}
			}
		}
		return isInMapArea;
	}

	bool BrickObject::AddToMap(Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (currentBricks[x][y] != nullptr)
				{
					if (mapX + x >= MAP_WIDTH || mapY + y >= MAP_HEIGHT || map[mapX + x][mapY + y] != nullptr)
					{
						return false;
					}
					map[mapX + x][mapY + y] = currentBricks[x][y];
				}
			}
		}

		return true;
	}

	void BrickObject::RotateToZero(Brick* map[MAP_WIDTH][MAP_HEIGHT])
	{
		if (rotate != 0)
		{
			for (int a = 0; a < 4; a++)
			{
				RotateClockwise(map, true);

				if (rotate == 0)
					return;
			}
		}
	}

	int BrickObject::GetMapX()
	{
		return mapX;
	}

	int BrickObject::GetMapY()
	{
		return mapY;
	}
}