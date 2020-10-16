#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "Score.h"

#define SCORE_BOARD_LIMIT 10
namespace Neno
{
	class ScoreHelper
	{
	private:
		static bool Compare(Score * left, Score * right);
	public:
		static void AddToScore(std::string name, int points);
		static std::vector<Score*> GetScoreBoard();
	};
}