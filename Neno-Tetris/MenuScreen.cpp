#include "MenuScreen.h"

namespace Neno
{
	MenuScreen::~MenuScreen()
	{
		delete mainMusic;
		delete newGameButton;
		delete exitButton;
		delete titleFont;
		delete buttonFont;

		titleFont = nullptr;
		buttonFont = nullptr;
		mainMusic = nullptr;
		newGameButton = nullptr;
		exitButton = nullptr;

		for (int a = 0; a < titleColors.size(); a++)
		{
			delete titleColors[a];
			titleColors[a] = nullptr;
		}

		titleColors.clear();
		titleColors.shrink_to_fit();
	}

	MenuScreen::MenuScreen()
	{
		titleColors.push_back(new Color(204,0,204));
		titleColors.push_back(new Color(255,0,0));
		titleColors.push_back(new Color(255, 255, 0));
		titleColors.push_back(new Color(0, 255, 0));
		titleColors.push_back(new Color(0,255,255));
		titleColors.push_back(new Color(0,0,170));

		titleX = (Application::currentConfig->screenWidth / 2) - (80 * 3);
		titleY = Application::currentConfig->screenHeight - 160;
	}

	void MenuScreen::Initialize()
	{
		titleFont = new Font("Content/Fonts/PressStart2P-Regular.ttf", 80, 32, 1104);
		buttonFont = new Font("Content/Fonts/PressStart2P-Regular.ttf", 32);
		mainMusic = new Sound("Content/Audio/Korobeiniki.wav");

		newGameButton = new Button(L"New game", buttonFont, Application::currentConfig->screenWidth/4, 256, Application::currentConfig->screenWidth / 2, 60);
		scoreButton = new Button(L"Score", buttonFont, Application::currentConfig->screenWidth / 4, 160, Application::currentConfig->screenWidth / 2, 60);
		exitButton = new Button(L"Exit", buttonFont, Application::currentConfig->screenWidth / 4, 64, Application::currentConfig->screenWidth / 2, 60);
	}

	void MenuScreen::Update(float framesPerSecond)
	{
		if (!mainMusic->IsPlayed())
			mainMusic->Play(true);

		if (newGameButton->IsClicked())
		{
			ScreenManager::SetScreen(new GameScreen());
			return;
		}

		if (scoreButton->IsClicked())
		{
			ScreenManager::SetScreen(new ScoreBoardScreen());
			return;
		}

		if (exitButton->IsClicked())
		{
			Application::Stop();
			return;
		}

		if (Keyboard::IsPressed(NENO_KEY_A))
			ScreenManager::SetScreen(new GameScreen());
	}

	void MenuScreen::Render()
	{
		newGameButton->Draw();
		scoreButton->Draw();
		exitButton->Draw();

		titleFont->DrawMultiColor(L"Тетрис", titleX, titleY, titleColors);
	}
}