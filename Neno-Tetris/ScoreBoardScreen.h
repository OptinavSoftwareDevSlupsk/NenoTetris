#pragma once
#include <Neno/Core/Neno.h>
#include <string>
#include <fstream>
#include "Screen.h"
#include "Score.h"
#include "ScoreHelper.h"
#include "ScreenManager.h"
#include "MenuScreen.h"

using namespace Neno::Core;
using namespace std;

namespace Neno
{
	class ScoreBoardScreen : public Screen
	{
	private:
		std::string currentName;
		Font* font;
		Font* titleFont;
		double titleX;
		double titleY;
		int points;
		vector<Score*> scores;
		vector<Color*> titleColors;

	public:
		~ScoreBoardScreen();
		ScoreBoardScreen();
		void Initialize();
		void Update(float framesPerSecond);
		void Render();
	};
}