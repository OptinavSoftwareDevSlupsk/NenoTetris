#pragma once
#include <Neno/Core/Neno.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include "Screen.h"
#include "Brick.h"
#include "BrickObject.h"
#include "MapUtils.h"
#include "ScreenManager.h"
#include "NameScreen.h"

using namespace Neno::Core;
using namespace std;

namespace Neno
{
	class GameScreen :
		public Screen
	{
	private:
		Font* scoreFont;
		Texture* brickTexture;
		Color* gridColor;
		Sound* mainMusic;
		vector<Color*> brickColors;
		vector<BrickObject*> brickObjects;
		BrickObject* currentBrickObject;
		Brick* map[MAP_WIDTH][MAP_HEIGHT];
		MapUtils* mapUtils;
		int nextBricks[5];
		int points;
		int helperY;

		int tickBase;

		void ProcessMap();
		void RenderGrid();
		void RenderNextBricks();
	public:
		void Initialize();
		void Update(float framesPerSecond);
		void Render();
	};
}

