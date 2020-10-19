#include "NameScreen.h"

namespace Neno
{
	NameScreen::~NameScreen()
	{
		delete font;
		delete titleFont;

		font = nullptr;
		titleFont = nullptr;

		titleColors.clear();
		titleColors.shrink_to_fit();
	}

	NameScreen::NameScreen(int points)
	{
		std::ifstream nameFile;
		nameFile.open(Utils::FilePath("temp.txt"));

		if (nameFile.good())
		{
			nameFile >> currentName;
			nameFile.close();
		}
		else
		{
			currentName = "";
		}

		titleColors.push_back(new Color(204, 0, 204));
		titleColors.push_back(new Color(255, 0, 0));
		titleColors.push_back(new Color(255, 255, 0));
		titleColors.push_back(new Color(0, 255, 0));
		titleColors.push_back(new Color(0, 255, 255));
		titleColors.push_back(new Color(0, 0, 170));

		titleX = (Application::currentConfig->screenWidth / 2) - (80 * 3);
		titleY = Application::currentConfig->screenHeight - 160;

		for (int a = 48; a < 123; a++)
		{
			if ((a >= 58 && a < 65) || (a >= 91 && a < 97))
				continue;

			chars.push_back((char)a);
		}

		this->points = points;
	}

	void NameScreen::Initialize()
	{
		font = new Font("Content/Fonts/PressStart2P-Regular.ttf", 32);
		titleFont = new Font("Content/Fonts/PressStart2P-Regular.ttf", 80, 32, 1104);
	}

	void NameScreen::Update(float framesPerSecond)
	{
		for (int a = 0; a < chars.size(); a++)
		{
			if (Keyboard::IsPressed(chars[a]))
				AddToName(chars[a]);
		}

		if (Keyboard::IsPressed(NENO_KEY_BACKSPACE))
		{
			if (currentName.size() > 0)
				currentName = currentName.substr(0, currentName.size() - 1);
		}

		if (Keyboard::IsPressed(NENO_KEY_ENTER))
		{
			if (currentName.size() > 0)
			{
				ScoreHelper::AddToScore(currentName, points);

				std::ofstream nameFile;
				nameFile.open(Utils::FilePath("temp.txt"));

				if (nameFile.good())
				{
					nameFile << currentName;
					nameFile.close();
				}

				ScreenManager::SetScreen(new ScoreBoardScreen());
			}
		}
	}

	void NameScreen::Render()
	{
		font->Draw("Points: ", (Application::currentConfig->screenWidth / 2) - 160, (Application::currentConfig->screenHeight / 2) + 40, Color::White);
		font->Draw(std::to_string(points), (Application::currentConfig->screenWidth / 2) + 96, (Application::currentConfig->screenHeight / 2) + 40, Color::White);
		font->Draw("Name:", (Application::currentConfig->screenWidth / 2) - 64, Application::currentConfig->screenHeight / 2, Color::White);

		Primitives::DrawRectangleOutline((Application::currentConfig->screenWidth / 2) - 160, (Application::currentConfig->screenHeight / 2) - 64, 320, 40, 4, Color::White);
		font->Draw(currentName, (Application::currentConfig->screenWidth / 2) - 160, (Application::currentConfig->screenHeight / 2) - 60, Color::White);

		font->Draw("Press ENTER to continue", (Application::currentConfig->screenWidth / 2) - 368, (Application::currentConfig->screenHeight / 2) - 120, Color::White);

		titleFont->DrawMultiColor(L"Тетрис", titleX, titleY, titleColors);
	}

	void NameScreen::AddToName(char letter)
	{
		if (currentName.size() < 10)
			currentName += letter;
	}
}