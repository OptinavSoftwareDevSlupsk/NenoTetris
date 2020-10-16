#pragma once
#include <Neno/Core/Neno.h>
#include <vector>
#include "Screen.h"
#include "Button.h"
#include "ScreenManager.h"
#include "GameScreen.h"
#include "ScoreBoardScreen.h"

using namespace Neno::Core;
using namespace std;

namespace Neno
{
	class MenuScreen :
		public Screen
	{
	private:
		Font* titleFont;
		Font* buttonFont;
		Sound* mainMusic;
		double titleAlpha;
		int titleX;
		int titleY;

		vector<Color*> titleColors;

		Button* newGameButton;
		Button* scoreButton;
		Button* exitButton;

	public:
		~MenuScreen();
		MenuScreen();

		void Initialize();
		void Update(float framesPerSecond);
		void Render();
	};
}

