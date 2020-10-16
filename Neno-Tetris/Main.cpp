#include<iostream>
#include <cstdio>
#include <vector>
#include <Neno/Core/Neno.h>
#include "Game.h"
#include "ScoreHelper.h"

using namespace std;
using namespace Neno;
using namespace Neno::Core;

int main()
{
	//640x768

	Game* game = new Game();
	ApplicationConfig* config = new ApplicationConfig("Neno Tetris by Mateusz Nejman", 800, 768, false, false, Color::Black.Clone());
	Application::Start(game, config, 0, nullptr);

	return 0;
}