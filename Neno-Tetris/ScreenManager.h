#pragma once
#include <Neno/Core/Application.h>
#include "Screen.h"

namespace Neno
{
	class ScreenManager
	{
	private:
		static Screen* currentScreen;
		static bool canRender;
	public:
		static void Update(float framesPerSecond);

		static void Render();

		static void SetScreen(Screen* screen);
	};
}