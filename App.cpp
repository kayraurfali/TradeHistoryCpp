#include "App.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <graphics/shader_loader.h>

namespace trade_history
{
	App::App()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glm::mat4 projection = glm::ortho(0.0f, 1080.0f, 0.0f, 720.0f);
		shader_loader::get_instance().use(shader::font);
		shader_loader::get_instance().set_int("text", 0);
		shader_loader::get_instance().set_mat4("projection", glm::value_ptr(projection));

		font_d = new font();
		font_d->load("res/ALGER.TTF", 48);
	}

	App::~App()
	{}

	void App::update()
	{}

	void App::render()
	{
		font_d->draw("This is sample text", 500.0f, 360.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	}
}
