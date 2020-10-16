#pragma once
#include <Neno/Core/Neno.h>

using namespace Neno::Core;

namespace Neno
{
	class Brick
	{
	private:
		Color* color;
		Texture* texture;
	public:
		Brick(Color* color, Texture* texture);
		void Draw(int x, int y, int width, int height);
	};
}
