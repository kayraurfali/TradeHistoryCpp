#pragma once

#include <cstdint>
#include <GL/glew.h>

namespace trade_history
{
	class texture_2d
	{
		GLuint texture_id;
		int width;
		int height;
	public:
		texture_2d();

		void load_texture(uint8_t *texture_data, int width, int height);

		void bind() const;
		void unbind() const;
	};
}
