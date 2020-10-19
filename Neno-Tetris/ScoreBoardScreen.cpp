#include "ScoreBoardScreen.h"

namespace Neno
{
	ScoreBoardScreen::~ScoreBoardScreen()
	{
		delete font;
		delete titleFont;

		font = nullptr;
		titleFont = nullptr;

		titleColors.clear();
		titleColors.shrink_to_fit();
	}

	ScoreBoardScreen::ScoreBoardScreen()
	{

		titleColors.push_back(new Color(204, 0, 204));
		titleColors.push_back(new Color(255, 0, 0));
		titleColors.push_back(new Color(255, 255, 0));
		titleColors.push_back(new Color(0, 255, 0));
		titleColors.push_back(new Color(0, 255, 255));
		titleColors.push_back(new Color(0, 0, 170));

		titleX = (Application::currentConfig->screenWidth / 2) - (80 * 3);
		titleY = Application::currentConfig->screenHeight - 160;

		this->points = points;

		scores = ScoreHelper::GetScoreBoard();
	}

	void ScoreBoardScreen::Initialize()
	{
		font = new Font("Content/Fonts/PressStart2P-Regular.ttf", 32);
		titleFont = new Font("Content/Fonts/PressStart2P-Regular.ttf", 80, 32, 1104);
	}

	void ScoreBoardScreen::Update(float framesPerSecond)
	{
		if (Keyboard::IsPressed(NENO_KEY_ESCAPE))
		{
			ScreenManager::SetScreen(new MenuScreen());
		}
	}

	void ScoreBoardScreen::Render()
	{
		Primitives::DrawRectangleOutline((Application::currentConfig->screenWidth / 2) - 356, 20, 712, 360, 2, Color::White);
		Primitives::DrawLine((Application::currentConfig->screenWidth / 2) - 292, 380, (Application::currentConfig->screenWidth / 2) - 292, 20, 2, Color::White);
		Primitives::DrawLine((Application::currentConfig->screenWidth / 2) + 28, 380, (Application::currentConfig->screenWidth / 2) + 28, 20, 2, Color::White);

		for (int a = 0; a < SCORE_BOARD_LIMIT; a++)
		{
			int y = 380 - ((a +1) * 32) - 2 - (4*a);

			font->Draw(std::to_string(a+1), (Application::currentConfig->screenWidth / 2) - 356, y, Color::White);
			Color color;

			if (a == 0)
				color = Color::Gold;
			else if (a == 1)
				color = Color::Silver;
			else if (a == 2)
				color = Color::Brown;
			else
				color = Color::White;
			if (a < scores.size())
			{
				font->Draw(scores[a]->date, (Application::currentConfig->screenWidth / 2) - 290, y, color);
				font->Draw(std::to_string(scores[a]->points), (Application::currentConfig->screenWidth / 2) + 30, y, color);
			}
		}

		titleFont->DrawMultiColor(L"Тетрис", titleX, titleY, titleColors);
	}
}