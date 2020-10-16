#include "GameScreen.h"

namespace Neno
{
	void GameScreen::Initialize()
	{
		srand(time(NULL));

		mapUtils = new MapUtils(MAP_WIDTH, MAP_HEIGHT);

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				map[x][y] = nullptr;
			}
		}
		BrickObject::mapUtils = mapUtils;

		scoreFont = new Font("Content/Fonts/PressStart2P-Regular.ttf", 32, 32, 58);
		brickTexture = new Texture("Content/Graphics/brickBase.png");
		Sound::Initialize();
		mainMusic = new Sound("Content/Audio/Korobeiniki.wav");
		gridColor = new Color(15, 15, 15);

		brickColors.push_back(new Color(204, 0, 204));
		brickColors.push_back(new Color(255, 0, 0));
		brickColors.push_back(new Color(255, 255, 0));
		brickColors.push_back(new Color(0, 255, 0));
		brickColors.push_back(new Color(0, 255, 255));
		brickColors.push_back(new Color(0, 0, 170));
		brickColors.push_back(new Color(255, 119, 0));

		brickObjects.push_back(new BrickObject(brickColors[0], brickTexture, 3, 2, "111010"));
		brickObjects.push_back(new BrickObject(brickColors[1], brickTexture, 4, 1, "1111"));
		brickObjects.push_back(new BrickObject(brickColors[2], brickTexture, 3, 2, "111001"));
		brickObjects.push_back(new BrickObject(brickColors[3], brickTexture, 3, 2, "111100"));
		brickObjects.push_back(new BrickObject(brickColors[4], brickTexture, 3, 2, "110011"));
		brickObjects.push_back(new BrickObject(brickColors[5], brickTexture, 3, 2, "011110"));
		brickObjects.push_back(new BrickObject(brickColors[6], brickTexture, 2, 2, "1111"));

		int brickObjectIndex = rand() % 7;
		currentBrickObject = brickObjects[brickObjectIndex];
		currentBrickObject->SetPosition(5, 18);

		for (int a = 0; a < 5; a++)
		{
			nextBricks[a] = rand() % 7;
		}
		points = 0;
	}

	void GameScreen::Update(float framesPerSecond)
	{
		if (!mainMusic->IsPlayed())
			mainMusic->Play(true);

		if (tickBase >= 60 - (points/7))
		{
			if (currentBrickObject->CanMove(0, -1, map))
			{
				currentBrickObject->Move(0, -1, map);
			}
			else
			{
				ProcessMap();
			}
			
			tickBase = 0;
		}
		if (Keyboard::IsPressed(NENO_KEY_Q))
		{
			currentBrickObject->RotateCounterClockwise(map);
		}
		
		if (Keyboard::IsPressed(NENO_KEY_E))
		{
			currentBrickObject->RotateClockwise(map);
		}

		if (Keyboard::IsPressed(NENO_KEY_A))
		{
			currentBrickObject->Move(-1, 0, map);
		}

		if (Keyboard::IsPressed(NENO_KEY_D))
		{
			currentBrickObject->Move(1, 0, map);
		}

		bool helperChanged = false;
		for (int y = currentBrickObject->GetMapY(); y >= 0 ; y--)
		{
			if (!currentBrickObject->CanPlace(currentBrickObject->GetMapX(), y, map))
			{
				helperY = y+1;
				helperChanged = true;
				break;
			}
		}

		if(!helperChanged)
			helperY = 0;

		if (Keyboard::IsPressed(NENO_KEY_S))
		{
			currentBrickObject->SetPosition(currentBrickObject->GetMapX(), helperY);
			ProcessMap();
		}

		tickBase++;
	}

	void GameScreen::Render()
	{
		RenderGrid();

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				if(map[x][y] != nullptr)
					map[x][y]->Draw(mapUtils->MapToScreenX(x), mapUtils->MapToScreenY(y), 32, 32);
			}
		}
		RenderNextBricks();

		currentBrickObject->DrawHelp(currentBrickObject->GetMapX(), helperY);
		currentBrickObject->Draw();
		scoreFont->Draw(std::to_wstring(points), 5, Application::currentConfig->screenHeight - 40, Color::White);
	}

	void GameScreen::RenderGrid()
	{
		int gameX = mapUtils->GetGameAreaX();
		
		for (int x = 0; x < MAP_WIDTH+2; x++)
		{
			//vertical lines
			Primitives::DrawLine(gameX + (x * 32), 64, gameX + (x * 32), Application::currentConfig->screenHeight - 64, 4, *gridColor);
			brickTexture->Draw(gameX + (x * 32), 32, 32, 32);
			brickTexture->Draw(gameX + (x * 32), Application::currentConfig->screenHeight - 64, 32, 32);
		}

		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//horizontal lines
			Primitives::DrawLine(gameX + 32, 64 + (y * 32), gameX + (11 * 32), 64 + (y * 32), 4, *gridColor);
			Primitives::DrawLine(gameX + 32, 64 + (y * 32), gameX + (1 * 32), 64 + (y * 32), 4, *gridColor);
			brickTexture->Draw(gameX, 64 + (y * 32), 32, 32);
			brickTexture->Draw(gameX + (11 * 32), 64 + (y * 32), 32, 32);
		}
	}

	void GameScreen::RenderNextBricks()
	{
		int nextBrickX = Application::currentConfig->screenWidth - 192;
		Primitives::DrawRectangleOutline(nextBrickX, 32, 128, 128, 4, Color::White);
		Primitives::DrawRectangleOutline(nextBrickX, 176, 128, 128, 4, Color::White);
		Primitives::DrawRectangleOutline(nextBrickX, 320, 128, 128, 4, Color::White);
		Primitives::DrawRectangleOutline(nextBrickX, 464, 128, 128, 4, Color::White);
		Primitives::DrawRectangleOutline(nextBrickX, 608, 128, 128, 4, Color::White);

		for (int a = 0; a < 5; a++)
		{
			brickObjects[nextBricks[a]]->DrawRelative(nextBrickX, 32 + (144 * a));
		}
	}

	void GameScreen::ProcessMap()
	{
		if (currentBrickObject->AddToMap(map))
		{
			currentBrickObject->SetPosition(0, 0);
			currentBrickObject = nullptr;
			currentBrickObject = brickObjects[nextBricks[4]];
			currentBrickObject->RotateToZero(map);
			currentBrickObject->SetPosition(5, 18);

			for (int a = 3; a >= 0; a--)
			{
				nextBricks[a + 1] = nextBricks[a];
			}

			nextBricks[0] = rand() % 7;

			vector<int> rowsToDelete;
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				bool all = true;

				for (int x = 0; x < MAP_WIDTH; x++)
				{
					if (map[x][y] == nullptr)
					{
						all = false;
						break;
					}
				}

				if (all)
				{
					rowsToDelete.push_back(y);
				}
			}

			for (int a = 0; a < rowsToDelete.size(); a++)
			{
				for (int x = 0; x < MAP_WIDTH; x++)
				{
					for (int y = rowsToDelete[a] + 1; y < MAP_HEIGHT; y++)
					{
						map[x][y - 1] = map[x][y];
					}
				}

				for (int b = 0; b < rowsToDelete.size(); b++)
				{
					rowsToDelete[b]--;
				}
			}

			points += (rowsToDelete.size()*10);
		}
		else
		{
			ScreenManager::SetScreen(new NameScreen(points));
		}
	}
}