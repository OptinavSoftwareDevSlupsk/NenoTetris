#pragma once
namespace Neno
{
	class Screen
	{
	public:
		virtual ~Screen();

		virtual void Initialize();

		virtual void Update(float framesPerSecond);

		virtual void Render();
	};
}
