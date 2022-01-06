#pragma once

#include <core/gui_handler.h>

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
		gui_handler &handler;
		entity_id id;
	};
}