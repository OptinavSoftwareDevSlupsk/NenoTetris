#pragma once
#include <Neno/Core/Neno.h>
#include <string>

using namespace Neno::Core;
using namespace std;

namespace Neno
{
	class Button
	{
	private:
		Font* font;
		wstring text;
		Neno::Core::Rectangle* rectangle;
	public:
		~Button();
		Button(wstring text, Font* font, int x, int y, int width, int height);
		bool IsSelected();
		bool IsClicked();
		void Draw();
	};
}
