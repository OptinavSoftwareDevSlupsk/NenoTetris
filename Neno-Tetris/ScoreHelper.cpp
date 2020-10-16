#include "ScoreHelper.h"

namespace Neno
{
	bool ScoreHelper::Compare(Score* left, Score* right)
	{
		return left->points > right->points;
	}

	void ScoreHelper::AddToScore(std::string name, int points)
	{
		std::vector<Score*> scoreBoard = GetScoreBoard();

		scoreBoard.push_back(new Score(name, points));

		std::sort(scoreBoard.begin(), scoreBoard.end(), Compare);

		if (scoreBoard.size() > SCORE_BOARD_LIMIT)
			scoreBoard.erase(scoreBoard.begin() + SCORE_BOARD_LIMIT);

		std::string buffer;

		for (int a = 0; a < scoreBoard.size(); a++)
		{
			buffer += scoreBoard[a]->date + ";" + std::to_string(scoreBoard[a]->points);

			if (a < scoreBoard.size() - 1)
				buffer += "\n";
		}

		std::fstream file("score.txt", std::ios::out);

		file.write(&buffer[0], buffer.length());

		file.close();
	}

	std::vector<Score*> ScoreHelper::GetScoreBoard()
	{
		std::vector<Score*> scoreBoard;
		std::ifstream file;
		file.open("score.txt");

		if (file.good())
		{
			std::string scoreItem;

			while (std::getline(file, scoreItem))
			{
				int delimeterIndex = scoreItem.find(';');
				std::string name = scoreItem.substr(0, delimeterIndex);
				std::string pointString = scoreItem.substr(delimeterIndex + 1, scoreItem.size() - (delimeterIndex + 1));
				int points = std::stoi(pointString);

				scoreBoard.push_back(new Score(name, points));
			}

			file.close();
		}
	
		return scoreBoard;
	}
}