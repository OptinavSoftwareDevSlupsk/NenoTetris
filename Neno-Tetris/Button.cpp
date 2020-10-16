#include "Button.h"

namespace Neno
{
	Button::~Button()
	{
		delete rectangle;
		rectangle = nullptr;
		font = nullptr;
		this->text.clear();
		this->text.shrink_to_fit();
	}

	Button::Button(wstring text, Font* font, int x, int y, int width, int height)
	{
		this->rectangle = new Neno::Core::Rectangle(x, y, width, height);
		this->font = font;
		this->text = text;
	}

	bool Button::IsSelected()
	{
		Point point(Mouse::GetX(), Application::currentConfig->screenHeight - Mouse::GetY());
		return this->rectangle->Contains(point);
	}

	void Button::Draw()
	{
		Color color = IsSelected() ? Color::Gray : Color::White;
		Primitives::DrawRectangleOutline(rectangle->position->x, rectangle->position->y, rectangle->size->x, rectangle->size->y, 4, color);

		int x = rectangle->position->x + (rectangle->size->x / 2) - (text.size() / 2 * font->GetSize());
		int y = rectangle->position->y + (rectangle->size->y / 2) - (font->GetSize() / 2);
		font->Draw(text, x, y, color);
	}

	bool Button::IsClicked()
	{
		return IsSelected() && Mouse::LeftReleased();
	}
}