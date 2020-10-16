#include "ScreenManager.h"
#include <iostream>


namespace Neno
{
	Screen* ScreenManager::currentScreen = nullptr;
	bool ScreenManager::canRender = false;

	void ScreenManager::Update(float framesPerSecond)
	{
		if (currentScreen != nullptr)
			currentScreen->Update(framesPerSecond);
	}

	void ScreenManager::Render()
	{
		if (currentScreen != nullptr && canRender)
			currentScreen->Render();

		canRender = true;
	}

	void ScreenManager::SetScreen(Screen* screen)
	{
		canRender = false;
		if (currentScreen != nullptr)
		{
			delete currentScreen;
		}

		currentScreen = screen;

		currentScreen->Initialize();
	}
}