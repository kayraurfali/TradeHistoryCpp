#include "App.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/gui_components.h>
#include <iostream>

namespace trade_history
{
	App::App() : handler(gui_handler::instance())
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	App::~App()
	{}

	void App::update()
	{}

	void App::render()
	{
	}
}
