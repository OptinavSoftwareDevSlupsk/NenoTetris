#include "Game.h"

namespace Neno
{
	void Game::Create()
	{
		ScreenManager::SetScreen(new MenuScreen());
		
	}

	void Game::Update(float framesPerSecond)
	{
		ScreenManager::Update(framesPerSecond);
	}

	void Game::Render()
	{
		ScreenManager::Render();
	}
}