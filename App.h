#pragma once

#include <graphics/font.h>

namespace trade_history
{
	class App
	{
	public:
		App();
		~App();

		void update();
		void render();
	private:
		unsigned int VAO, VBO;
		font *font_d;
	};
}