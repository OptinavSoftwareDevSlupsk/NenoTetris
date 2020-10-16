#pragma once
#include <iostream>
#include <ctime>

namespace Neno
{
	class Score
	{
	private:

	public:
		Score(std::string date, int points);

		std::string date;
		int points;
	};
}

