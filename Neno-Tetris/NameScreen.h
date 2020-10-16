#pragma once
#include <Neno/Core/Neno.h>
#include <string>
#include <fstream>
#include "Screen.h"
#include "ScoreHelper.h"
#include "ScoreBoardScreen.h"
#include "ScreenManager.h"

using namespace Neno::Core;
using namespace std;

namespace Neno
{
	class NameScreen : public Screen
	{
	private:
		std::string currentName;
		Font* font;
		Font* titleFont;
		double titleX;
		double titleY;
		int points;
		vector<Color*> titleColors;
		vector<char> chars;
		void AddToName(char letter);
		
	public:
		~NameScreen();
		NameScreen(int points);
		void Initialize();
		void Update(float framesPerSecond);
		void Render();
	};
}