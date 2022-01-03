#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace trade_history
{
	struct shader
	{
		static const uint32_t font = 0;
		static const uint32_t color = 1;
	};

	class shader_loader
	{
	public:

		static shader_loader &get_instance()
		{
			return instance;
		}

		void load(const char *vert_file, const char *frag_file);
		void use(unsigned short program_id_index);

		void set_int(const char *name, int value);
		void set_mat4(const char *name, float *value);
		void set_vec3(const char *name, float *value);
	private:

		static const unsigned short MAX_SHADERS = 16;
		uint32_t current_index;
		uint32_t shader_to_use;
		GLuint program_ids[MAX_SHADERS];

		static shader_loader &instance;

		static shader_loader &create()
		{
			static shader_loader sm;

			return sm;
		}

		shader_loader();

		static bool _is_successful(GLuint id, GLuint action);
	};

}