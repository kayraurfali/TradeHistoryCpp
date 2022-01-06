#pragma once

#include <util/types.h>
#include <GL/glew.h>

namespace trade_history
{
	class texture_2d
	{
	public:
		texture_2d();

		void load_texture(byte *texture_data, int width, int height);

		void bind() const;
		void unbind() const;
	private:
		GLuint texture_id;
		int width;
		int height;
	};
}
