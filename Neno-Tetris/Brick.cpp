#include "Brick.h"

namespace Neno
{
	Brick::Brick(Color* color, Texture* texture)
	{
		this->color = color;
		this->texture = texture;
	}

	void Brick::Draw(int x, int y, int width, int height)
	{
		texture->Draw(x, y, 32, 32, *color);
	}
}