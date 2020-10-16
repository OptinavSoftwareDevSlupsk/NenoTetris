#pragma once
#include <Neno/Core/Neno.h>
#include "ScreenManager.h"
#include "Screen.h"
#include "MenuScreen.h"
#include "NameScreen.h"
#include "ScoreBoardScreen.h"

using namespace Neno::Core;

namespace Neno
{
	class Game :
		public Engine
	{
	private:

	public:
		void Create();
		void Update(float framesPerSecond);
		void Render();
	};
}
